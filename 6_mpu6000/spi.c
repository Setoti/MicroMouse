#include "define_wakaba.h"
#include "spi.h"
#include "sci.h"

static u16 SPI_SendRecvMPU6000(u32 packet);

/* Write to MPU6000 register */
void SPI_WriteMPU6000(u8 address, u8 data){
	u16 packet;

	/* make packet */
	packet = address << 8;
	packet |= data;

	/* Number of data to send = 16bit */
	RSPI0.SPCMD0.BIT.SPB = LENGTH_16BIT;

    SPI_SendRecvMPU6000(packet);  // Write
}

/* Read MPU6000 register */
u16 SPI_ReadMPU6000(u8 address){
	u16 data;
	u32 packet;

	/* make packet */
	packet = 0x800000;
	packet |= address << 16;

	/* Number of data to send = 24bit */
	RSPI0.SPCMD0.BIT.SPB = LENGTH_24BIT;

	data = SPI_SendRecvMPU6000(packet);  // Read

	return data;
}

/* Sending/receiving data to/from MPU6000 */
static u16 SPI_SendRecvMPU6000(u32 packet){
	u16 data;

	CS_MPU6000 = ASSERT;   // Assert MPU6000 CS

	RSPI0.SPCR.BIT.SPTIE  = 1;  // Enable transmission IRQ
	RSPI0.SPCR.BIT.SPE    = 1;  // Enable RSPI

	/* Wait for the send buffer to be empty */
	while(IR(RSPI0, SPTI0)==0);
	IR(RSPI0, SPTI0)=0;         // Clear Flag

	RSPI0.SPDR.LONG = packet;   // Send data

	RSPI0.SPCR.BIT.SPTIE  = 0;  // Disable transmission IRQ
	RSPI0.SPCR2.BIT.SPIIE = 1;  // Enable idle IRQ
	RSPI0.SPCR.BIT.SPRIE  = 1;  // Enable receive IRQ

	/* Wait for RSPI to idle */
	while(IR(RSPI0, SPII0)==0);
	IR(RSPI0, SPII0)=0;         // Clear Flag

	/* Wait for the receive buffer to be written */
	while(IR(RSPI0, SPRI0)==0);
	IR(RSPI0, SPRI0)=0;         // Clear Flag

	data = RSPI0.SPDR.LONG & 0xFFFF;

	RSPI0.SPCR2.BIT.SPIIE = 0;  // Enable idle IRQ
	RSPI0.SPCR.BIT.SPRIE  = 0;  // Enable receive IRQ
	RSPI0.SPCR.BIT.SPE    = 0;  // Disable RSPI

	CS_MPU6000 = NEGATE;  // Negate MPU6000 CS

	return data;
}
