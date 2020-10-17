/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */
 /*
 *  USBSTK5515 Definitions
 */

#define USBLDOCTRL           *( volatile ioport Uint16* )( 0x7004 )
#define CLKSTOP            *( volatile Uint16* )(0x1c3a) // CLKSTOP register 
#define PCGCR_H            *( volatile Uint16* )(0x1c03) // PERIPHERAL CLOCK GATING CONFIGURATION REGISTER
#define PSRCR              *( volatile Uint16* )(0x1c04) // Peripheral Software Reset Counter Register
#define PRCR               *( volatile Uint16* )(0x1c05) // Peripheral Reset Control Register
#define IVPD               *( volatile Uint16* )(0x0049) // Interrupt vector pointer DSP
#define IVPH               *( volatile Uint16* )(0x004A) // Interrupt vector pointer HOST
#define IER0               *( volatile Uint16* )(0x0000) // Interrupt mask register 0; in C5515 spec, it is also called IMR0 
#define IER1               *( volatile Uint16* )(0x0045) // Interrupt mask register 1; in C5515 spec, it is also called IMR1
#define IFR0               *( volatile Uint16* )(0x0001) // Interrupt flag register 0 
#define IFR1               *( volatile Uint16* )(0x0046) // Interrupt flag register 1  
#define USBSCR             *( volatile ioport Uint16* )(0x1c32) //USB system control Register
