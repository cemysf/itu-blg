/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#include "stdio.h"
#include "usbstk5515.h"

#define PLL_100M 1

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Testing Function                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void TEST_execute( Int16 ( *funchandle )( ), char *testname, Int16 testid )
{
    Int16 status;

#define CONFIG_MSW       *(ioport volatile unsigned *)0x1C1F    // Clock Configuration MSW Register
#define PLL_CNTL1        *(ioport volatile unsigned *)0x1C20    // PLL Control Register #1
#define PLL_CNTL2        *(ioport volatile unsigned *)0x1C21    //  PLL Control Register #2
#define PLL_CNTL3        *(ioport volatile unsigned *)0x1C22    //  PLL Control Register #3
#define PLL_CNTL4        *(ioport volatile unsigned *)0x1C23    //  PLL Control Register #4

    /*
    CONFIG_MSW = 0x0;
    PLL_CNTL1 = 0x0;

#if (PLL_100M ==1)
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0000;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x8BE8;

#elif (PLL_12M ==1)
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0200;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x82ED;
#elif (PLL_98M ==1)
    // 98.304 MHz
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0000;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x82ED;

#endif

    while ( (PLL_CNTL3 & 0x0008) == 0);
    // Switch to PLL clk
    CONFIG_MSW = 0x1;
*/

    /* Display test ID */
    printf( "%02d  Testing %s...\n", testid, testname );

    /* Call test function */
    status = funchandle( );

    /* Check for test fail */
    if ( status != 0 )
    {
        /* Print error message */
        printf( "     FAIL... error code %d... quitting\n", status );

        /* Software Breakpoint to Code Composer */
        SW_BREAKPOINT;
    }
    else
    {
        /* Print error message */
        printf( "    PASS\n" );
    }
}

extern Int16 aic3204_test( );

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void main( void )
{
    /* Initialize BSL */
    USBSTK5515_init( );

    printf("EXBUSSEL = %02x\n", SYS_EXBUSSEL);
    
    TEST_execute( aic3204_test, "AIC3204", 1 );

    printf( "\n***ALL Tests Passed***\n" );
    SW_BREAKPOINT;
}
