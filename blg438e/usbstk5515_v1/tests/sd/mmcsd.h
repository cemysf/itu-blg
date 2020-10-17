/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#include "usbstk5515.h"

#ifndef _MMCSD_H
#define _MMCSD_H


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  MMC/SD1 controller                                                       *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define MMCSD_MMCCTL            *( volatile ioport Uint16* )( 0x3B00 )
#define MMCSD_MMCCLK            *( volatile ioport Uint16* )( 0x3B04 )
#define MMCSD_MMCST0            *( volatile ioport Uint16* )( 0x3B08 )
#define MMCSD_MMCST1            *( volatile ioport Uint16* )( 0x3B0C )
#define MMCSD_MMCIM             *( volatile ioport Uint16* )( 0x3B10 )
#define MMCSD_MMCTOR            *( volatile ioport Uint16* )( 0x3B14 )
#define MMCSD_MMCTOD            *( volatile ioport Uint16* )( 0x3B18 )
#define MMCSD_MMCBLEN           *( volatile ioport Uint16* )( 0x3B1C )
#define MMCSD_MMCNBLK           *( volatile ioport Uint16* )( 0x3B20 )
#define MMCSD_MMCNBLC           *( volatile ioport Uint16* )( 0x3B24 )
#define MMCSD_MMCDRR1           *( volatile ioport Uint16* )( 0x3B28 )
#define MMCSD_MMCDRR2           *( volatile ioport Uint16* )( 0x3B29 )
#define MMCSD_MMCDXR1           *( volatile ioport Uint16* )( 0x3B2C )
#define MMCSD_MMCDXR2           *( volatile ioport Uint16* )( 0x3B2D )
#define MMCSD_MMCCMD1           *( volatile ioport Uint16* )( 0x3B30 )
#define MMCSD_MMCCMD2           *( volatile ioport Uint16* )( 0x3B31 )
#define MMCSD_MMCARG1           *( volatile ioport Uint16* )( 0x3B34 )
#define MMCSD_MMCARG2           *( volatile ioport Uint16* )( 0x3B35 )
#define MMCSD_MMCRSP_BASE       ( 0x3B38 )
#define MMCSD_MMCRSP0           *( volatile ioport Uint16* )( 0x3B38 )
#define MMCSD_MMCRSP1           *( volatile ioport Uint16* )( 0x3B39 )
#define MMCSD_MMCRSP2           *( volatile ioport Uint16* )( 0x3B3C )
#define MMCSD_MMCRSP3           *( volatile ioport Uint16* )( 0x3B3D )
#define MMCSD_MMCRSP4           *( volatile ioport Uint16* )( 0x3B40 )
#define MMCSD_MMCRSP5           *( volatile ioport Uint16* )( 0x3B41 )
#define MMCSD_MMCRSP6           *( volatile ioport Uint16* )( 0x3B44 )
#define MMCSD_MMCRSP7           *( volatile ioport Uint16* )( 0x3B45 )
#define MMCSD_MMCDRSP           *( volatile ioport Uint16* )( 0x3B48 )
#define MMCSD_MMCCIDX           *( volatile ioport Uint16* )( 0x3B50 )
#define MMCSD_SDIOCTL           *( volatile ioport Uint16* )( 0x3B64 )
#define MMCSD_SDIOST0           *( volatile ioport Uint16* )( 0x3B68 )
#define MMCSD_SDIOIEN           *( volatile ioport Uint16* )( 0x3B6C )
#define MMCSD_SDIOIST           *( volatile ioport Uint16* )( 0x3B70 )
#define MMCSD_MMCFIFOCTL        *( volatile ioport Uint16* )( 0x3B74 )


#define E_FAIL              1
#define E_INVALID_INPUT     2
#define E_TIMEOUT           3
#define E_DEVICE            4
#define E_MISC              0xF800

#define MMCSD_OP_TIMEOUT    2048
#define MMCSD_BSYEXP        0x0100
#define MMCSD_PPLEN         0x0080
#define MMCSD_FNCLK_INIT    1
#define MMCSD_CLK_INIT      300000

/*
 *  FIFO LEVEL
 */
#define MMCSD_FIFOLEVEL_32BYTES 0   // MMCSD_FIFO Levelzero ( 32 bytes )
#define MMCSD_FIFOLEVEL_64BYTES 1   // MMCSD_FIFO LevelOne ( 64 Bytes )

/*
 *  Endianness Select
 */
#define MMCSD_LITTLE_ENDIAN     0   // Little Endian Selection
#define MMCSD_BIG_ENDIAN        1   // Big Endian Selection

/*
 *  Data Bus Width
 */
#define MMCSD_DATA_BUS_1        0   // Data bus has 1 bit
#define MMCSD_DATA_BUS_4        1   // Data bus has 4 bits

/*
 *  DAT3 Edge Detection select
 */
#define MMCSD_DAT3_DISABLE      0   // DAT3 edge detection is disabled
#define MMCSD_DAT3_RISE         1   // DAT3 rising edge detection is enabled
#define MMCSD_DAT3_FALL         2   // DAT3 falling edge detection is enabled
#define MMCSD_DAT3_BOTH         3   // DAT3 both edge detection is enabled

/*
 *  Status bits of Register - Status0
 */
#define MMCSD_STAT0_DATDNE      0x0001      // Data Done Status
#define MMCSD_STAT0_BSYDNE      0x0002      // Busy Done Status
#define MMCSD_STAT0_RSPDNE      0x0004      // Command / Response Done Status
#define MMCSD_STAT0_TOUTRD      0x0008      // Time-Out ( read data ) Status
#define MMCSD_STAT0_TOUTRS      0x0010      // Time-Out ( response ) Status
#define MMCSD_STAT0_CRCWR       0x0020      // CRC error ( write data ) Status
#define MMCSD_STAT0_CRCRD       0x0040      // CRC error ( read data ) Status
#define MMCSD_STAT0_CRCRS       0x0080      // CRC error ( response ) Status
#define MMCSD_STAT0_SPIERR      0x0100      // Data Error ( in SPI mode ) Status
#define MMCSD_STAT0_DXRDY       0x0200      // Data Transmit Ready Status
#define MMCSD_STAT0_DRRDY       0x0400      // Data Receive Ready Status
#define MMCSD_STAT0_DATED       0x0800      // DAT3 Edge Detect Status

/*
 *  Status bits of Register - Status1
 */
#define MMCSD_STAT1_BUSY        0x0001      // Busy Status
#define MMCSD_STAT1_CLKSTP      0x0002      // Clock Stop Status
#define MMCSD_STAT1_DXEMP       0x0004      // Data transmit empty Status
#define MMCSD_STAT1_DRFUL       0x0008      // Data receive full Status
#define MMCSD_STAT1_DAT3ST      0x0010      // DAT3 Status
#define MMCSD_STAT1_FIFOEMP     0x0020      // FIFO empty status
#define MMCSD_STAT1_FIFOFULL    0x0040      // FIFO full status

/*
 *  Card States as per MMC/SD Specifications
 */
#define MMCSD_STATE_IDLE        0
#define MMCSD_STATE_READY       1
#define MMCSD_STATE_IDENT       2
#define MMCSD_STATE_STBY        3
#define MMCSD_STATE_TRAN        4
#define MMCSD_STATE_DATA        5
#define MMCSD_STATE_RCV         6
#define MMCSD_STATE_PRG         7
#define MMCSD_STATE_DIS         8
#define MMCSD_STATE_INA         9

/*
 *  Direction of DMA Transfer
 */
#define MMCSD_FROM_MMC          0           // MMCIF to SDRAM
#define MMCSD_TO_MMC            1           // SDRAM to MMCIF

/*
 *  MMCSD Controller Configuration parameters
 */
typedef struct {
    Uint16 writeEndian;         // Endian select enable while writing
    Uint16 readEndian;          // Endian select enable while reading
    Uint16 dat3Detect;          // DAT3 Edge detection
    Uint8 cardReadyFlag;        // Card Ready flag in SDIO init response TRUE:
                                // Card Ready FALSE: Card not ready
    Uint8 IOflag;               // SDIO I/O function flag TRUE: I/O present FALSE: I/O absent
    Uint8 memoryFlag;           // SD memory function presence flag
                                // TRUE: memory present FALSE: memory absent
    Uint8 numFunctions;         // Number of I/O functions available in SDIO card
    Uint8 spiModeEnable;        // SPI mode, TRUE:Enable SPI Mode, FALSE:Enable Native Mode
    Uint8 csEnable;             // Card Select enable when writing, TRUE:CS output
                                // is LOW, FALSE: CS output is HIGH. Valid Only in SPI mode
    Uint8 spiCrcErrCheckEnable; // CRC Error check enabled, TRUE:Enable CRC check,
                                // FALSE:Disable CRC check. Valid Only in SPI mode
    Uint16 busWidth;            // Data bus width, Only in Native mode,
                                // MMCSD_DATA_BUS_1:1 bit data bus,
                                // MMCSD_DATA_BUS_4:4 bit data bus
    Uint16 timeoutResponse;     // Timeout value for response, range 0 to 255
                                // MMC CLK clock cycles for Native mode, for
                                // SPI mode timeout value is equal to this
                                // value multiplied by 8 MMC CLK clock cycles
    Uint16 timeoutRead;         // Time out value for data read, range from
                                // 0 to 65535 MMC CLK clock cycles in native mode,
                                // for SPI mode timeout value is equal to this
                                // value multiplied by 8 MMC CLK clock cycles
    Uint16 fifoThreshold;       // To set the FIFO depth 16bytes or 32 bytes
} MMCSD_ConfigData;

/*
 *  Response information received from MMCSD
 */
typedef struct {
  Uint16 response[8];           // Response of the command
  Uint8 dataResponse;           // Data response
  Uint8 errorToken;             // Error Token
  Uint8 commandIdk;             // Command Index
} MMCSD_ResponseData;

/*
 *  MMC-SD: Card Status Register \n
    In native mode, all the fields will be set. \n
    In SPI mode, the error flags will contain the entire response.
 */
typedef struct {
  Uint8  appSpecific;
  Uint8  ready;
  Uint16 currentState;
  Uint8  eraseReset;
  Uint8  eccDisabled;
  Uint8  wpEraseSkip;
  Uint16 errorFlags;
  Uint8  multiMediaCard;
} MMCSD_cardStatusReg;

/*
 *  MMC-SD: Native mode Card CSD Register Information, required by the driver
 */
typedef struct {
  Uint8  permWriteProtect;
  Uint8  tmpWriteProtect;
  Uint8  writeBlkPartial;
  Uint16 writeBlkLenBytes;
  Uint8  wpGrpEnable;
  Uint8  wpGrpSize;             // Extracting 7 bits: For MMC - 5 bits reqd; For SD - 7 bits reqd. ( have to be taken care by user )
  Uint8  dsrImp;
  Uint8  readBlkMisalign;
  Uint8  writeBlkMisalign;
  Uint8  readBlkPartial;
  Uint16 readBlkLenBytes;
  Uint8  sysSpecVersion;        // These bits are reserved in the case of SD card
} MMCSD_csdRegInfo;

/*----- Function prototypes -----*/
Uint16 MMCSD_clearResponse  ( );
Uint16 MMCSD_checkStatus    ( Uint16 event, Int16 timeOut, Int16 operation );
Uint16 MMCSD_setConfig      ( MMCSD_ConfigData* mmcsdConfig );
Uint16 MMCSD_sendCmd        ( Uint32 command, Uint32 argument, Uint8 checkStatus, Uint16 statusBits );
Uint16 MMCSD_getCardStatus  ( MMCSD_ResponseData* mmcsdResponse, MMCSD_cardStatusReg* cardStatus );
Uint16 MMCSD_getCardCID     ( MMCSD_ResponseData* mmcsdResponse, Uint16* cardCID );
Uint16 MMCSD_getCardCSD     ( MMCSD_ResponseData* mmcsdResponse, Uint16* cardCSD, MMCSD_csdRegInfo* localCSDInfo );

Uint16 MMCSD_readNWords     ( Uint16* data, Uint32 numofBytes, Uint32 cardMemAddr );
Uint16 MMCSD_writeNWords    ( Uint16* data, Uint32 numofBytes, Uint32 cardMemAddr );

#define MMCSD_VDD_32_34         0x00300000

/* Response Macros */
#define MMCSD_RSPNONE           0x0000
#define MMCSD_RSP1              0x0200
#define MMCSD_RSP2              0x0400
#define MMCSD_RSP3              0x0600
#define MMCSD_RSP4              MMCSD_RSP1
#define MMCSD_RSP5              MMCSD_RSP1
#define MMCSD_RSP6              MMCSD_RSP1

/* Commands and their responses */
/* MMC and SD */
#define MMCSD_GO_IDLE_STATE         ( 0 )
#define MMCSD_ALL_SEND_CID          ( 2 | MMCSD_RSP2 )
#define MMCSD_SELECT_CARD           ( 7 | MMCSD_RSP1 )
#define MMCSD_DESELECT_CARD         ( 7 )
#define MMCSD_SEND_CSD              ( 9 | MMCSD_RSP2 )
#define MMCSD_SEND_CID              ( 10 | MMCSD_RSP2 )
#define MMCSD_SEND_STATUS           ( 13 | MMCSD_RSP1 )
#define MMCSD_GO_INACTIVE_STATE     ( 15 )
#define MMCSD_APP_CMD               ( 55 | MMCSD_RSP1 )
#define MMCSD_READ_MULTIPLE_BLOCK   ( 18 | MMCSD_RSP1 )
#define MMCSD_WRITE_MULTIPLE_BLOCK  ( 25 | MMCSD_RSP1 )

/* Common to SPI & MMC */
#define MMCSD_SET_BLOCKLEN          ( 16 | MMCSD_RSP1 )
#define MMCSD_PROGRAM_CSD           ( 27 | MMCSD_RSP1 | MMCSD_BSYEXP )
#define MMCSD_SET_WRITE_PROT        ( 28 | MMCSD_RSP1 | MMCSD_BSYEXP )
#define MMCSD_CLR_WRITE_PROT        ( 29 | MMCSD_RSP1 | MMCSD_BSYEXP )
#define MMCSD_SEND_WRITE_PROT       ( 30 | MMCSD_RSP1 )
#define MMCSD_READ_SINGLE_BLOCK     ( 17 | MMCSD_RSP1 )
#define MMCSD_WRITE_BLOCK           ( 24 | MMCSD_RSP1 )

#define SD_SEND_RELATIVE_ADDR       ( 03 | MMCSD_RSP6 | MMCSD_PPLEN )
#define SD_SET_BUS_WIDTH            ( 06 | MMCSD_RSP1 | MMCSD_PPLEN )
#define SD_APP_OP_COND              ( 41 | MMCSD_RSP3 )

#define MMC_SEND_OP_COND            ( 01 | MMCSD_RSP3 )

/* Function Prototypes */
Uint16 MMCSD_goIdleState        ( );
Uint16 MMCSD_allSendCID         ( );
Uint16 MMCSD_sendStatus         ( Uint32 rca, MMCSD_cardStatusReg* cardStatus );
Uint16 MMCSD_selectCard         ( Uint32 rca );
Uint16 MMCSD_sendCSD            ( Uint32 rca, Uint16* cardCSD );
Uint16 MMCSD_appCmd             ( Uint32 rca );
Uint16 MMCSD_singleBlkRead      ( Uint32 cardMemAddr, Uint32* dest, Uint32 blklength, Uint32 endian );
Uint16 MMCSD_singleBlkWrite     ( Uint32 cardMemAddr, Uint32* src, Uint32 blklength, Uint32 endian );
Uint16 MMCSD_initCard           ( Uint32* relCardAddr, MMCSD_cardStatusReg* cardStatus, MMCSD_ConfigData* mmcsdConfig, Uint16 fifoThrlevel );
Uint16 MMCSD_cardIdentification ( MMCSD_ConfigData* mmcsdConfig, Uint32* relCardAddr, MMCSD_cardStatusReg* cardStatus, Uint32 opTimeout );

#endif
