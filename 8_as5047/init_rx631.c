#include "init_rx631.h"
#include "iodefine.h"
#include "spi.h"

/*** Function Declaration ***/
static void init_clock(void);
static void init_cmt0(void);
static void init_sci1(void);
static void init_rspi0(void);

/*---- RX631 Initialization ----*/
void init_rx631(void){
	SYSTEM.PRCR.WORD = 0xA503;  // Unprotect

	// MainCLK, SUBCLK and RTC Initialization
	init_clock();

	// CMT0 Initialization
	init_cmt0();

	// SCI1 Initialization
	init_sci1();

	// RSPI0 Initialization
	init_rspi0();

	SYSTEM.PRCR.WORD = 0xA500;  // Reprotect
}


/*---- MainCLK, SUBCLK and RTC Initialization ----*/
static void init_clock(void){
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
static void init_cmt0(void){

	MSTP(CMT0) = 0;          // CMT0 Module Stop Release

	CMT.CMSTR0.BIT.STR0 = 0; // CMT0 Stop
	CMT0.CMCR.WORD = 0x00C0; // interrupt enabled and PCLK/8
	CMT0.CMCOR = 6249;      // Set interrupt cycle to 1ms

	IPR(CMT0,CMI0) = 10;     // Priority Level 10
	IEN(CMT0,CMI0) = 1;      // Interrupt enabled

	CMT.CMSTR0.BIT.STR0 = 1; // CMT0 Start
}


/*---- SCI1 Initialization ----*/
static void init_sci1(void){

	MSTP(SCI1) = 0;             // SCI1 Module Stop Release

	MPC.PWPR.BIT.B0WI   = 0;    // PFSWE bit write enable
	MPC.PWPR.BIT.PFSWE  = 1;    // PmnPFS Register write enable
	MPC.P26PFS.BIT.PSEL = 0x0A; // set to TXD1
	MPC.PWPR.BYTE       = 0x80; // Reprotect
	PORT2.PMR.BIT.B6    = 1;    // set to Peripheral

	SCI1.SMR.BYTE       = 0x00; // PCLK/1, asynchronous,
	                            // 1 stop bit, no parity bit, data length=8bit
	SCI1.SEMR.BIT.ABCS  = 1;    // 1bit transfer in 8 cycles
	SCI1.BRR            = 80;   // 38400 bps, error=0.47%

	SCI1.SCR.BIT.TE     = 1;    // Enable serial transmission
}

/*---- RSPI0 Initialization ----*/
static void init_rspi0(void){

	MSTP(RSPI0) = 0;               //  RSPI0 Module Stop Release

	RSPI0.SPBR = 5;                //  521 kbps when BRDV=3

	RSPI0.SPSCR.BIT.SPSLN = 0;     //  Sequence length = 1
	RSPI0.SPDCR.BIT.SPFC  = 0;     //  Frame Num = 1
	RSPI0.SPDCR.BIT.SPLW  = 1;     //  Long Word Access

	/* RSPI Command Register0 */
	// CPHA = 1  : Data change at odd edges, data sample at even edges
	// CPOL = 0  : RSPCK at idle is LOW
	// BRDV = 3  : 8 divisions of the base bit rate
	// LSBF = 0  : MSB First
	// SPB  = 15 : Data length = 16bit
	RSPI0.SPCMD0.WORD = 0x0F0D;

	MPC.PWPR.BIT.B0WI     = 0;     // PFSWE bit write enable
	MPC.PWPR.BIT.PFSWE    = 1;     // PmnPFS Register write enable
	MPC.PC7PFS.BIT.PSEL   = 13;    // Set to MISOA
	MPC.PC6PFS.BIT.PSEL   = 13;    // Set to MOSIA
	MPC.PC5PFS.BIT.PSEL   = 13;    // Set to RSPCKA
	MPC.PWPR.BYTE         = 0x80;  // Reprotect
	PORTC.PMR.BIT.B7      = 1;     // set to Peripheral
	PORTC.PMR.BIT.B6      = 1;     // set to Peripheral
	PORTC.PMR.BIT.B5      = 1;     // set to Peripheral
	PORTB.PDR.BIT.B5      = 1;     // CS1: OUT
	PORTB.PODR.BIT.B5     = 1;     // CS1: HIGH

	RSPI0.SPCR.BIT.SPMS = 1;       // Clock synchronous operation
	RSPI0.SPCR.BIT.MSTR = 1;       // Master Mode
}
