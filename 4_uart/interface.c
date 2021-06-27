#include "define_wakaba.h"
#include "interface.h"
#include "iodefine.h"

volatile unsigned char g_sw_chg;

// CMT0 CMI0 Interrupt function
// check the status of SW
void SW_CheckStat(void){
	static unsigned char pre_sw_status = SW_OFF;

	// When sw changes from Off to On
	if(PUSH_SW==SW_ON && pre_sw_status==SW_OFF){
		g_sw_chg = 1;
	}

	pre_sw_status = PUSH_SW;
}
