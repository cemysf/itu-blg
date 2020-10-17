/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  LED implementation
 *
 */

#include "usbstk5515.h"
#include "usbstk5515_gpio.h"
#include "usbstk5515_led.h"

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USBSTK5515_LED_init( )                                                  *
 *                                                                          *
 *      Clear LEDs                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_LED_init( )
{
    /* Turn OFF all LEDs */
    return USBSTK5515_LED_off( 0 );
}


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USBSTK5515_LED_on( number )                                             *
 *                                                                          *
 *      number <- 0                                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_LED_on(Uint16 number)
{
	asm(" bset XF");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USBSTK5515_LED_off( number )                                            *
 *                                                                          *
 *      number <- 0                                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */

Int16 USBSTK5515_LED_off(Uint16 number)
{
	asm(" bclr XF");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _ULED_init( )                                                           *
 *                                                                          *
 *      Initialize User LEDs DS2 - DS5                                      *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_ULED_init( )
{
    /* Enable LED Outputs */
    
    USBSTK5515_GPIO_setDirection( 14, GPIO_OUT );  // DS1
    USBSTK5515_GPIO_setDirection( 15, GPIO_OUT );  // DS2
    USBSTK5515_GPIO_setDirection( 16, GPIO_OUT );  // DS3
    USBSTK5515_GPIO_setDirection( 17, GPIO_OUT );  // DS4

    /* Turn OFF all LEDs */
    return USBSTK5515_ULED_setall( 0x0F );
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _ULED_getall( pattern )                                                 *
 *                                                                          *
 *      Get all User LED values                                             *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_ULED_getall( Uint16 *pattern )
{
    Uint16 retval;

	retval = USBSTK5515_GPIO_getInput(14)  |
	    (USBSTK5515_GPIO_getInput(15) << 1) |
		(USBSTK5515_GPIO_getInput(16) << 2) |
		(USBSTK5515_GPIO_getInput(17) << 3);

    *pattern = retval;

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _ULED_setall( pattern )                                                 *
 *                                                                          *
 *      Set all User LED values                                             *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_ULED_setall( Uint16 pattern )
{
    if (pattern & 0x01)
        USBSTK5515_GPIO_setOutput( 14, 1);
    else
        USBSTK5515_GPIO_setOutput( 14, 0);

    if (pattern & 0x02)
        USBSTK5515_GPIO_setOutput( 15, 1);
    else
        USBSTK5515_GPIO_setOutput( 15, 0);

    if (pattern & 0x04)
        USBSTK5515_GPIO_setOutput( 16, 1);
    else
        USBSTK5515_GPIO_setOutput( 16, 0);

    if (pattern & 0x08)
        USBSTK5515_GPIO_setOutput( 17, 1);
    else
        USBSTK5515_GPIO_setOutput( 17, 0);

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _ULED_on( number )                                                      *
 *                                                                          *
 *      number <- LED# [0:3]                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_ULED_on( Uint16 number )
{
    Uint16 led_state;
    Uint16 led_bit_on;

    led_bit_on = 1 << ( 3 - number );

    /*
     *  Get then set LED
     */
    if ( USBSTK5515_ULED_getall( &led_state ) )
        return -1;

    led_state = led_state & ( ~led_bit_on );

    if ( USBSTK5515_ULED_setall( led_state ) )
        return -1;

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _ULED_off( number )                                                     *
 *                                                                          *
 *      number <- LED# [0:7]                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_ULED_off( Uint16 number )
{
    Uint16 led_state;
    Uint16 led_bit_off;

    led_bit_off = 1 << ( 3 - number );

    /*
     *  Get then set LED
     */
    if ( USBSTK5515_ULED_getall( &led_state ) )
        return -1;

    led_state = led_state | led_bit_off;

    if ( USBSTK5515_ULED_setall( led_state ) )
        return -1;

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _ULED_toggle( number )                                                  *
 *                                                                          *
 *      number <- LED# [0:3]                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_ULED_toggle( Uint16 number )
{
    Uint16 led_state;
    Uint16 new_led_state;
    Uint16 led_bit_toggle;


    led_bit_toggle = 1 << ( 3 - number );

    /*
     *  Get then set LED
     */
    if ( USBSTK5515_ULED_getall( &led_state ) )
        return -1;

    if ( ( led_state & led_bit_toggle ) == 0 )
        new_led_state = led_state | led_bit_toggle;     /* Turn OFF */
    else
        new_led_state = led_state & ~led_bit_toggle;    /* Turn ON */

    if ( USBSTK5515_ULED_setall( new_led_state ) )
        return -1;

    return 0;
}
