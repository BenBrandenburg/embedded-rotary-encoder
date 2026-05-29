#ifndef DISPLAY_H
#define DISPLAY_H

// start the main display output
void display_start();

// update the display buffer 
void display_updateBuffer(double angle ,double velocity);

// print one character from the display buffer 
void display_update();

#endif
// EOF