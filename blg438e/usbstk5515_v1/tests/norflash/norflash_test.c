/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  NOR Flash Test
 *
 */

#include "stdio.h"
#include "norflash.h"

static Uint32 buf_len = 1024;
static Uint16 rx[1024];
static Uint16 tx[1024];

#define FLASH_PAGESIZE      0x20000  // FLASH_PAGESIZE is an arbitrarily set size. 
                                     // It does not have any significance to the flash device.

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  norflash_test( )                                                        *
 *                                                                          *
 *      Write a 1024-byte long pattern every FLASH_PAGESIZE bytes           *
 * ------------------------------------------------------------------------ */
Int16 norflash_test( )
{
    Int32 i = 0, j = 0;
    Uint16 *p16, id[3];
    Uint32 addr;
    
    /* Initialize Flash */
    norflash_init();
    printf( "This test writes a 1024-byte long pattern every FLASH_PAGESIZE = 0x20000 bytes.\n");

    _FLASH_getId( &id[0] );
    printf("     Manufacture ID is: 0x%02x \n     Device ID is     : 0x%02x\n", id[0], id[1] & 0xFF );
    
    /* ---------------------------------------------------------------- *
     *  Erase                                                           *
     * ---------------------------------------------------------------- */

    /* Erasing Flash Sectors */
    printf( "     Erasing Sectors containing pages.\n");
    for ( i = 1 ; i < 16 ; i++ )    // Skip first page to avoid erasing demo
        norflash_erase( FLASH_BASE + ( i * FLASH_PAGESIZE ), FLASH_PAGESIZE  );

    /* ---------------------------------------------------------------- *
     *  Write                                                           *
     * ---------------------------------------------------------------- */
    printf( "     Writing Flash pattern\n", 0, buf_len );
    i = 0;
    /* Write a pattern of buf_len length every FLASH_PAGESIZE bytes till end of Flash */
    for ( addr = FLASH_BASE + FLASH_PAGESIZE ; addr < FLASH_BASE + (FLASH_SIZE / 2) ; addr += FLASH_PAGESIZE )
    {
        /* Create write pattern */
        p16 = ( Uint16* )tx;
        for ( j = 0 ; j < buf_len ; j += 4 )
            *p16++ = ( (addr >> 8) + j + i );

        /* Write the pattern to Flash */
        norflash_write( ( Uint32 )tx, addr, buf_len );
        i++;
    }

    /* ---------------------------------------------------------------- *
     *  Read                                                            *
     * ---------------------------------------------------------------- */
    printf( "     Reading Flash pattern\n", 0, 1024/*nbytes*/ );

    i = 0;

    /* Read the pattern of buf_len length every FLASH_PAGESIZE bytes till end of Flash */
    for ( addr = FLASH_BASE + FLASH_PAGESIZE ; addr < FLASH_BASE + (FLASH_SIZE / 2) ; addr += FLASH_PAGESIZE )
    {
        /* Read from Flash */
        norflash_read( addr, ( Uint32 )rx, buf_len );

        /* Check pattern */
        p16 = ( Uint16* )rx;
        for ( j = 0 ; j < buf_len ; j += 4 )
            if ( *p16++ != ( (addr >> 8) + j + i ) )
                return ( j | 0x8000 );
        i++;
    }

    /* Test Passed */

    return 0;
}
