/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  Switch Test
 *
 */

#include "usbstk5515.h"
#include "usbstk5515_led.h"
#include "sar.h"

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  switch_test( )                                                             *
 *      Running Eight LED test                                              *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 switch_test( )
{
    Int16 key;
    
    SYS_EXBUSSEL = 0x6000;  // Enable LEDs on external bus
    /* Initialize SAR ADC */
    Init_SAR();
    USBSTK5515_ULED_init( );
    
    /* Infinite loop to accept switch inputs */
    while(1)
    {
    	key = Get_Sar_Key();
    	if((key == SW1))   // If SW1 pressed
    	{
    		USBSTK5515_ULED_toggle( 0 );  // Toggle DS2 (GREEN LED)
    	}
    	if((key == SW2))   // If SW2 pressed
    	{
    		USBSTK5515_ULED_toggle( 3 );  // Toggle DS5 (BLUE LED)
    	}
    	if((key == SW12))   // If SW1 and SW2 pressed
    	{
    		USBSTK5515_ULED_toggle( 1 );  // Toggle DS3 (RED LED)
    		USBSTK5515_ULED_toggle( 2 );  // Toggle DS4 (YELLOW LED)
    	}
    }
    
    return 0;
}
