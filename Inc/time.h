#ifndef TIME_H
#define TIME_H

#define TICKS_PER_SEC 90000000 // the timer ticks  90-millionen times per second

#include <stdint.h>

// init the timer register, which is a given module from my uni 
void time_initTimer();

// get a timestamp
uint32_t time_getTimeStamp();

//  return the delta between 2 timestamps
double time_getDt(uint32_t t2, uint32_t t1);

#endif
// EOF