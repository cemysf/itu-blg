/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  SD Card Test
 *
 */

#include "mmcsd.h"
#include "stdio.h"

Uint16 id[128];
Uint16 tx[128];
Uint16 rx[128];

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  SD Test                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Uint16 sd_test( )
{
    Uint16 i;
    Uint16 errorflag    = 0;
    Uint32 relCardAddr  = 2;
    Uint32 cardAddr     = 4096;
    Uint32 blkLength    = 512;

    MMCSD_cardStatusReg cardStatus;
    MMCSD_ConfigData    mmcsdConfig2 = {
        MMCSD_LITTLE_ENDIAN,  // write Endian
        MMCSD_LITTLE_ENDIAN,  // read Endian
        MMCSD_DAT3_DISABLE,   // Edge Detection disbale
        0,                    // SpiModeEnable
        0,                    // csEnable
        0,                    // spiCrcEnable
        0,
        0,                    // SpiModeEnable
        0,                    // csEnable
        0,                    // spiCrcEnable
        MMCSD_DATA_BUS_4,     // data bus width
        0xFF,                 // response timeout
        0xFFFF                // data read timeout
    };
    
 	SYS_EXBUSSEL = 0x0100;  // Enable SD1 on external bus
 	
    /*
     *  Fill tx buffer and clear rx buffer
     */
    for( i = 0 ; i < 128 ; i++ )
    {
        tx[i]= i;
        rx[i]= 0;
    }

    if ( MMCSD_initCard( &relCardAddr, &cardStatus, &mmcsdConfig2,
                         MMCSD_FIFOLEVEL_32BYTES ) )
    {
        printf( "SD Card Initialization failed\n" );
        return 1;
    }

    /*
     *  Write Block
     */
    if ( MMCSD_singleBlkWrite( cardAddr, ( Uint32* )tx, blkLength, 0 ) )
    {
        printf( "ERROR : SD Write block\n" );
        return 1;
    }

    /*
     *  Read Block
     */
    if ( MMCSD_singleBlkRead( cardAddr, ( Uint32* )rx, blkLength, 0 ) )
    {
        printf( "ERROR : SD Read block\n" );
        return 1;
    }

    /*
     * Compare tx and Rx Buffers
     */
    for ( i = 0 ; i < 128 ; i++ )
    {
        if ( rx[i] != tx[i] )
        {
            errorflag++;
            break;
        }
    }

    return errorflag;
}
