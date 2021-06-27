#include "define_wakaba.h"
#include "interface.h"
#include "iodefine.h"

volatile unsigned char g_sw_chg;
static volatile unsigned char spk_cnt;

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

// CMT1 CMI1 Interrupt function
// Control soundout time
void SPK_CtrlCnt(void){

	// Reduce the count
	spk_cnt--;
	// Stop square wave output
	if(spk_cnt==0){
		MTU.TSTR.BIT.CST3 = 0;
		MTU3.TCNT = 0;
	}
}

// Speaker Sound output
void SPK_Soundout(NOTE spk_note, unsigned char l_spk_cnt){
	spk_cnt = l_spk_cnt;
	MTU3.TGRA = spk_note>>2;
	MTU3.TGRB = spk_note;
	MTU.TSTR.BIT.CST3 = 1;
}
