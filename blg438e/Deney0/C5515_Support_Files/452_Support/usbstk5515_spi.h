/*
 * usbstk5515_spi.h
 *
 *  Created on: Jul 13, 2011
 *      Author: GSI
 */

#ifndef USBSTK5515_SPI_H_
#define USBSTK5515_SPI_H_

//SPI clock Divider Register
#define SPICDR	 *(volatile ioport Uint16*)(0x3000)
//SPI clock control register
#define SPICCR	 *(volatile ioport Uint16*)(0x3001)
//Device Configuration Register 1
#define SPIDCR1	 *(volatile ioport Uint16*)(0x3002)
//Device Configuration Register 2
#define SPIDCR2	 *(volatile ioport Uint16*)(0x3003)
//Command Register 1
#define SPICMD1	 *(volatile ioport Uint16*)(0x3004)
//Command Register 2
#define SPICMD2	 *(volatile ioport Uint16*)(0x3005)
//Status Register 1
#define SPISTAT1 *(volatile ioport Uint16*)(0x3006)
//Status Register 2
#define SPISTAT2 *(volatile ioport Uint16*)(0x3007)
//Data Register 1
#define SPIDAT1  *(volatile ioport Uint16*)(0x3008)
//Data Register 2
#define SPIDAT2  *(volatile ioport Uint16*)(0x3009)

#define SPI_OFFSET 0x98
#define SPI_BIT    0x3
//Above is for flag and enable registers 1

#endif /* USBSTK5515_SPI_H_ */
