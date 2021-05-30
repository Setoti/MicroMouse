#include "define_wakaba.h"
#include "led_and_sw.h"

// Turn on the Full color LED
void Full_color_LED(char color){
	switch(color){
	    case OFF:
	    	LED_RED   = LED_OFF;
	    	LED_BLUE  = LED_OFF;
	    	LED_GREEN = LED_OFF;
	    	break;
	    case RED:
	    	LED_RED   = LED_ON;
	    	LED_BLUE  = LED_OFF;
	    	LED_GREEN = LED_OFF;
	    	break;
	    case BLUE:
	    	LED_RED   = LED_OFF;
	    	LED_BLUE  = LED_ON;
	    	LED_GREEN = LED_OFF;
	    	break;
	    case PURPLE:
	    	LED_RED   = LED_ON;
	    	LED_BLUE  = LED_ON;
	    	LED_GREEN = LED_OFF;
	    	break;
	    case GREEN:
	    	LED_RED   = LED_OFF;
	    	LED_BLUE  = LED_OFF;
	    	LED_GREEN = LED_ON;
	    	break;
	    case YELLOW:
	    	LED_RED   = LED_ON;
	    	LED_BLUE  = LED_OFF;
	    	LED_GREEN = LED_ON;
	    	break;
	    case LIGHT_BLUE:
	    	LED_RED   = LED_OFF;
	    	LED_BLUE  = LED_ON;
	    	LED_GREEN = LED_ON;
	    	break;
	    case WHITE:
	    	LED_RED   = LED_ON;
	    	LED_BLUE  = LED_ON;
	    	LED_GREEN = LED_ON;
	    	break;
	    default:
	    	LED_RED   = LED_OFF;
	        LED_BLUE  = LED_OFF;
	    	LED_GREEN = LED_OFF;
	}
}

// Interrupt function
// check the status of SW
void SW_status_check(void){

	static unsigned char pre_sw_status = SW_OFF;

	// When sw changes from Off to On
	if(PUSH_SW==SW_ON && pre_sw_status==SW_OFF){
		g_sw_chg = 1;
	}

	pre_sw_status = PUSH_SW;
}
