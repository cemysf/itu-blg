/******************************************************************************
**+-------------------------------------------------------------------------+**
**|                            ****                                         |**
**|                            ****                                         |**
**|                            ******o***                                   |**
**|                      ********_///_****                                  |**
**|                      ***** /_//_/ ****                                  |**
**|                       ** ** (__/ ****                                   |**
**|                           *********                                     |**
**|                            ****                                         |**
**|                            ***                                          |**
**|                                                                         |**
**|         Copyright (c) 2006 - 2010    Texas Instruments Incorporated     |**
**|                        ALL RIGHTS RESERVED                              |**
**|                                                                         |**
**| Permission is hereby granted to licensees of Texas Instruments          |**
**| Incorporated (TI) products to use this computer program for the sole    |**
**| purpose of implementing a licensee product based on TI products.        |**
**| No other rights to reproduce, use, or disseminate this computer         |**
**| program, whether in part or in whole, are granted.                      |**
**|                                                                         |**
**| TI makes no representation or warranties with respect to the            |**
**| performance of this computer program, and specifically disclaims        |**
**| any responsibility for any damages, special or consequential,           |**
**| connected with the use of this program.                                 |**
**|                                                                         |**
**+-------------------------------------------------------------------------+**
******************************************************************************/

/**
 *  \file   i2s_sample.c
 *
 *  \brief  I2S application program
 *
 *  This file contains the fuction calls to I2S api's.
 *
 *  (C) Copyright 2008, Texas Instruments, Inc
 *
 */

#include <stdio.h>
#include <std.h>
//#include "corazon.h"
#include "system_drv.h"
#include "csl_dma.h"
#include "csl_i2s.h"
//#include "data_types.h"

extern void AIC3254_init (void);

// SINE_WAVE_1K and AUDIO_BYPASS are exclusive
#define SINE_WAVE_1K    1        
#define AUDIO_BYPASS    0
#define CONTENT     SINE_WAVE_1K  

#define USE_DMA         1       // if USE_DMA ==0, then I2S Interrupt is used
#define SINE_WAVE       2 

#if (CONTENT ==SINE_WAVE_1K)

#define XMIT_BUFF_SIZE  48

#if (SINE_WAVE ==1)
//0 dB 1 KHz sine sampled at 48 KHz
Int16 XmitL_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x1051,0x205A,0x2FD6,0x3E80,0x4C18,0x5863,0x632B, 
0x6C41,0x737C,0x78BE,0x7BEE,0x7D00,0x7BEE,0x78BE,0x737C, 
0x6C41,0x632B,0x5863,0x4C18,0x3E80,0x2FD6,0x205A,0x1051, 
0x0000,0xEFAF,0xDFA6,0xD02A,0xC180,0xB3E8,0xA79D,0x9CD5, 
0x93BF,0x8C84,0x8742,0x8412,0x8300,0x8412,0x8742,0x8C84, 
0x93BF,0x9CD5,0xA79D,0xB3E8,0xC180,0xD02A,0xDFA6,0xEFAF };
#elif (SINE_WAVE ==2)
// -3dB 1 KHz sine sampled at 48 KHz
Int16 XmitL_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x0B6C,0x16A6,0x217C,0x2BC0,0x3544,0x3DDF,0x456B, 
0x4BC7,0x50D7,0x5485,0x56C0,0x5780,0x56C0,0x5485,0x50D7, 
0x4BC7,0x456B,0x3DDF,0x3544,0x2BC0,0x217C,0x16A6,0x0B6C, 
0x0000,0xF494,0xE95A,0xDE84,0xD440,0xCABC,0xC221,0xBA95, 
0xB439,0xAF29,0xAB7B,0xA940,0xA880,0xA940,0xAB7B,0xAF29, 
0xB439,0xBA95,0xC221,0xCABC,0xD440,0xDE84,0xE95A,0xF494

};
#elif (SINE_WAVE ==3)
//0 dB 2 KHz sine sampled at 48 KHz
Int16 XmitL_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x205A,0x3E80,0x5863,0x6C41,0x78BE,0x7D00,0x78BE, 
0x6C41,0x5863,0x3E80,0x205A,0x0000,0xDFA6,0xC180,0xA79D, 
0x93BF,0x8742,0x8300,0x8742,0x93BF,0xA79D,0xC180,0xDFA6, 
0x0000,0x205A,0x3E80,0x5863,0x6C41,0x78BE,0x7D00,0x78BE, 
0x6C41,0x5863,0x3E80,0x205A,0x0000,0xDFA6,0xC180,0xA79D, 
0x93BF,0x8742,0x8300,0x8742,0x93BF,0xA79D,0xC180,0xDFA6 
};
#elif (SINE_WAVE ==4)
//-3 dB 2 KHz sine sampled at 48 KHz
Int16 XmitL_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A,
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A
};
#endif


#if (SINE_WAVE ==1)
//0 dB 1 KHz sine sampled at 48 KHz
Int16 XmitR_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x1051,0x205A,0x2FD6,0x3E80,0x4C18,0x5863,0x632B, 
0x6C41,0x737C,0x78BE,0x7BEE,0x7D00,0x7BEE,0x78BE,0x737C, 
0x6C41,0x632B,0x5863,0x4C18,0x3E80,0x2FD6,0x205A,0x1051, 
0x0000,0xEFAF,0xDFA6,0xD02A,0xC180,0xB3E8,0xA79D,0x9CD5, 
0x93BF,0x8C84,0x8742,0x8412,0x8300,0x8412,0x8742,0x8C84, 
0x93BF,0x9CD5,0xA79D,0xB3E8,0xC180,0xD02A,0xDFA6,0xEFAF };
#elif (SINE_WAVE ==2)
// -3dB 1 KHz sine sampled at 48 KHz
Int16 XmitR_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x0B6C,0x16A6,0x217C,0x2BC0,0x3544,0x3DDF,0x456B, 
0x4BC7,0x50D7,0x5485,0x56C0,0x5780,0x56C0,0x5485,0x50D7, 
0x4BC7,0x456B,0x3DDF,0x3544,0x2BC0,0x217C,0x16A6,0x0B6C, 
0x0000,0xF494,0xE95A,0xDE84,0xD440,0xCABC,0xC221,0xBA95, 
0xB439,0xAF29,0xAB7B,0xA940,0xA880,0xA940,0xAB7B,0xAF29, 
0xB439,0xBA95,0xC221,0xCABC,0xD440,0xDE84,0xE95A,0xF494

};
#elif (SINE_WAVE ==3)
//0 dB 2 KHz sine sampled at 48 KHz
Int16 XmitR_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x205A,0x3E80,0x5863,0x6C41,0x78BE,0x7D00,0x78BE, 
0x6C41,0x5863,0x3E80,0x205A,0x0000,0xDFA6,0xC180,0xA79D, 
0x93BF,0x8742,0x8300,0x8742,0x93BF,0xA79D,0xC180,0xDFA6, 
0x0000,0x205A,0x3E80,0x5863,0x6C41,0x78BE,0x7D00,0x78BE, 
0x6C41,0x5863,0x3E80,0x205A,0x0000,0xDFA6,0xC180,0xA79D, 
0x93BF,0x8742,0x8300,0x8742,0x93BF,0xA79D,0xC180,0xDFA6 
};
#elif (SINE_WAVE ==4)
//-3 dB 2 KHz sine sampled at 48 KHz
Int16 XmitR_Sine[XMIT_BUFF_SIZE] = {
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A,
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A
};
#endif


Uint16 XmitL_Buff_index =0, XmitR_Buff_index=0;

#else// if(CONTENT == AUDIO_BYPASS)

#define AUD_BUFF_SIZE  256

//#pragma DATA_SECTION(RcvL_Buff,".xram_buf1");
//Int16 RcvL_Buff[AUD_BUFF_SIZE];
Int32 RcvL_Buff[AUD_BUFF_SIZE];

//#pragma DATA_SECTION(RcvR_Buff,".xram_buf2");
//Int16 RcvR_Buff[AUD_BUFF_SIZE];
Int32 RcvR_Buff[AUD_BUFF_SIZE];

Uint16 RcvL_Buff_index =0, RcvR_Buff_index=0;
#endif


I2S_Handle                  *hI2s;
   
Uint16 I2S_AudioBypass (void)
{
    PLLConfigInfo               PllConfig;
    PeripheralClockGateInfo     PeripheralClock;
    PortMapInfo                 PortMapping;
    I2S_Config                  I2sConfig;
#if (USE_DMA ==1)    
    DMA_ChanHandle              *hDmaXmitL;
    DMA_ChanHandle              *hDmaXmitR;
#if (CONTENT == AUDIO_BYPASS)
    DMA_ChanHandle              *hDmaRcvL;
    DMA_ChanHandle              *hDmaRcvR;            
#endif
    DMA_Config                  DmaConfigXmitL;
    DMA_Config                  DmaConfigXmitR;
#if (CONTENT == AUDIO_BYPASS)    
    DMA_Config                  DmaConfigRcvL;
    DMA_Config                  DmaConfigRcvR;            
#endif    
#endif
    Int16                       status;

   
    PllConfig.BypassPLL = 0;
    PllConfig.BypassRDiv = 1;
    PllConfig.EnableOutDiv2 = 1;
    PllConfig.BypassOutDiv = 1;
    PllConfig.VP = 749;
    PllConfig.VS = 0;
    PllConfig.RD = 0;
    PllConfig.OD = 0;
    SYS_PllSet(&PllConfig);       // target frequency = 49.152MHz

    // set up peripheral clock gating
    // clock gated =1
    // active =0
    PeripheralClock.MasterClockCG =0;
    PeripheralClock.I2S2CG =0;
    PeripheralClock.Timer2CG =1;
    PeripheralClock.Timer1CG =1;
    PeripheralClock.EmifCG =0;
    PeripheralClock.Timer0CG =1;
    PeripheralClock.I2S1CG =0;
    PeripheralClock.I2S0CG =0;
    PeripheralClock.MMC1CG =1;
    PeripheralClock.I2CCG =0;       
    PeripheralClock.CoprocCG =1;

    PeripheralClock.MMC0CG =1;
    PeripheralClock.Dma0CG =0;
    PeripheralClock.UARTCG =1;
    PeripheralClock.SPICG =1;
    PeripheralClock.I2S3CG =0;
    PeripheralClock.AnaRegCG =0;
    PeripheralClock.Dma3CG =0;
    PeripheralClock.Dma2CG =0;
    PeripheralClock.Dma1CG =0;
    PeripheralClock.USBCG =1;
    PeripheralClock.SARCG =0;
    PeripheralClock.LCDCG =0;

    SYS_PeripheralClockGating(&PeripheralClock);
    SYS_ResetPeripherals();

    SYS_GlobalIntEnable();

    PortMapping.SerialPort0 = SERIAL_PORT_MODE2;
    PortMapping.SerialPort1 = SERIAL_PORT_MODE2;
    PortMapping.ParallelPort = PARALLEL_PORT_MODE4;
    SYS_MapPort(&PortMapping);

    message_on_LCD();
        
    AIC3254_init();


#if (USE_DMA==1)

    hI2s = CSL_I2S_Open(I2S_2,I2S_CHANNEL_STEREO);
    if (hI2s == NULL)
        return 1;


    I2sConfig.IntEnable = 0;
    I2sConfig.eDataPack = I2S_DATAPACK_ENABLE;
    //I2sConfig.eTxMode = I2S_TXMODE_MASTER;
    I2sConfig.eTxMode = I2S_TXMODE_SLAVE;
    I2sConfig.eSignExt = I2S_SIGNEXT_ENABLE;
    I2sConfig.eDataType = I2S_MONO_DISABLE;
    I2sConfig.eWordLength = I2S_DATATX_WORDLEN_16;
    I2sConfig.eClkPol = I2S_TX_CLKPOL_FALLING;
    I2sConfig.eFsPol = I2S_FSPOL_LOW;
    I2sConfig.eDataDelay = I2S_DATADELAY_ONEBIT;
    I2sConfig.eDataFormat = I2S_DATAFORMAT_LJUST;
    I2sConfig.eFsdiv = I2S_FSDIV16;         // i2s clk = 768KHz, FS clk = 768KHz/16 = 48KHz
    I2sConfig.eClkdiv = I2S_CLKDIV32;       // system clk = 49.152MHz, i2s clk = 49.152/64 = 768KHz
    
    status = CSL_I2S_Configure(hI2s, &I2sConfig);
    if(status != CSL_OK)
        return 1;


    // set up DMA
    CSL_DMA_DrvInit();
    
#if(CONTENT == AUDIO_BYPASS)    

    hDmaXmitL = CSL_DMA_RequestChan(DMA_I2S2);
    if(hDmaXmitL == NULL)
        return 1;
      
    DmaConfigXmitL.autoMode = DMA_AUTORELOAD_ENABLE;
    DmaConfigXmitL.destDataSize = DMA_DEST_DATASIZE_32;
    DmaConfigXmitL.burstLen = DMA_TXBURST_1WORD;
    DmaConfigXmitL.srcDataSize = DMA_SRC_DATASIZE_32;
    DmaConfigXmitL.dmaEvt = DMA_EVT_I2S2_RX;
    DmaConfigXmitL.chanDir = DMA_WRITE;
    DmaConfigXmitL.trigger = DMA_EVENT_TRIGGER;
    DmaConfigXmitL.trfType = DMA_TRANSFER_IO_MEMORY;
    DmaConfigXmitL.srcAddr = (Uint32)RcvL_Buff;
    DmaConfigXmitL.destAddr = 0x2A08;
    DmaConfigXmitL.dataLen = 2*AUD_BUFF_SIZE;
    DmaConfigXmitL.IntEnable = 0;
    CSL_DMA_ConfigChan(hDmaXmitL,&DmaConfigXmitL,NULL);
    
    CSL_DMA_StartTransfer(hDmaXmitL);


    hDmaXmitR = CSL_DMA_RequestChan(DMA_I2S2);
    if(hDmaXmitR == NULL)
        return 1;
      
    DmaConfigXmitR.autoMode = DMA_AUTORELOAD_ENABLE;
    DmaConfigXmitR.destDataSize = DMA_DEST_DATASIZE_32;
    DmaConfigXmitR.burstLen = DMA_TXBURST_1WORD;
    DmaConfigXmitR.srcDataSize = DMA_SRC_DATASIZE_32;
    DmaConfigXmitR.dmaEvt = DMA_EVT_I2S2_RX;
    DmaConfigXmitR.chanDir = DMA_WRITE;
    DmaConfigXmitR.trigger = DMA_EVENT_TRIGGER;
    DmaConfigXmitR.trfType = DMA_TRANSFER_IO_MEMORY;
    DmaConfigXmitR.srcAddr = (Uint32)RcvR_Buff;
    DmaConfigXmitR.destAddr = 0x2A0C;
    DmaConfigXmitR.dataLen = 2*AUD_BUFF_SIZE;
    DmaConfigXmitR.IntEnable = 0;
    CSL_DMA_ConfigChan(hDmaXmitR,&DmaConfigXmitR,NULL);
    
    CSL_DMA_StartTransfer(hDmaXmitR);

    hDmaRcvL = CSL_DMA_RequestChan(DMA_I2S2);
    if(hDmaRcvL == NULL)
        return 1;
      
    DmaConfigRcvL.autoMode = DMA_AUTORELOAD_ENABLE;
    DmaConfigRcvL.destDataSize = DMA_DEST_DATASIZE_32;
    DmaConfigRcvL.burstLen = DMA_TXBURST_1WORD;
    DmaConfigRcvL.srcDataSize = DMA_SRC_DATASIZE_32;
    DmaConfigRcvL.dmaEvt = DMA_EVT_I2S2_RX;
    DmaConfigRcvL.chanDir = DMA_READ;
    DmaConfigRcvL.trigger = DMA_EVENT_TRIGGER;
    DmaConfigRcvL.trfType = DMA_TRANSFER_IO_MEMORY;
    DmaConfigRcvL.srcAddr = 0x2A28;
    DmaConfigRcvL.destAddr = (Uint32)RcvL_Buff;
    DmaConfigRcvL.dataLen = 2*AUD_BUFF_SIZE;
    DmaConfigRcvL.IntEnable = 0;
    CSL_DMA_ConfigChan(hDmaRcvL,&DmaConfigRcvL,NULL);
    
    CSL_DMA_StartTransfer(hDmaRcvL);


    hDmaRcvR = CSL_DMA_RequestChan(DMA_I2S2);
    if(hDmaRcvR == NULL)
        return 1;
      
    DmaConfigRcvR.autoMode = DMA_AUTORELOAD_ENABLE;
    DmaConfigRcvR.destDataSize = DMA_DEST_DATASIZE_32;
    DmaConfigRcvR.burstLen = DMA_TXBURST_1WORD;
    DmaConfigRcvR.srcDataSize = DMA_SRC_DATASIZE_32;
    DmaConfigRcvR.dmaEvt = DMA_EVT_I2S2_RX;
    DmaConfigRcvR.chanDir = DMA_READ;
    DmaConfigRcvR.trigger = DMA_EVENT_TRIGGER;
    DmaConfigRcvR.trfType = DMA_TRANSFER_IO_MEMORY;
    DmaConfigRcvR.srcAddr = 0x2A2C;
    DmaConfigRcvR.destAddr = (Uint32)RcvR_Buff;
    DmaConfigRcvR.dataLen = 2*AUD_BUFF_SIZE;
    DmaConfigRcvR.IntEnable = 0;
    CSL_DMA_ConfigChan(hDmaRcvR,&DmaConfigRcvR,NULL);
    
    CSL_DMA_StartTransfer(hDmaRcvR);


#else// if(CONTENT == SINE_WAVE_1K)    
    hDmaXmitL = CSL_DMA_RequestChan(DMA_I2S2);
    if(hDmaXmitL == NULL)
        return 1;
      
    DmaConfigXmitL.autoMode = DMA_AUTORELOAD_ENABLE;
    DmaConfigXmitL.destDataSize = DMA_DEST_DATASIZE_32;
    DmaConfigXmitL.burstLen = DMA_TXBURST_1WORD;
    DmaConfigXmitL.srcDataSize = DMA_SRC_DATASIZE_32;
    DmaConfigXmitL.dmaEvt = DMA_EVT_I2S2_RX;
    DmaConfigXmitL.chanDir = DMA_WRITE;
    DmaConfigXmitL.trigger = DMA_EVENT_TRIGGER;
    DmaConfigXmitL.trfType = DMA_TRANSFER_IO_MEMORY;
    DmaConfigXmitL.srcAddr = (Uint32)XmitL_Sine;
    DmaConfigXmitL.destAddr = 0x2A08;
    DmaConfigXmitL.dataLen = 2*48;
    DmaConfigXmitL.IntEnable = 0;
    CSL_DMA_ConfigChan(hDmaXmitL,&DmaConfigXmitL,NULL);
    
    CSL_DMA_StartTransfer(hDmaXmitL);


    hDmaXmitR = CSL_DMA_RequestChan(DMA_I2S2);
    if(hDmaXmitR == NULL)
        return 1;
      
    DmaConfigXmitR.autoMode = DMA_AUTORELOAD_ENABLE;
    DmaConfigXmitR.destDataSize = DMA_DEST_DATASIZE_32;
    DmaConfigXmitR.burstLen = DMA_TXBURST_1WORD;
    DmaConfigXmitR.srcDataSize = DMA_SRC_DATASIZE_32;
    DmaConfigXmitR.dmaEvt = DMA_EVT_I2S2_RX;
    DmaConfigXmitR.chanDir = DMA_WRITE;
    DmaConfigXmitR.trigger = DMA_EVENT_TRIGGER;
    DmaConfigXmitR.trfType = DMA_TRANSFER_IO_MEMORY;
    DmaConfigXmitR.srcAddr = (Uint32)XmitR_Sine;
    DmaConfigXmitR.destAddr = 0x2A0C;
    DmaConfigXmitR.dataLen = 2*48;
    DmaConfigXmitR.IntEnable = 0;
    CSL_DMA_ConfigChan(hDmaXmitR,&DmaConfigXmitR,NULL);
    
    CSL_DMA_StartTransfer(hDmaXmitR);
#endif

#else //#if (USE_DMA)
// use CPU
    hI2s = CSL_I2S_Open(I2S_2,I2S_CHANNEL_STEREO);
    if (hI2s == NULL)
        return 1;


    I2sConfig.IntEnable = 1;
    I2sConfig.eDataPack = I2S_DATAPACK_ENABLE;
    I2sConfig.eTxMode = I2S_TXMODE_MASTER;
    I2sConfig.eSignExt = I2S_SIGNEXT_ENABLE;
    I2sConfig.eDataType = I2S_MONO_DISABLE;
    I2sConfig.eWordLength = I2S_DATATX_WORDLEN_16;
    I2sConfig.eClkPol = I2S_TX_CLKPOL_FALLING;
    I2sConfig.eFsPol = I2S_FSPOL_LOW;
    I2sConfig.eDataDelay = I2S_DATADELAY_ONEBIT;
    I2sConfig.eDataFormat = I2S_DATAFORMAT_LJUST;
    I2sConfig.eFsdiv = I2S_FSDIV16;         // i2s clk = 768KHz, FS clk = 768KHz/16 = 48KHz
    I2sConfig.eClkdiv = I2S_CLKDIV32;       // system clk = 49.152MHz, i2s clk = 49.152/64 = 768KHz

  
    status = CSL_I2S_Configure(hI2s, &I2sConfig);
    if(status != CSL_OK)
        return 1;
    
    LLC_I2S_writeLdata_LSW(hI2s->regs, 0);
    LLC_I2S_writeLdata_MSW(hI2s->regs, 0);
    LLC_I2S_writeRdata_LSW(hI2s->regs, 0);
    LLC_I2S_writeRdata_MSW(hI2s->regs, 0);

#endif //#if (USE_DMA)

    CSL_I2S_Enable(hI2s);

	return 0;
}




interrupt void I2S2_TX_Isr (void)
{
#if (USE_DMA==0)
#if (CONTENT == SINE_WAVE_1K)  
    LLC_I2S_writeLdata_LSW(hI2s->regs, *(XmitL_Sine + XmitL_Buff_index));
    //LLC_I2S_writeLdata_MSW(hI2s->regs, 0);
    LLC_I2S_writeRdata_LSW(hI2s->regs, *(XmitR_Sine + XmitR_Buff_index));
    //LLC_I2S_writeRdata_MSW(hI2s->regs, 0);

    XmitL_Buff_index++;
    XmitR_Buff_index++;
    if(XmitL_Buff_index == XMIT_BUFF_SIZE -1)
    {
        XmitL_Buff_index = 0;
    }
    if(XmitR_Buff_index == XMIT_BUFF_SIZE -1)
    {
        XmitR_Buff_index = 0;
    }
#else //if(CONTENT == AUDIO_BYPASS)

    Uint16 txL_index =  RcvL_Buff_index;
    Uint16 txR_index =  RcvR_Buff_index;
    
    if(RcvL_Buff_index ==0)
    {
        txL_index = AUD_BUFF_SIZE -1;
    }
    else
    {
        txL_index = RcvL_Buff_index -1;
    }

    if(RcvR_Buff_index ==0)
    {
        txR_index = AUD_BUFF_SIZE -1;
    }
    else
    {
        txR_index = RcvR_Buff_index -1;
    }
    LLC_I2S_writeLdata_LSW(hI2s->regs, *(RcvL_Buff + txL_index));
    LLC_I2S_writeRdata_LSW(hI2s->regs, *(RcvR_Buff + txR_index));

#endif
#endif
}

interrupt void I2S2_RX_Isr (void)
{
#if (USE_DMA==0)    
#if (CONTENT == SINE_WAVE_1K)      
    LLC_I2S_readLdata_LSW(hI2s->regs);
    LLC_I2S_readLdata_MSW(hI2s->regs);
    LLC_I2S_readRdata_LSW(hI2s->regs);
    LLC_I2S_readRdata_MSW(hI2s->regs);
#else //if(CONTENT ==AUDIO_BYPASS)
    *(RcvL_Buff + RcvL_Buff_index) = LLC_I2S_readLdata_LSW(hI2s->regs);
    *(RcvR_Buff + RcvR_Buff_index) = LLC_I2S_readRdata_LSW(hI2s->regs);
    RcvL_Buff_index++;
    RcvR_Buff_index++;
    if(RcvL_Buff_index == AUD_BUFF_SIZE -1)
    {
        RcvL_Buff_index = 0;
    }
    if(RcvR_Buff_index == AUD_BUFF_SIZE -1)
    {
        RcvR_Buff_index = 0;
    }    
#endif
#endif
}

