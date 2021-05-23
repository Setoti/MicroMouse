#include "define_wakaba.h"

void main(void){
	unsigned short i=0;
	unsigned short j=0;

	init_rx631();
	while(1){
		LED_RED = LED_ON;
		for(i=0;i<10000;i++)
			for(j=0;j<100;j++);
		LED_RED = LED_OFF;
		for(i=0;i<10000;i++)
			for(j=0;j<100;j++);
	}
}

