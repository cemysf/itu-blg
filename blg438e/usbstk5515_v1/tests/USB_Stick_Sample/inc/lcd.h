/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  LCD Header file
 *
 */
 
/* ------------------------------------------------------------------------ *
 *  LCD Module Registers                                                    *
 * ------------------------------------------------------------------------ */
 
#define LCD_LCDREVMIN           *(volatile ioport Uint16*)(0x2E00) // LCD Minor Revision Register
#define LCD_LCDREVMAJ           *(volatile ioport Uint16*)(0x2E01) // LCD Major Revision Register
#define LCD_LCDCR               *(volatile ioport Uint16*)(0x2E04) // LCD Control Register
#define LCD_LCDSR               *(volatile ioport Uint16*)(0x2E08) // LCD Status Register
#define LCD_LCDLIDDCR           *(volatile ioport Uint16*)(0x2E0C) // LCD LIDD Control Register
#define LCD_LCDLIDDCS0CONFIG0   *(volatile ioport Uint16*)(0x2E10) // LCD LIDD CS0 Configuration Register 0
#define LCD_LCDLIDDCS0CONFIG1   *(volatile ioport Uint16*)(0x2E11) // LCD LIDD CS0 Configuration Register 1
#define LCD_LCDLIDDCS0ADDR      *(volatile ioport Uint16*)(0x2E14) // LCD LIDD CS0 Address Read/Write Section Register
#define LCD_LCDLIDDCS0DATA      *(volatile ioport Uint16*)(0x2E18) // LCD LIDD CS0 Data Read/Write Register
#define LCD_LCDLIDDCS1CONFIG0   *(volatile ioport Uint16*)(0x2E1C) // LCD LIDD CS1 Configuration Register 0
#define LCD_LCDLIDDCS1CONFIG1   *(volatile ioport Uint16*)(0x2E1D) // LCD LIDD CS1 Configuration Register
#define LCD_LCDLIDDCS1ADDR      *(volatile ioport Uint16*)(0x2E20) // LCD LIDD CS1 Address Read/Write Register
#define LCD_LCDLIDDCS1DATA      *(volatile ioport Uint16*)(0x2E24) // LCD LIDD CS1 Data Read/Write Register
#define LCD_LCDDMACR            *(volatile ioport Uint16*)(0x2E40) // LCD DMA Control Register
#define LCD_LCDDMAFB0BAR0       *(volatile ioport Uint16*)(0x2E44) // LCD DMA Frame Buffer 0 Base Address Register 0
#define LCD_LCDDMAFB0BAR1       *(volatile ioport Uint16*)(0x2E45) // LCD DMA Frame Buffer 0 Base Address Register 1
#define LCD_LCDDMAFB0CAR0       *(volatile ioport Uint16*)(0x2E48) // LCD DMA Frame Buffer 0 Ceiling Address Register 0
#define LCD_LCDDMAFB0CAR1       *(volatile ioport Uint16*)(0x2E49) // LCD DMA Frame Buffer 0 Ceiling Address Register 1
#define LCD_LCDDMAFB1BAR0       *(volatile ioport Uint16*)(0x2E4C) // LCD DMA Frame Buffer 1 Base Address Register 0
#define LCD_LCDDMAFB1BAR1       *(volatile ioport Uint16*)(0x2E4D) // LCD DMA Frame Buffer 1 Base Address Register 1
#define LCD_LCDDMAFB1CAR0       *(volatile ioport Uint16*)(0x2E50) // LCD DMA Frame Buffer 1 Ceiling Address Register 0
#define LCD_LCDDMAFB1CAR1       *(volatile ioport Uint16*)(0x2E51) // LCD DMA Frame Buffer 1 Ceiling Address Register 1

