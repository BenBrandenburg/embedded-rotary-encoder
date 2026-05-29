#include "time.h"
#include "timer.h" 

void time_initTimer() {
    initTimer();
}

uint32_t time_getTimeStamp() {
    return getTimeStamp();
}

double time_getDt(uint32_t t2, uint32_t t1) {
    uint32_t diff = t2 - t1;
    return (double) diff / TICKS_PER_SEC;
}
// EOF