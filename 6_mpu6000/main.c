#include "sci.h"
#include "spi.h"
#include "init_rx631.h"
#include "define_wakaba.h"

extern volatile unsigned char g_flag;

void main(void){
	int angle_Z=0;
	u16 cnt=0;
	int send_data;
	short rd_data;

	init_rx631();       // Overall Initialization

	while(1){
		if(g_flag){
			g_flag = 0;  // Clear flag

			// Read angular velocity
			rd_data = SPI_ReadMPU6000(MPU6000_GYRO_ZOUT_H);
			angle_Z += rd_data;

			cnt++;
			if(cnt==100){
				cnt=0;
				send_data = angle_Z / 16384;  // (angle_Z*2000) / (32768*1000)
				sci_printf("%l\r\n", send_data);
			}
		}
	}
}
