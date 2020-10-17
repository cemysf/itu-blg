/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  OSD9616 OLED Test
 *
 */

#include"usbstk5515.h"
#include"usbstk5515_i2c.h"
#include"lcd.h"
#include "usbstk5515_gpio.h"

#define OSD9616_I2C_ADDR 0x3C    // OSD9616 I2C address

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Int16 OSD9616_send( Uint16 comdat, Uint16 data )                        *
 *                                                                          *
 *      Sends 2 bytes of data to the OSD9616                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 OSD9616_send( Uint16 comdat, Uint16 data )
{
    Uint8 cmd[2];
    cmd[0] = comdat & 0x00FF;     // Specifies whether data is Command or Data
    cmd[1] = data;                // Command / Data

    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 2 );
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Int16 OSD9616_multiSend( Uint16 comdat, Uint16 data )                   *
 *                                                                          *
 *      Sends multiple bytes of data to the OSD9616                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 OSD9616_multiSend( Uint8* data, Uint16 len )
{
    Uint16 x;
    Uint8 cmd[10];
    for(x=0;x<len;x++)               // Command / Data
    {
    	cmd[x] = data[x];
    }
    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, len );
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Int16 printLetter(Uint16 l1,Uint16 l2,Uint16 l3,Uint16 l4)              *
 *                                                                          *
 *      Send 4 bytes representing a Character                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 printLetter(Uint16 l1,Uint16 l2,Uint16 l3,Uint16 l4)
{
	OSD9616_send(0x40,l1);
    OSD9616_send(0x40,l2);
    OSD9616_send(0x40,l3);
    OSD9616_send(0x40,l4);
    OSD9616_send(0x40,0x00);
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Int16 oled_test()                                                       *
 *                                                                          *
 *      Testing function for the OSD9616 display                            *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 oled_test()
{
	Int16 i, i2c_err;
	Uint8 cmd[10];    // For multibyte commands
	
	/* Initialize I2C */
    USBSTK5515_I2C_init( );
    
    /* Initialize LCD power */
    USBSTK5515_GPIO_setDirection( 12, 1 );  // Output
    USBSTK5515_GPIO_setOutput( 12, 1 );     // Enable 13V 
    
    /* Initialize OSD9616 display */
    i2c_err = OSD9616_send(0x00,0x00); // Set low column address
    i2c_err = OSD9616_send(0x00,0x10); // Set high column address
    if(i2c_err)  // Don't setup display if not connected
        return 1;
    
    OSD9616_send(0x00,0x40); // Set start line address

    cmd[0] = 0x00 & 0x00FF;  // Set contrast control register
    cmd[1] = 0x81;
    cmd[2] = 0x7f;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xa1); // Set segment re-map 95 to 0
    OSD9616_send(0x00,0xa6); // Set normal display

    cmd[0] = 0x00 & 0x00FF;  // Set multiplex ratio(1 to 16)
    cmd[1] = 0xa8; 
    cmd[2] = 0x0f;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xd3); // Set display offset
    OSD9616_send(0x00,0x00); // Not offset
    OSD9616_send(0x00,0xd5); // Set display clock divide ratio/oscillator frequency
    OSD9616_send(0x00,0xf0); // Set divide ratio

    cmd[0] = 0x00 & 0x00FF;  // Set pre-charge period
    cmd[1] = 0xd9;
    cmd[2] = 0x22;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    cmd[0] = 0x00 & 0x00FF;  // Set com pins hardware configuration
    cmd[1] = 0xda;
    cmd[2] = 0x02;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xdb); // Set vcomh
    OSD9616_send(0x00,0x49); // 0.83*vref
    
    cmd[0] = 0x00 & 0x00FF;  //--set DC-DC enable
    cmd[1] = 0x8d;
    cmd[2] = 0x14;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xaf); // Turn on oled panel    
    
    /* Fill page 0 */ 
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    for(i=0;i<128;i++)
    {
    	OSD9616_send(0x40,0xff);
    }
    /* Write to page 0 */
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    for(i=0;i<22;i++)
    {
    	OSD9616_send(0x40,0x00);  // Spaces
    }
    printLetter(0x32,0x49,0x49,0x26);  // S
    printLetter(0x01,0x7F,0x01,0x01);  // T
    printLetter(0x7F,0x30,0x0E,0x7F);  // N
    printLetter(0x41,0x49,0x49,0x7F);  // E
    printLetter(0x7F,0x06,0x06,0x7F);  // M
    printLetter(0x3F,0x40,0x40,0x3F);  // U
    printLetter(0x46,0x29,0x19,0x7F);  // R
    printLetter(0x01,0x7F,0x01,0x01);  // T
    printLetter(0x32,0x49,0x49,0x26);  // S
    printLetter(0x7F,0x30,0x0E,0x7F);  // N
    printLetter(0x00,0x7F,0x00,0x00);  // I
    for(i=0;i<5;i++)
    {
    	OSD9616_send(0x40,0x00);  // Spaces
    }
    printLetter(0x32,0x49,0x49,0x26);  // S
    printLetter(0x7C,0x09,0x0A,0x7C);  // A
    printLetter(0x63,0x1C,0x1C,0x63);  // X
    printLetter(0x41,0x49,0x49,0x7F);  // E
    printLetter(0x01,0x7F,0x01,0x01);  // T    
    
    for(i=0;i<23;i++)
    {
    	OSD9616_send(0x40,0x00);  // Spaces
    }
    /* Fill page 1*/ 
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    for(i=0;i<128;i++)
    {
    	OSD9616_send(0x40,0xff);
    }
    
    /* Write to page 1*/ 
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    for(i=0;i<20;i++)
    {
    	OSD9616_send(0x40,0x00);
    }
    printLetter(0x41,0x22,0x14,0x7F);  // K
    printLetter(0x22,0x41,0x41,0x3E);  // C
    printLetter(0x00,0x7F,0x00,0x00);  // I
    printLetter(0x01,0x7F,0x01,0x01);  // T
    printLetter(0x32,0x49,0x49,0x26);  // S
    for(i=0;i<5;i++)
    {
    	OSD9616_send(0x40,0x00);  // Spaces
    }
    printLetter(0x36,0x49,0x49,0x7F);  // B
    printLetter(0x32,0x49,0x49,0x26);  // S
    printLetter(0x3F,0x40,0x40,0x3F);  // U
    for(i=0;i<5;i++)
    {
    	OSD9616_send(0x40,0x00);  // Spaces
    }
   	printLetter(0x06,0x09,0x09,0x7F);  // P
    printLetter(0x32,0x49,0x49,0x26);  // S
    printLetter(0x3E,0x41,0x41,0x7F);  // D	
    printLetter(0x43,0x4D,0x51,0x61);  // Z
    printLetter(0x10,0x58,0x58,0x30);  // e
    for(i=0;i<5;i++)
    {
    	OSD9616_send(0x40,0x00);  // Spaces
    }
    printLetter(0x31,0x49,0x49,0x2F);  // 5
   	printLetter(0x00,0x7F,0x00,0x00);  // 1
    printLetter(0x31,0x49,0x49,0x2F);  // 5
   	printLetter(0x31,0x49,0x49,0x2F);  // 5
    printLetter(0x22,0x41,0x41,0x3E);  // C

    for(i=0;i<23;i++)
    {
    	OSD9616_send(0x40,0x00);       // Spaces
    }
    /* Set vertical and horizontal scrolling */
    cmd[0] = 0x00;
    cmd[1] = 0x29;  // Vertical and Right Horizontal Scroll
    cmd[2] = 0x00;  // Dummy byte
    cmd[3] = 0x00;  // Define start page address
    cmd[4] = 0x03;  // Set time interval between each scroll step
    cmd[5] = 0x01;  // Define end page address
    cmd[6] = 0x01;  // Vertical scrolling offset
    OSD9616_multiSend( cmd, 7 );
    OSD9616_send(0x00,0x2f);
    /* Keep first 8 rows from vertical scrolling  */
    cmd[0] = 0x00;
    cmd[1] = 0xa3;  // Set Vertical Scroll Area
    cmd[2] = 0x08;  // Set No. of rows in top fixed area
    cmd[3] = 0x08;  // Set No. of rows in scroll area
    OSD9616_multiSend( cmd, 4 );

	return 0;
}
