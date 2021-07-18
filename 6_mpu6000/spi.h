#ifndef SPI_H_
#define SPI_H_

#include "iodefine.h"
#include "define_wakaba.h"

#define MPU6000_GYRO_CONFIG  27
#define MPU6000_GYRO_ZOUT_H  71
#define MPU6000_GYRO_ZOUT_L  72
#define MPU6000_USER_CTRL   106
#define MPU6000_PWR_MGMT_1  107
#define MPU6000_WHO_AM_I    117

#define LENGTH_16BIT  15
#define LENGTH_24BIT   1

#define ASSERT 0
#define NEGATE 1

#define CS_MPU6000  PORT1.PODR.BIT.B6

void SPI_WriteMPU6000(u8 address, u8 data);
u16 SPI_ReadMPU6000(u8 address);

#endif /* SPI_H_ */
