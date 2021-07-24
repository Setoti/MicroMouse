#include "define_wakaba.h"
#include "interface.h"
#include "iodefine.h"

#define NSLEEP       PORT1.PODR.BIT.B5
#define M_PHASE_R    PORTB.PODR.BIT.B0
#define M_PHASE_L    PORTE.PODR.BIT.B4
#define MOTOR_START  MTU.TSTR.BIT.CST4

void main(void){
	unsigned char status = 0;

	init_rx631(); // Overall Initialization
	NSLEEP = 1;   // Sleep mode stop

	while(1){
		if(g_sw_chg){   // Enter when SW is pressed
			g_sw_chg = 0;
			if(status==0){  // Rotate motor
				M_PHASE_R = 0;
				MTU4.TGRA = 249;   // Duty M_ENBL_R
				MTU4.TGRC = 249;   // Duty M_ENBL_L
				MOTOR_START = 1;
				status = 1;
			}
			else if(status==1){  // Reverse rotation of motor
				M_PHASE_R = 1;
				status = 2;
			}
			else if(status==2){  // Motor Stop
				MTU4.TGRA = 500;   // Duty M_ENBL_R
				MTU4.TGRC = 500;   // Duty M_ENBL_L
				status = 0;
			}
		}
	}
}
