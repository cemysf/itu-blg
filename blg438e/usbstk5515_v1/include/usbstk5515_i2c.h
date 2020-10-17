/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  I2C header file
 *
 */

#ifndef I2C_
#define I2C_

#include "usbstk5515.h"

#define MDR_STT			0x2000
#define MDR_TRX			0x0200
#define MDR_MST			0x0400
#define MDR_IRS			0x0020
#define MDR_FREE		0x4000
#define STR_XRDY		0x0010
#define STR_RRDY		0x0008
#define MDR_STP 		0x0800
/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_I2C_init ( );
Int16 USBSTK5515_I2C_close( );
Int16 USBSTK5515_I2C_read( Uint16 i2c_addr, Uint8* data, Uint16 len );
Int16 USBSTK5515_I2C_write( Uint16 i2c_addr, Uint8* data, Uint16 len );

#endif
