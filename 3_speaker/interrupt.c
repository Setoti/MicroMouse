#include "interface.h"
#pragma section P PIntPRG

/*** Function Declaration ***/
static void CMT0_CMI0(void);  // CMT0 CMI0

// CMT0 CMI0
// Check the status of the switch
#pragma interrupt (CMT0_CMI0(vect=28))
void CMT0_CMI0(void){
	SW_CheckStat();
}

// CMT1 CMI1
#pragma interrupt (CMT1_CMI1(vect=29))
void CMT1_CMI1(void){
	SPK_CtrlCnt();
}
