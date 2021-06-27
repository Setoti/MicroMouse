#include "interface.h"
#include "sci.h"
#include "init_rx631.h"

void main(void){

	init_rx631();       // Overall Initialization

	while(1){
		if(g_sw_chg){   // Enter when SW is pressed
			g_sw_chg = 0;
			sci_printf("Hello World\n\r");
		}
	}
}
