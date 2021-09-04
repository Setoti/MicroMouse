#include "led_and_sw.h"
#pragma section P PIntPRG

/*** Function Declaration ***/
static void CMT0_CMI0(void);  // CMT0 CMI0

// CMT0 CMI0
// Check the status of the switch
#pragma interrupt (CMT0_CMI0(vect=28))
void CMT0_CMI0(void){
	SW_status_check();
}
