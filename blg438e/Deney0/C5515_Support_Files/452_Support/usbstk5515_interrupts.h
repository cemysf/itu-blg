/*
 * usbstk5515_interrupts.h
 *
 *  Created on: Jun 28, 2011
 *      Author: GSI
 */

#ifndef USBSTK5515_INTERRUPTS_H_
#define USBSTK5515_INTERRUPTS_H_

#define IER0		*(volatile Uint16*)(0x0000)//Interrupt Enable Register 0
#define IFR0		*(volatile Uint16*)(0x0001)//Interrupt Flag Register 0
#define IER1		*(volatile Uint16*)(0x0045)//Interrupt Enable Register 1
#define IFR1		*(volatile Uint16*)(0x0046)//Interrupt Flag Register 1
#define IVPD		*(volatile Uint16*)(0x0049)//Interrupt Vector Pointer table
#define IVPH		*(volatile Uint16*)(0x004A)//Interrupt Vector Pointer table continued

//Timer Interrupt Aggregated Flag Register
#define TIAFR		*(volatile ioport Uint16*)(0x1C14)

//General Purpose Timer 0
#define TCR0		*((ioport volatile Uint16*)0x1810)//Timer Control Register
#define TPR0_1		*((ioport volatile Uint16*)0x1812)//Timer Period Register 1
#define TPR0_2		*((ioport volatile Uint16*)0x1813)//Timer Period Register 2
#define TCR0_1		*((ioport volatile Uint16*)0x1814)//Timer Counter Register 1
#define TCR0_2		*((ioport volatile Uint16*)0x1815)//Timer Counter Register 2
#define T_INT_0		*((ioport volatile Uint16*)0x1816)//Timer Interrupts register

#define TINT   0x20
#define TINT_BIT 4

#define TIME_START  		0x8001
#define TIME_STOP   		0x8000
#define TIME_START_AUTOLOAD 0x8003

#define I2S_ISR_OFFSET  0x38
#define I2S_BIT_POS		0x7

#endif /* USBSTK5515_INTERRUPTS_H_ */
