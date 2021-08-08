#ifndef SPI_H_
#define SPI_H_

#include "iodefine.h"
#include "define_wakaba.h"

#define LENGTH_16BIT  15
#define LENGTH_24BIT   1

#define AS5047_SETTINGS1 0x0018
#define AS5047_SETTINGS2 0x0019
#define AS5047_ANGLE     0x3FFE

#define ASSERT 0
#define NEGATE 1

#define CS_AS5047	PORTB.PODR.BIT.B5

void SPI_WriteAS5047(u16 address, u16 data);
u16 SPI_ReadAS5047(u16 address);

#endif /* SPI_H_ */
