#ifndef GPIOI_H
#define GPIO_H

#include <stdbool.h>
#include "fsmStates.h"
#include <stdint.h>

typedef enum {
    PHASE_A = 0, // 00 
    PHASE_D = 1, // 01 
    PHASE_B = 2, // 10 
    PHASE_C = 3  // 11
} Phase;


/*
*   returns the encoder input as a Phase
*/
Phase gpio_getPhase(void);

/*
*   checks if button S6 is pressed
*/
bool gpio_S6Pressed(void);

/*
*   updates all output leds depending on state of fsm
*   counter converted to first 8 bits
*/  
void gpio_output(uint8_t counter, FsmState state);

void gpio_ledD20_high();

void gpio_ledD20_low();

#endif
// EOF