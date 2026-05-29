#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"

#include "fsm.h"


int main(void) {
	initITSboard();    // initialization of the board
	
	GUI_init(DEFAULT_BRIGHTNESS);   // initialization of the boards LCD
	TP_Init(false);                 // disable touch
	
	fsm_run();
}

// EOF
