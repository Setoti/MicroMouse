#include "interface.h"
#include "sci.h"
#include "init_rx631.h"
#include "iodefine.h"

void main(void){
	unsigned short voltage;

	init_rx631();       // Overall Initialization

	while(1){
		if(g_sw_chg){   // Enter when SW is pressed
			g_sw_chg = 0;
			S12AD.ADCSR.BIT.ADST = 1;         // ADC start
			while(S12AD.ADCSR.BIT.ADST==1);   // wait for ADC completion
			voltage = S12AD.ADDR9*330*2/4095; // Convert to voltage
			sci_printf("voltage = %u.%u\n\r",voltage/100,voltage%100);
		}
	}
}
