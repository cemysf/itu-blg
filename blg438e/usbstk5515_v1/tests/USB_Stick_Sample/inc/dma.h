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
**|         Copyright (c); 2006 - 2010    Texas Instruments Incorporated     |**
**|                        ALL RIGHTS RESERVED                              |**
**|                                                                         |**
**| Permission is hereby granted to licensees of Texas Instruments          |**
**| Incorporated (TI); products to use this computer program for the sole    |**
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

#ifndef _DMA_H_
#define _DMA_H_

Uint16 set_dma0_ch0_i2s0_Lout(void);
Uint16 set_dma0_ch1_i2s0_Rout(void);
Uint16 set_dma3_ch0_i2s1_Lin(void);
Uint16 set_dma3_ch1_i2s1_Rin(void);
Uint16 set_dma1_ch0_i2s2_Lout(void);
Uint16 set_dma1_ch1_i2s2_Rout(void);
Uint16 set_dma2_ch0_i2s3_Lin(void);
Uint16 set_dma2_ch1_i2s3_Rin(void);
Uint16 set_dma3_ch0_i2s1_Lout(void);
Uint16 set_dma3_ch1_i2s1_Rout(void);
Uint16 set_dma2_ch0_i2s3_Lin(void);
Uint16 set_dma2_ch1_i2s3_Rin(void);
void set_dma1_ch0_stop(void);
void set_dma1_ch1_stop(void);
void set_dma0_ch0_stop(void);
void set_dma0_ch1_stop(void);
void enable_dma_int(void);
interrupt void DMA_Isr(void);

#endif
