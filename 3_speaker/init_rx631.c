#include "init_rx631.h"
#include "iodefine.h"

/*** Function Declaration ***/
static void init_clock(void);
static void init_cmt0(void);
static void init_cmt1(void);
static void init_mtu3(void);

/*---- RX631 Initialization ----*/
void init_rx631(void){
	SYSTEM.PRCR.WORD = 0xA503;  // Unprotect

	// MainCLK, SUBCLK and RTC Initialization
	init_clock();

	// CMT0 and CMT1 Initialization
	init_cmt0();
	init_cmt1();

	// MTU3 Initialization
	init_mtu3();

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
	RTC.RCR1.BYTE        = 0;       // Alarm interrupt disable
	while(RTC.RCR1.BYTE != 0);      // wait until RCR1=0x00
}


/*---- CMT0 Initialization ----*/
void init_cmt0(void){

	MSTP(CMT0) = 0;          // CMT0 Module Stop Release

	CMT.CMSTR0.BIT.STR0 = 0; // CMT0 Stop
	CMT0.CMCR.WORD = 0x00C1; // interrupt enabled and PCLK/512
	CMT0.CMCOR = 37499;      // Set interrupt cycle to 24ms

	IPR(CMT0,CMI0) = 10;     // Priority Level 10
	IEN(CMT0,CMI0) = 1;      // Interrupt enabled

	CMT.CMSTR0.BIT.STR0 = 1; // CMT0 Start
}

/*---- CMT1 Initialization ----*/
void init_cmt1(void){

	MSTP(CMT1) = 0;          // CMT1 Module Stop Release

	CMT.CMSTR0.BIT.STR1 = 0; // CMT1 Stop
	CMT1.CMCR.WORD = 0x00C1; // interrupt enabled and PCLK/32
	CMT1.CMCOR = 15624;      // Set interrupt cycle to 10ms

	IPR(CMT1,CMI1) = 9;      // Priority Level 9
	IEN(CMT1,CMI1) = 1;      // Interrupt enabled

	CMT.CMSTR0.BIT.STR1 = 1; // CMT1 Start
}

/*---- MTU3 Initialization ----*/
void init_mtu3(void){

	MSTP(MTU) = 0;              // MTU Module Stop Release

	MPC.PWPR.BIT.B0WI   = 0;    // PFSWE bit write enable
	MPC.PWPR.BIT.PFSWE  = 1;    // PmnPFS Register write enable
	MPC.P14PFS.BIT.PSEL = 0x01; // set to MTIOC3A
	MPC.PWPR.BYTE       = 0x80; // Reprotect
	PORT1.PMR.BIT.B4    = 1;    // set to Peripheral

    MTU3.TMDR.BIT.MD   = 0x2;   // PWM mode1
    MTU3.TIORH.BIT.IOA = 0x5;   // Initial output HIGH, Compare match LOW
    MTU3.TIORH.BIT.IOB = 0x6;   // Initial output HIGH, Compare match HIGH
	MTU3.TCR.BIT.TPSC  = 0x1;   // PCLK/4
	MTU3.TCR.BIT.CKEG  = 0x0;   // count by riging edge
	MTU3.TCR.BIT.CCLR  = 0x2;   // Clear by compare match TGRB
}
