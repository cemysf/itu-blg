/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  LED header file
 *
 */

#ifndef LED_
#define LED_

#include "usbstk5515.h"

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_LED_init  ( );
Int16 USBSTK5515_LED_on    ( Uint16 number );
Int16 USBSTK5515_LED_off   ( Uint16 number );

Int16 USBSTK5515_ULED_init( );
Int16 USBSTK5515_ULED_getall( Uint16 *pattern );
Int16 USBSTK5515_ULED_setall( Uint16 pattern );
Int16 USBSTK5515_ULED_on( Uint16 number );
Int16 USBSTK5515_ULED_off( Uint16 number );
Int16 USBSTK5515_ULED_toggle( Uint16 number );

#endif
