#ifndef COMPUTING_H
#define COMPUTING_H
#include <stdint.h>

#define SLOTS 300

// calculate the rotational angle from counter for a 300 slots encoder
double computing_getRotationAngle(int counter);

// calculate the angular velocity from difference between phases and delta time
double computing_getAngleVelocity(int diffBetweenPhases, double dt);

#endif 
// EOF