#include "gpio.h"
#include "stm32f4xx.h"

#define LED_FORWARD 7 
#define LED_REVERSE 6
#define LED_ERROR 5
#define LED_OSC 3

static FsmState lastState_;

/* 
*   read the encoder input and return it as a phase
*   the encoder sends 2 bits which indicates it's movement
*/
Phase gpio_getPhase(void) {
    return(GPIOF->IDR & 0x3U); // ANDed with 3, because only the first two bits are significant
}


bool gpio_S6Pressed(void) {
    return !(GPIOF->IDR & (1 << 6)); // s6 is 6th bit of gpiof
}

/*
*   update the boards leds depending on fsm state and first 8 bits of counter
*/
void gpio_output(uint8_t counter, FsmState state) {
    if (state == Idle) return;
    if (lastState_ != state) {
        GPIOE->BSRR = (0xff << 16); // reset all state leds
    
        switch (state) {
            case Forward:
                GPIOE->BSRR = (1 << LED_FORWARD);
                break;
            case Reverse:
                GPIOE->BSRR = (1 << LED_REVERSE);
                break;
            case Error:
                GPIOE->BSRR = (1 << LED_ERROR);
                break;
            default:
                break;
        }
    }

    // update counter leds 
    GPIOD->BSRR = (0xff << 16); // resette all counter leds

    GPIOD->BSRR = counter; // turn on counter leds

    lastState_ = state;
}

void gpio_ledD20_high() {
    GPIOE->BSRR = (1 << LED_OSC);
}

void gpio_ledD20_low() {
    GPIOE->BSRR = (1 << (LED_OSC + 16));
}
// EOF