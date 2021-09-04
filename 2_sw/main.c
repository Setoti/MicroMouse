#include "define_wakaba.h"
#include "led_and_sw.h"

void main(void){
	unsigned char led_color = 0;

	init_rx631();
	while(1){
		if(g_sw_chg){
			led_color++;
			led_color = led_color & 0x07;
			Full_color_LED(led_color);
			g_sw_chg = 0;
		}
	}
}
