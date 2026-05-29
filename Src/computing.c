#include <stdint.h>
#define DEGREES_PER_STEP (360.0 / 1200.0)

double computing_getRotationAngle(int counter){
    double angle = counter * DEGREES_PER_STEP;
    return angle;
}

double computing_getAngleVelocity(int diffBetweenPhases, double dt){ 
    double velocity = (diffBetweenPhases * 0.3 ) / dt;
    return velocity;
}
// EOF