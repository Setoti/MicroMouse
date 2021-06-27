#ifndef INTERFACE_H_
#define INTERFACE_H_

/*** type define ***/
typedef enum{
	C5 = 23900,
	D5 = 21282,
	E5 = 18960,
	F5 = 17896,
	G5 = 15943,
	A5 = 14204,
	B5 = 12654,
	C6 = 11944
} NOTE;

/*** Function Declaration ***/
void SW_CheckStat(void);
void SPK_CtrlCnt(void);
void SPK_Soundout(NOTE spk_note, unsigned char l_spk_cnt);

/*** Global variables ***/
extern volatile unsigned char g_sw_chg;

#endif /* LED_AND_INTERFACE_H_ */
