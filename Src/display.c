#include "display.h"
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include <stdbool.h>

#define START_X  8
#define X   1
#define Y_ANGLE   5
#define Y_VEL 7

void convertVelocity(double velocity);
void convertAngle(double angle);

static char angleBuffer_ [12] = "";
static int angleLength_ = 0;
static int angleIndex_ = 0;
static bool angleNextChar_ = false;

static char velocityBuffer_ [12] = "";
static int velocityLength_ = 0;
static int velocityIndex_ = 0;
static bool velocityNextChar_ = false;

/* 
*   print the standard text on display
*/
void display_start() {
    lcdGotoXY(X,Y_ANGLE);
    lcdPrintlnS("Angle:\n");
    lcdGotoXY( X,(Y_VEL) );
    lcdPrintlnS("Speed:\n");
}

void display_updateBuffer(double angle , double velocity) {
    convertAngle(angle);
    convertVelocity(velocity);
}

void display_update() {
    if (angleNextChar_){
        lcdGotoXY(START_X + angleIndex_, Y_ANGLE); 
        lcdPrintC(angleBuffer_[angleIndex_]);
        angleIndex_++;
        if(angleIndex_ >= angleLength_){
            angleNextChar_ = false;
        }
    }
    else if (velocityNextChar_){
        lcdGotoXY(START_X + velocityIndex_, Y_VEL); 
        lcdPrintC(velocityBuffer_[velocityIndex_]);
        velocityIndex_++;
        if(velocityIndex_ >= velocityLength_){
            velocityNextChar_ = false;
        }
    }
}

void convertAngle(double angle) {
    sprintf(angleBuffer_, "%.3f", angle);
    angleLength_ = (int) strlen(angleBuffer_);
    angleIndex_ = 0;
    angleNextChar_ = true;
}

void convertVelocity(double velocity) {
    sprintf(velocityBuffer_, "%.3f", velocity);
    velocityLength_ = (int) strlen(velocityBuffer_);
    velocityIndex_ = 0;
    velocityNextChar_ = true;
}
// EOF