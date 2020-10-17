/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#include "mmcsd.h"

MMCSD_ResponseData mmcsdResponse;
MMCSD_csdRegInfo mmcsdCSDRegInfo;

/*
 *  Set Data size for MMC/SD
 */
Uint16 MMCSD_setDataSize( Uint16 numBlks, Uint16 blockSize )
{
    if ( blockSize == 0 )
        return E_INVALID_INPUT;

    MMCSD_MMCBLEN = blockSize;
    MMCSD_MMCNBLK = numBlks;
    return 0;
}

/*
 *  Check Status of the MMC/SD controller
 */
Uint16 MMCSD_checkStatus( Uint16 event, Int16 timeOut, Int16 operation )
{
    Uint16 event_log = 0;
    Uint16 ret_status = E_DEVICE;

    if ( timeOut )
    {
        for ( ; timeOut > 0 ; timeOut-- )
        {
            event_log |= ( MMCSD_MMCST0 & event );

            /* 1 or more events have occured */
            if ( ( operation == 1 ) && event_log )
            {
                ret_status = 0;
                break;
            }

            /* all events have occured */
            if ( ( operation == 0 ) && ( ( event_log & event ) == event ) )
            {
                ret_status = 0;
                break;
            }
        }
        return E_TIMEOUT;
    }
    else
    {
        for ( ; ; )
        {
            event_log |= ( MMCSD_MMCST0 & event );

            /* 1 or more events have occured */
            if ( ( operation == 1 ) && event_log )
            {
                ret_status=0;
                break;
            }

            /* all events have occured */
            if ( ( operation == 0 ) && ( ( event_log & event ) == event ) )
            {
                ret_status=0;
                break;
            }
        }
    }

    return ret_status;
}

/*
 *  Send command to set all the MMC/SD cards to Idle State
 */
Uint16 MMCSD_goIdleState( )
{
    return MMCSD_sendCmd( ( 0x4000 | MMCSD_GO_IDLE_STATE ), 0, 0, MMCSD_STAT0_RSPDNE );
}

/*
 *  Send command to read the contents of the Card Identification( CID )register, on the MMC/SD
 */
Uint16 MMCSD_allSendCID( void )
{
    return MMCSD_sendCmd( MMCSD_ALL_SEND_CID, 0, 1, MMCSD_STAT0_RSPDNE );
}

/*
 *  Send command to read the status of the MMC/SD
 */
Uint16 MMCSD_sendStatus( Uint32 rca, MMCSD_cardStatusReg *cardStatus )
{
    Uint16 status;

    if ( status = MMCSD_sendCmd( MMCSD_SEND_STATUS, rca << 16, 1, MMCSD_STAT0_RSPDNE ) )
        return status;

    MMCSD_getCardStatus( &mmcsdResponse, cardStatus );
    return 0;
}

/*
 *  Send command to select a particular MMC/SD, using it's assigned RCA
 */
Uint16 MMCSD_selectCard( Uint32 rca )
{
    Uint16 status;
    MMCSD_cardStatusReg cardStatus;

    if ( rca == 0 )
        return E_INVALID_INPUT;

    if ( status = MMCSD_sendCmd( MMCSD_SELECT_CARD, rca << 16, 1, MMCSD_STAT0_RSPDNE ) )
        return status;

    if ( ( status = MMCSD_sendStatus( rca, &cardStatus ) ) == 0 )
        return status;

    if ( ( cardStatus.currentState != MMCSD_STATE_TRAN )
      && ( cardStatus.currentState != MMCSD_STATE_PRG ) )
        return E_FAIL;

    return 0;
}

/*
 *  Send command to read the contents of the Card Specific Data( CSD )register, on the MMC/SD
 */
Uint16 MMCSD_sendCSD( Uint32 rca, Uint16 *cardCSD )
{
    Uint16 status;

    if ( status = MMCSD_sendCmd( MMCSD_SEND_CSD, rca << 16, 1, MMCSD_STAT0_RSPDNE ) )
        return status;

    MMCSD_getCardCSD( &mmcsdResponse, cardCSD, &mmcsdCSDRegInfo );
    return 0;
}

/*
 *  Send command to indicate that the next command is an application specific command
 */
Uint16 MMCSD_appCmd( Uint32 rca )
{
    return MMCSD_sendCmd( MMCSD_APP_CMD, rca << 16, 1, MMCSD_STAT0_RSPDNE );
}

/*
 *  Send command to read a single block of data from the MMC/SD card
 */
Uint16 MMCSD_singleBlkRead( Uint32 cardMemAddr, Uint32 *dest, Uint32 blklength, Uint32 endian )
{
    Uint16 i;
    Uint16 status = 0;

//    if ( mmcsdCSDRegInfo.readBlkLenBytes != blklength )
//        if ( mmcsdCSDRegInfo.readBlkPartial != 1 )
//            return E_INVALID_INPUT;

    if ( cardMemAddr & 0x1FF )
        if ( mmcsdCSDRegInfo.readBlkMisalign != 1 )
            return E_INVALID_INPUT;

    if ( MMCSD_sendCmd( MMCSD_SET_BLOCKLEN, blklength, 0, MMCSD_STAT0_RSPDNE ) )
        return E_FAIL;

    MMCSD_clearResponse( );

    if ( MMCSD_setDataSize( 1, blklength ) )/* num_blks = 1, num_of_bytes = blklength */
        return E_FAIL;

    /* reset the FIFO  */
    MMCSD_MMCFIFOCTL |= 1;
    USBSTK5515_waitusec(10);

    /* Set the Transfer direction from the FIFO as receive*/
    MMCSD_MMCFIFOCTL &= 0xFFFD;

    /*Send read single Block Command */
    if ( MMCSD_sendCmd( 0x12000 | MMCSD_READ_SINGLE_BLOCK, cardMemAddr, 0, MMCSD_STAT0_RSPDNE ) )
        return E_FAIL;

    if ( MMCSD_readNWords( ( Uint16* )dest, blklength, cardMemAddr ) )
        return E_FAIL;

    for ( i = 0 ; i < 100 ; i++ );


    if ( status == 0 )
    {
        if ( MMCSD_checkStatus( MMCSD_STAT0_DATDNE, 0, 0 ) == 0 )
            return 0;
        else
            return E_FAIL;
    }

    USBSTK5515_waitusec(10000);
    return 0;
}

/*
 *  Send command to write a single block of data to the MMC/SD card
 */
Uint16 MMCSD_singleBlkWrite( Uint32 cardMemAddr, Uint32 *src, Uint32 blklength, Uint32 endian )
{
    Uint16 status;

    /* Check for the Valid block length of the Card */
//    if ( mmcsdCSDRegInfo.writeBlkLenBytes != blklength )
//        if ( mmcsdCSDRegInfo.writeBlkPartial != 1 )
//            return E_INVALID_INPUT;

    if ( cardMemAddr & 0x01FF )
        if ( mmcsdCSDRegInfo.writeBlkMisalign != 1 )
            return E_INVALID_INPUT;

    status = MMCSD_setDataSize( 1, blklength ); /* num_blks = 1, num_of_bytes = blklength */

    status = MMCSD_sendCmd( MMCSD_SET_BLOCKLEN, blklength, 0, MMCSD_STAT0_RSPDNE );

    if ( status == 0 )
    {
        /* Write Data, every time MMCDXR Reg full */
        status = MMCSD_writeNWords( ( Uint16* )src, blklength, cardMemAddr );

        /* Delay Required*/
        USBSTK5515_waitusec( 100000 );

        if ( status )
            return E_FAIL;

        /* command been sent */
        if ( MMCSD_checkStatus( MMCSD_STAT0_DATDNE, 0, 0 ) )
            return E_FAIL;

        USBSTK5515_waitusec(10000);
    }
    return 0;
}

/*
 *  command to check if the Operating Voltage Conditions of the MMC, match that of the host
 */
Uint16 MMC_sendOpCond( Uint32 voltageWindow, Uint32 opTimeOut )
{
    for ( ; opTimeOut > 0 ; opTimeOut -- )
    {
        /* Format and send cmd: Volt. window is usually 0x00300000( 3.4-3.2v ) */
        MMCSD_sendCmd( MMC_SEND_OP_COND, voltageWindow, 1, MMCSD_STAT0_RSPDNE );

        if ( MMCSD_MMCRSP7 & 0x8000 )
            return 0;
   }

   return E_DEVICE;
}

/*
 *  Send command to check if the Operating Voltage Conditions of the SD, match that of the host
 */
Uint16 SD_sendOpCond( Uint32 voltageWindow, Uint32 opTimeOut )
{
    Uint16 status;

    for ( ; opTimeOut > 0 ; opTimeOut-- )
    {
        /* Format and send cmd: Volt. window is usually 0x00300000( 3.4-3.2v )*/
        if ( status = MMCSD_sendCmd( SD_APP_OP_COND, voltageWindow,1, MMCSD_STAT0_RSPDNE ) )
            return status;

        if ( MMCSD_MMCRSP7 & 0x8000 )
            return 0;

        /* Send CMD55 with RCA = 0 for the next iteration */
        if ( status = MMCSD_appCmd( 0 ) )
            return status;
   }

   return E_DEVICE;
}

/*
 *  Send command to set the Relative Card Address( RCA )of the SD
 */
Uint16 SD_sendRCA( Uint32* rcaRcvd )
{
    Uint16 status;

    /*
     *  rca is given a value >= 2, as 0 or 1 ( in case of SanDisk cards ) is
     *  the default value for all cards. Also, the rca value is sent as
     *  the upper 16 bits of the command argument
     */
    if ( status = MMCSD_sendCmd( SD_SEND_RELATIVE_ADDR, 0, 1, MMCSD_STAT0_RSPDNE ) )
        return status;

    *rcaRcvd = MMCSD_MMCRSP7;
    return 0;
}

/*
 *  Send command to set the Bus Width for SD Card( 1 or 4 data lines )
 */
Uint16 SD_setBusWidth( Uint32 rca, Uint8 busWidth, Uint32 opTimeOut )
{
    Uint16 status;

    for ( ; opTimeOut > 0 ; opTimeOut-- )
    {
        /* Send CMD55 */
        if ( status = MMCSD_appCmd( rca ) )
            return E_MISC;

        if ( ( status = MMCSD_sendCmd( SD_SET_BUS_WIDTH, busWidth, 1, MMCSD_STAT0_RSPDNE ) ) == 0 )
            break;
    }

    if ( status == 0 )
    {
        if ( busWidth == 0 )
            MMCSD_MMCCTL &= 0xFFFB;
        else
            MMCSD_MMCCTL |= 0x0004;
    }

    return status;
}

/*
 *  Card Identification Sequence for MMC and SD
 */
Uint16 MMCSD_cardIdentification( MMCSD_ConfigData* config, Uint32* rca, MMCSD_cardStatusReg* cardStatus, Uint32 opTimeout )
{
    Uint16 status;
    Uint16 cardReg[8];
    Uint8 mmc = 1;

    /* Place all cards in idle state */
    if ( status = MMCSD_goIdleState( ) )
        return status;

    /* Send the operating Voltage Range */
    RESEND_CMD41:

    /* Introduce a delay for slow cards */
    USBSTK5515_waitusec( 100000 );

    status = MMCSD_appCmd( 0 );     /* Send CMD55 with RCA = 0 */

    if ( status )
        status = MMC_sendOpCond( MMCSD_VDD_32_34, opTimeout );
    else
    {
        // Experimenting with the whole supported voltage range
        if ( SD_sendOpCond( 0x00ff8000, opTimeout ) )
            goto RESEND_CMD41;
        mmc = 0;
    }
	mmc = 0;

    /* Return to the application, of the card is an MMC card or an SD card */
    cardStatus->multiMediaCard = mmc;

    /* Ask all cards to send their CIDs */
    if ( status = MMCSD_allSendCID( ) )
        return status;

    MMCSD_getCardCID( &mmcsdResponse, cardReg );

    /* Read Relative Address from the card and store it in variable rca */
    if ( status = SD_sendRCA( rca ) )
        return status;

    /* Read the CSD structure for MMC/SD */
    if ( status = MMCSD_sendCSD( *rca, cardReg ) )
        return status;

    /* Select the Card which responded */
    if ( status = MMCSD_selectCard( *rca ) )
        return status;

    if ( *rca > 0 )
        if ( status = MMCSD_sendStatus( *rca, cardStatus ) )
            return status;

    if ( config->busWidth == MMCSD_DATA_BUS_4 )
        if ( status = SD_setBusWidth( *rca, 2, 2048 ) )
          return status;

    return status;
}

/*
 *  MMC/SD interface selection, Controller and Card Initialization
 */
Uint16 MMCSD_initCard( Uint32* relCardAddr, MMCSD_cardStatusReg* cardStatus,
                        MMCSD_ConfigData* config, Uint16 fifoThrlevel )
{
    Uint16 i;
    Uint16 status;

    MMCSD_MMCCLK = 0x0102;                          // Enable the Clock and set the divide-down value

    for( i = 0 ; i < 1000 ; i++ );

    if ( fifoThrlevel == MMCSD_FIFOLEVEL_32BYTES )  // Set the FIFO level to 16bytes or 32 bytes
        MMCSD_MMCFIFOCTL &= 0xFFFB;
    else
        MMCSD_MMCFIFOCTL |= 0x0004;

    MMCSD_MMCCTL = 0x0007;                          // Put the CMD and Data Logic in RESET state
    USBSTK5515_waitusec(10);

    /*
     *  Configuration Set; Clk: MMC Clk Rt = ARMClock/fnClkRate+1,
     *  MMC Clk o/p =( MMC Clk Rt/2*( mmcClockRateDiv+1 ) )
     */
    if ( status = MMCSD_setConfig( config ) )
        return status;

    /* Identification cycle of MMC/SD */
    return MMCSD_cardIdentification( config, relCardAddr, cardStatus, MMCSD_OP_TIMEOUT );
}
