#include "define_wakaba.h"
#include "spi.h"
#include "sci.h"

static u16 SPI_SendRecvAS5047(u32 packet);

/* Write to AS5047 register */
void SPI_WriteAS5047(u16 address, u16 data){
	u16 packet;
	u8  i;
	u8  parity=0;

	CS_AS5047 = ASSERT;  // Assert AS5047

	/* make packet */
	packet = address;
	for(i=0;i<15;i++)
		parity += (packet >> i) & 1;
	packet += (parity % 2) << 15;

    SPI_SendRecvAS5047(packet);  // Send Address

	CS_AS5047 = NEGATE;  // Negate AS5047

	for(i=0;i<10;i++)   // Wait 700ns
		__nop();

	CS_AS5047 = ASSERT;  // Assert AS5047

	/* make packet */
	packet = data;
	parity = 0;
	for(i=0;i<15;i++)
		parity += (packet >> i) & 1;
	packet += (parity % 2) << 15;

    SPI_SendRecvAS5047(packet);  // Send Data

	CS_AS5047 = NEGATE;  // Negate AS5047
}

/* Read AS5047 register */
u16 SPI_ReadAS5047(u16 address){
	u16 packet=0;
	u8  i;
	u8  parity=0;
	u16 data=0;

	CS_AS5047 = ASSERT;  // Assert AS5047

	/* make packet */
	packet = 0x4000 + address;
	for(i=0;i<15;i++)
		parity += (packet >> i) & 1;
	packet += (parity % 2) << 15;

    SPI_SendRecvAS5047(packet);  // Send Address

	CS_AS5047 = NEGATE;  // Negate AS5047

	for(i=0;i<10;i++)   // Wait 700ns
		__nop();

	CS_AS5047 = ASSERT;  // Assert AS5047

	/* make packet */
	packet = 0xC000;

    data = SPI_SendRecvAS5047(packet);  // Receive Data

	CS_AS5047 = NEGATE;  // Negate AS5047

	return data;
}

/* Sending/receiving data */
static u16 SPI_SendRecvAS5047(u32 packet){
	u16 data;

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

	return data;
}
