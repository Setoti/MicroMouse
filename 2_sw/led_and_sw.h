#ifndef LED_AND_SW_H_
#define LED_AND_SW_H_

/*** Function Declaration ***/
void Full_color_LED(char color);
void SW_status_check(void);

/*** Global variables ***/
extern volatile unsigned char g_sw_chg;

enum COLOR{
	OFF,
	RED,
	BLUE,
	PURPLE,
	GREEN,
	YELLOW,
	LIGHT_BLUE,
	WHITE
};

#define LED_ON   0
#define LED_OFF  1
#define SW_ON  0
#define SW_OFF 1

#endif /* LED_AND_SW_H_ */
