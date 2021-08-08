#include "sci.h"
#include "spi.h"
#include "init_rx631.h"
#include "define_wakaba.h"

extern volatile unsigned char g_flag;

void main(void){
	unsigned short rd_data;
	unsigned short data;

	init_rx631();       // Overall Initialization

	while(1){
		if(g_flag){
			g_flag = 0;  // Clear flag

			// Read angular velocity
			rd_data = SPI_ReadAS5047(AS5047_ANGLECOM);
			data = (rd_data & 0x3FFF) * 360 / 16384;
			sci_printf("%u\r\n", data);
		}
	}
}
