/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  ULED Test
 *
 */

#include "usbstk5515.h"
#include "usbstk5515_led.h"
#include "stdio.h"

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  uled_test( )                                                            *
 *     User LED tests toggles each of the four user LEDs 6 times            *                                             
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 uled_test( )
{
    Int16 i, j;
    
    printf("    User LED tests toggles each of the four user LEDs 6 times\n");
 	SYS_EXBUSSEL = 0x6000;  // Enable user LEDs on external bus
    USBSTK5515_ULED_init( );

    /* Running LED test */
    for ( j = 0 ; j < 6 ; j++ )
    {
        for ( i = 0 ; i < 4 ; i++ )
        {
            if ( USBSTK5515_ULED_on( i ) )  // Turn on user LED i
                return 1;
            USBSTK5515_waitusec( 50000 );
        }
        
        for ( i = 0 ; i < 4 ; i++ )
        {
            if ( USBSTK5515_ULED_off( i ) ) // Turn off user LED i
                return 2;
            USBSTK5515_waitusec( 50000 );
        }
    }
    USBSTK5515_ULED_setall( 0x00 );

    return 0;
}

