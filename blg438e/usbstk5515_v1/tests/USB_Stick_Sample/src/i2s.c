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
#include "data_types.h"
#include "register_cpu.h"
#include "i2s.h"

#define WORD_8		0
#define WORD_16		0x04
#define WORD_24		0x07
#define WORD_32		0x08

#define WORD_SIZE	WORD_16	 

#define FS_8		0
#define FS_16		0x1
#define FS_32		0x2
#define FS_64		0x3
#define FS_128		0x4
#define FS_256		0x5

#define FS_DIV		FS_32

#define BUF_SIZE 	48
Uint16 I2S_RCV_L[BUF_SIZE];
Uint16 I2S_RCV_R[BUF_SIZE];
Uint16 Buf_Address =0;


Uint16 set_i2s2_master(void)
{
    Uint16 temp=0;

	temp = WORD_SIZE <<2;
	temp |= 0x0082;				// Master, Pack
    i2s2_write_CR(temp);        // Master, I2S, 16 bit
    temp = i2s2_read_CR();
    
	temp = FS_DIV <<3;
	temp |= 0x0005; 				// clock = CPU / 4 
    i2s2_write_SRGR(temp);       
    
#if(USE_DMA ==1)    
    i2s2_write_INT_MASK(0);         // Disable I2S interrupt
#else
    i2s2_write_INT_MASK(0x20);         // Tx stereo interrupt

    i2s2_write_TXL_LSW(0x5678);
    i2s2_write_TXL_MSW(0x1234);
    i2s2_write_TXR_LSW(0x5678);
    i2s2_write_TXR_MSW(0x1234);
#endif

        
    return SUCCESS;
}




Uint16 set_i2s0_master(void)
{
    Uint16 temp=0;

	temp = WORD_SIZE <<2;
	temp |= 0x0082;				// Master, Pack
    i2s0_write_CR(temp);        // Master, I2S, 16 bit
    temp = i2s0_read_CR();
    
	temp = FS_DIV <<3;
	temp |= 0x0005; 				// clock = CPU / 4 
    i2s0_write_SRGR(temp);       
    
#if(USE_DMA ==1)    
    i2s0_write_INT_MASK(0);         // Disable I2S interrupt
#else
    i2s0_write_INT_MASK(0x20);         // Tx stereo interrupt

    i2s0_write_TXL_LSW(0x5678);
    i2s0_write_TXL_MSW(0x1234);
    i2s0_write_TXR_LSW(0x5678);
    i2s0_write_TXR_MSW(0x1234);
#endif

        
    return SUCCESS;
}

Uint16 set_i2s0_slave(void)
{
    Uint16 temp=0;

	temp = WORD_SIZE <<2;
	temp |= 0x0080;				// Slave, Pack
    i2s0_write_CR(temp);        // Slave, I2S, 16 bit
    temp = i2s0_read_CR();
    
#if(USE_DMA ==1)    
    i2s0_write_INT_MASK(0);         // Disable I2S interrupt
#else
    i2s0_write_INT_MASK(0x20);         // Tx stereo interrupt

    i2s0_write_TXL_LSW(0x5678);
    i2s0_write_TXL_MSW(0x1234);
    i2s0_write_TXR_LSW(0x5678);
    i2s0_write_TXR_MSW(0x1234);
#endif

        
    return SUCCESS;
}
