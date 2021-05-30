#include "init_rx631.h"
#include "iodefine.h"

/*** Function Declaration ***/
static void init_clock(void);
static void init_IO(void);
static void init_cmt0(void);

/*---- RX631 Initialization ----*/
void init_rx631(void){
	SYSTEM.PRCR.WORD = 0xA503;  // Unprotect

	// MainCLK, SUBCLK and RTC Initialization
	init_clock();

	// I/O setting
	init_IO();

	// CMT0 Initialization
	init_cmt0();

	SYSTEM.PRCR.WORD = 0xA500;  // Reprotect
}


/*---- MainCLK, SUBCLK and RTC Initialization ----*/
void init_clock(void){
	unsigned short i=0;

	// SUBCLK Initialization
	SYSTEM.SOSCCR.BIT.SOSTP = 1;    // Sub CLK STOP
	while(SYSTEM.SOSCCR.BIT.SOSTP != 1); // Wait until SOSTP=1
	RTC.RCR3.BIT.RTCEN      = 0;    // Sub CLK STOP
	while(RTC.RCR3.BIT.RTCEN != 0); // Wait until RTCEN=0

	// Main CLK setting
	RTC.RCR4.BIT.RCKSEL     = 1;    // Select main CLK as count source
	SYSTEM.MOSCCR.BIT.MOSTP = 0;    // Main CLK ON
	for(i=0;i<1000;i++);            // Wait about 50ms

	// SYSTEM CLK setting
	SYSTEM.PLLCR.BIT.PLIDIV = 0x0;  // Main CLK divided by 1
	SYSTEM.PLLCR.BIT.STC    = 0x13; // Main CLK multiplied by 20
	SYSTEM.PLLCR2.BIT.PLLEN = 0;    // PLL Enable
	for(i=0;i<1000;i++);            // wait about 50ms
	// FCK: 4div, ICK:  2div, BCK:  stop, SDCLK stop,
	// BCK: 4div, PCKA: 2div, PCKB: 4div
	SYSTEM.SCKCR.LONG       = 0x21C21211;
	SYSTEM.SCKCR3.BIT.CKSEL = 0x4;  // Select PLL as CLK source
	SYSTEM.LOCOCR.BIT.LCSTP = 1;    // LOCO stop

	// RTC stop and reset
	RTC.RCR2.BIT.START      = 0;    // RTC stop
	while(RTC.RCR2.BIT.START != 0); // Wait until START=0
	RTC.RCR2.BIT.RESET      = 1;    // RTC reset
	while(RTC.RCR2.BIT.RESET != 0); // Wait until RESET=0

	// Disable RTC interrupt requests
	RTC.RCR1.BYTE        = 0;    // Alarm interrupt disable
	while(RTC.RCR1.BYTE != 0);   // wait until RCR1=0x00
}

/*---- I/O Initialization ----*/
void init_IO(void){

	PORT1.PMR.BIT.B7 = 0;  // LED_Red:   I/O
	PORT2.PMR.BIT.B7 = 0;  // LED_Green: I/O
	PORTE.PMR.BIT.B3 = 0;  // LED_Blue:  I/O
	PORT3.PMR.BIT.B5 = 0;  // PUSH_SW:   I/O

	PORT1.PODR.BIT.B7 = 1; // LED_Red:   HIGH
	PORT2.PODR.BIT.B7 = 1; // LED_Green: HIGH
	PORTE.PODR.BIT.B3 = 1; // LED_Blue:  HIGH

	PORT1.PDR.BIT.B7 = 1;  // LED_Red:   Out
	PORT2.PDR.BIT.B7 = 1;  // LED_Green: Out
	PORTE.PDR.BIT.B3 = 1;  // LED_Blue:  Out
}

/*---- CMT0 Initialization ----*/
void init_cmt0(void){

	MSTP(CMT0) = 0; // CMT0 Module Stop Release

	CMT.CMSTR0.BIT.STR0 = 0; // CMT0 Stop
	CMT0.CMCR.WORD = 0x00C1; // interrupt enabled and PCLK/32
	CMT0.CMCOR = 37499;      // Set interrupt cycle to 24ms

	IPR(CMT0,CMI0) = 10; // Priority Level 10
	IEN(CMT0,CMI0) = 1;  // Interrupt enabled

	CMT.CMSTR0.BIT.STR0 = 1; // CMT0 Start
}
