/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  Flash interface for Intel/Micron Flash chips & Spansion Flash chips
 *
 */

#ifndef FLASH_
#define FLASH_

#include "usbstk5515.h"

#define MFG_SPANSION                0x01

/* ------------------------------------------------------------------------ *
 *  Flash Memory Property Definitions                                       *
 * ------------------------------------------------------------------------ */
#define FLASH_BASE                  ( 0x0400000 )
#define FLASH_END_OR_RANGE          ( 0x04000000 )
#define FLASH_SECTORSIZE_LOW        (Uint32)0x001000
#define FLASH_SECTORSIZE_HIGH       (Uint32)0x08000
#define FLASH_SECTORS_LOW           (Uint32)0x08
#define FLASH_SECTORS_HIGH          (Uint32)0x3A
#define FLASH_SECTORS               FLASH_SECTORS_HIGH + FLASH_SECTORS_LOW
#define FLASH_SIZE                  (FLASH_SECTORSIZE_LOW * FLASH_SECTORS_LOW) + (FLASH_SECTORSIZE_HIGH * FLASH_SECTORS_HIGH)

/* ------------------------------------------------------------------------ *
 *  Flash Memory Base Pointers                                              *
 * ------------------------------------------------------------------------ */
#define FLASH_BASE_PTR32    *( volatile Uint32* )FLASH_BASE
#define FLASH_BASE_PTR16    *( volatile Uint16* )FLASH_BASE
#define FLASH_BASE_PTR8     *( volatile Uint8* ) FLASH_BASE

/* Spansion only */
#define FLASH_CTL555        *( volatile Uint16* )( FLASH_BASE + 0x555 )
#define FLASH_CTL2AA        *( volatile Uint16* )( FLASH_BASE + 0x2AA )

/* ------------------------------------------------------------------------ *
 *  Flash Command Codes ( SPANSION )                                        *
 * ------------------------------------------------------------------------ */
#define FLASH_RESET                         0xF0
#define FLASH_CMD_AA                        0xAA
#define FLASH_CMD_55                        0x55
#define FLASH_ID                            0x90
#define FLASH_PROGRAM                       0xA0
#define FLASH_WRITE_BUFFER                  0x25
#define FLASH_PROGRAM_BUFFER                0x29
#define FLASH_ERASE                         0x80
#define FLASH_ERASE_CHIP                    0x10
#define FLASH_ERASE_SECTOR                  0x30
#define FLASH_ERASE_SUSPEND                 0xB0
#define FLASH_ERASE_RESUME                  0x10
#define FLASH_CFI_QUERY                     0x98

/* ------------------------------------------------------------------------ *
 *  Flash Memory Read Status Register Fields                                *
 * ------------------------------------------------------------------------ */
#define READ_STATUS_REGISTER_ISMS           0x80 // WRITE STATE MACHINE
#define READ_STATUS_REGISTER_ESS            0x40 // ERASE SUSPEND
#define READ_STATUS_REGISTER_ECLBS          0x20 // ERASE & CLEAR LOCK BITS
#define READ_STATUS_REGISTER_PSLBS          0x10 // PROGRAM & SET LOCK BIT
#define READ_STATUS_REGISTER_VPENS          0x08 // PROGRAMMING VOLTAGE
#define READ_STATUS_REGISTER_PSS            0x04 // PROGRAM SUSPEND
#define READ_STATUS_REGISTER_DPS            0x02 // DEVICE PROTECT

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
Int16  norflash_init        ( );
Int16  norflash_read        ( Uint32 src, Uint32 dst, Uint32 length );
Int16  norflash_write       ( Uint32 src, Uint32 dst, Uint32 length );
Int16  norflash_erase       ( Uint32 start, Uint32 length );
Uint32 norflash_checksum    ( Uint32 start, Uint32 length );
Uint32 norflash_getTotalPages( Uint16 num_flash_device );
Uint16 _FLASH_getId( Uint16* id);

/* Internal functions */
Int32  _FLASH_getMfg                ( );
Int32  _FLASH_getPageLength         ( );

/* Spansion */
Int16 _FLASH_waitWhileErasing       ( Uint32 addr, Int32 timeout );
Int16 _FLASH_waitWhileProgramming   ( Uint32 addr, Uint16 data, Int32 timeout );



#endif
