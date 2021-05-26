#include "init_rx631.h"
#include "iodefine.h"

void init_rx631(void){
	unsigned short i=0;
	SYSTEM.PRCR.WORD = 0xA503;  // Unprotect

	/*---- SUBCLK and RTC Initialization ----*/
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
	RTC.RCR1.BYTE        = 0x00;    // Alarm interrupt disable
	while(RTC.RCR1.BYTE != 0x00);   // wait until PIE=0
	/*---- End of SUBCLK and RTC Initialization ----*/

	// I/O setting
	PORT1.PDR.BIT.B7 = 1;  // LED_Red:   Out
	PORT2.PDR.BIT.B7 = 1;  // LED_Green: Out
	PORTE.PDR.BIT.B3 = 1;  // LED_Blue:  Out

	PORT1.PODR.BIT.B7 = 1; // LED_Red:   HIGH
	PORT2.PODR.BIT.B7 = 1; // LED_Green: HIGH
	PORTE.PODR.BIT.B3 = 1; // LED_Blue:  HIGH

	PORT1.PMR.BIT.B7 = 0;  // LED_Red:   I/O
	PORT2.PMR.BIT.B7 = 0;  // LED_Green: I/O
	PORTE.PMR.BIT.B3 = 0;  // LED_Blue:  I/O

	SYSTEM.PRCR.WORD = 0xA500;  // Reprotect
}
