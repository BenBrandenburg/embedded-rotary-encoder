#include "fsm.h"
#include "display.h"
#include "fsmStates.h"
#include "gpio.h"
#include "computing.h"
#include "time.h"
#include <stdbool.h>
#include <stdint.h>

#define MIN_TIME 0.25   // min time between display updates
#define MAX_TIME 0.5    // max time between display updates

void getInput();
void changeState();
void processInput();
void outPut();

void setErrorState();
void reset();
void countSteps();
void calcPhaseDiff();

// converts last phase and new phase to a state
static FsmState phaseToState[4][4] = {
    {Idle, Reverse, Forward, Error},
    {Forward, Idle, Error, Reverse},
    {Reverse, Error, Idle, Forward},
    {Error, Forward, Reverse, Idle}
};

/*
*   declaration and initialization of variables
*/
static FsmState state_ = Idle;
static int counter_ = 0;
static int lastCounter_ = 0;

static int phaseDiffCounter_ = 0;

static Phase currentPhase_;
static Phase previousPhase_;
static bool s6Pressed_ = false;

static double angle_ = 0.0;
static double velocity_ = 0.0;
static uint32_t currentTime_ = 0;
static uint32_t lastTime_;

// superloop
void fsm_run() {
    display_start();
    time_initTimer();
    reset();

    while(1) {
        getInput(); 
        changeState();
        if (state_ == Error && (s6Pressed_)) reset();
        processInput();
        outPut();
    }
}

void getInput() {
    currentPhase_ = gpio_getPhase();
    currentTime_ = time_getTimeStamp();
    s6Pressed_ = gpio_S6Pressed();
}

void changeState() {
    if (state_ == Error) return;
    state_ = phaseToState[previousPhase_][currentPhase_];
}

void processInput() {
    if (state_ == Error) return;

    countSteps();
    
    double dt = time_getDt(currentTime_, lastTime_);

    /*
    *   calculate new angle, velocity and update displaybuffer if time since last update >= 0.25 s 
    *   and phases changed or if 0.5 s have passed since last update
    */ 
    if ((dt >= MIN_TIME && currentPhase_ != previousPhase_) || (dt >= MAX_TIME)) { 
        calcPhaseDiff();  
        angle_ = computing_getRotationAngle(counter_);
        velocity_ = computing_getAngleVelocity(phaseDiffCounter_, dt);
        display_updateBuffer(angle_, velocity_);
        lastTime_ = currentTime_;
    }
    previousPhase_ = currentPhase_;
}

/*
*   update the display and the gpio output
*   ledD20 was used to measure the time it takes to print with an oscilloscope
*/
void outPut() {
    gpio_ledD20_high();    
    display_update();
    gpio_ledD20_low();
    gpio_output(counter_, state_);
}

void reset() {
    currentPhase_ = gpio_getPhase();
    previousPhase_ = currentPhase_;
    lastTime_ = time_getTimeStamp();
    counter_ = 0;
    lastCounter_ = 0;
    currentTime_ = 0;
    phaseDiffCounter_ = 0;
    state_ = Idle;
}


void countSteps() {
    if (state_ == Forward) {
        if (counter_ == INT_MAX) {
            counter_ = INT_MIN;
        }
        else {
            counter_++;
        }
    }
    if (state_ == Reverse) {
        if (counter_ == INT_MIN) {
            counter_ = INT_MAX;
        }
        else {
            counter_--;            
        }
    }
}


void calcPhaseDiff(){
    phaseDiffCounter_ = counter_ - lastCounter_;
    lastCounter_ = counter_; 
}
// EOF