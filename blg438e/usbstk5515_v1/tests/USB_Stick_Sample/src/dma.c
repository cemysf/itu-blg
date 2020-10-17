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
#include "register_dma.h"
#include "register_cpu.h"
#include "dma.h"


#define XMIT_BUFF_SIZE  48
#define AUTO_RELOAD     1
#define SINE_WAVE       2

// -3dB 1 KHz sine sampled at 48 KHz
Int16 XmitL_Sine_1K[XMIT_BUFF_SIZE] = {
0x0000,0x0B6C,0x16A6,0x217C,0x2BC0,0x3544,0x3DDF,0x456B, 
0x4BC7,0x50D7,0x5485,0x56C0,0x5780,0x56C0,0x5485,0x50D7, 
0x4BC7,0x456B,0x3DDF,0x3544,0x2BC0,0x217C,0x16A6,0x0B6C, 
0x0000,0xF494,0xE95A,0xDE84,0xD440,0xCABC,0xC221,0xBA95, 
0xB439,0xAF29,0xAB7B,0xA940,0xA880,0xA940,0xAB7B,0xAF29, 
0xB439,0xBA95,0xC221,0xCABC,0xD440,0xDE84,0xE95A,0xF494
};

//-3 dB 2 KHz sine sampled at 48 KHz
Int16 XmitL_Sine_2K[XMIT_BUFF_SIZE] = {
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A,
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A
};



// -3dB 1 KHz sine sampled at 48 KHz
Int16 XmitR_Sine_1K[XMIT_BUFF_SIZE] = {
0x0000,0x0B6C,0x16A6,0x217C,0x2BC0,0x3544,0x3DDF,0x456B, 
0x4BC7,0x50D7,0x5485,0x56C0,0x5780,0x56C0,0x5485,0x50D7, 
0x4BC7,0x456B,0x3DDF,0x3544,0x2BC0,0x217C,0x16A6,0x0B6C, 
0x0000,0xF494,0xE95A,0xDE84,0xD440,0xCABC,0xC221,0xBA95, 
0xB439,0xAF29,0xAB7B,0xA940,0xA880,0xA940,0xAB7B,0xAF29, 
0xB439,0xBA95,0xC221,0xCABC,0xD440,0xDE84,0xE95A,0xF494
};

//-3 dB 2 KHz sine sampled at 48 KHz
Int16 XmitR_Sine_2K[XMIT_BUFF_SIZE] = {
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A,
0x0000,0x16A6,0x2BC0,0x3DDF,0x4BC7,0x5485,0x5780,0x5485, 
0x4BC7,0x3DDF,0x2BC0,0x16A6,0x0000,0xE95A,0xD440,0xC221, 
0xB439,0xAB7B,0xA880,0xAB7B,0xB439,0xC221,0xD440,0xE95A
};



Int16 RcvL_Sine[XMIT_BUFF_SIZE];
Int16 RcvR_Sine[XMIT_BUFF_SIZE];
Uint16 DMA_Count =0, Error_Count_L =0, Error_Count_R =0;
Uint16 DMA_Done = 0;
extern Uint16 fSineWave;

void set_dma1_ch0_stop(void)
{
	Uint16 temp;
//  DMA stop
    temp = DMA1_CH0_TC_MSW;
	temp &= 0x7FFF;
	DMA1_CH0_TC_MSW = temp;    
}

void set_dma0_ch0_stop(void)
{
	Uint16 temp;
//  DMA stop
    temp = DMA0_CH0_TC_MSW;
	temp &= 0x7FFF;
	DMA0_CH0_TC_MSW = temp;    
}


void set_dma1_ch1_stop(void)
{
	Uint16 temp;
//  DMA stop
    temp = DMA1_CH1_TC_MSW;
	temp &= 0x7FFF;
	DMA1_CH1_TC_MSW = temp;    
}

void set_dma0_ch1_stop(void)
{
	Uint16 temp;
//  DMA stop
    temp = DMA0_CH1_TC_MSW;
	temp &= 0x7FFF;
	DMA0_CH1_TC_MSW = temp;    
}

Uint16 set_dma1_ch0_i2s2_Lout(void)
{
	Uint16 temp; 
	Uint32 add;

    DMA1_CH0_TC_LSW = XMIT_BUFF_SIZE*2;

#if(AUTO_RELOAD ==1)        
    DMA1_CH0_TC_MSW = 0x3204;     //src incre, destination fix, sync, auto  
#else
    DMA1_CH0_TC_MSW = 0x2204;     //src incre, destination fix, sync, No auto  
#endif
                
	temp = DMA1_CH10_EVENT_SRC;
    DMA1_CH10_EVENT_SRC = temp | 0x0001;   // I2S2 transmit event
    
    if(fSineWave ==1)
    {
        add = (Uint32)XmitL_Sine_1K;        
    }
    else
    {
        add = (Uint32)XmitL_Sine_2K;        
    }
    
    add = (add<<1) + 0x10000;		// change word address to byte address and add DARAM offset for DMA
    DMA1_CH0_SRC_LSW = (Uint16)add;
    
    DMA1_CH0_SRC_MSW = 0xFFFF & (add >> 16);
    
    DMA1_CH0_DST_LSW = 0x2808;      // is20 transmit left data register lsw
    
//  DMA starts   
    temp = DMA1_CH0_TC_MSW;
	temp |= 0x8000;
	DMA1_CH0_TC_MSW = temp;

    return SUCCESS;
}

Uint16 set_dma0_ch0_i2s0_Lout(void)
{
	Uint16 temp; 
	Uint32 add;

    DMA0_CH0_TC_LSW = XMIT_BUFF_SIZE*2;

#if(AUTO_RELOAD ==1)        
    DMA0_CH0_TC_MSW = 0x3204;     //src incre, destination fix, sync, auto  
#else
    DMA0_CH0_TC_MSW = 0x2204;     //src incre, destination fix, sync, No auto  
#endif
                
	temp = DMA0_CH10_EVENT_SRC;
    DMA0_CH10_EVENT_SRC = temp | 0x0001;   // I2S2 transmit event
    
    if(fSineWave ==1)
    {
        add = (Uint32)XmitL_Sine_1K;        
    }
    else
    {
        add = (Uint32)XmitL_Sine_2K;        
    }
    
    add = (add<<1) + 0x10000;		// change word address to byte address and add DARAM offset for DMA
    DMA0_CH0_SRC_LSW = (Uint16)add;
    
    DMA0_CH0_SRC_MSW = 0xFFFF & (add >> 16);
    
    DMA0_CH0_DST_LSW = 0x2808;      // is20 transmit left data register lsw
    
//  DMA starts   
    temp = DMA0_CH0_TC_MSW;
	temp |= 0x8000;
	DMA0_CH0_TC_MSW = temp;

    return SUCCESS;
}


Uint16 set_dma1_ch1_i2s2_Rout(void)
{	
	Uint16 temp;
	Uint32 add;

    DMA1_CH1_TC_LSW = XMIT_BUFF_SIZE*2;
//    DMA0_CH1_TC_LSW = 8;

#if(AUTO_RELOAD ==1)            
    DMA1_CH1_TC_MSW = 0x3204;     //src incre, destination fix, sync, auto
#else    
    DMA1_CH1_TC_MSW = 0x2204;     //src incre, destination fix, sync, No auto
#endif
            
	temp = DMA1_CH10_EVENT_SRC;
    DMA1_CH10_EVENT_SRC = temp | 0x0100;   // I2S2 transmit event
    
    if(fSineWave ==1)
    {
        add = (Uint32)XmitR_Sine_1K;        
    }
    else
    {
        add = (Uint32)XmitR_Sine_2K;        
    }    
    add = (add<<1) + 0x10000;		//// change word address to byte address and add DARAM offset for DMA
    DMA1_CH1_SRC_LSW = (Uint16)add;
    
    DMA1_CH1_SRC_MSW = 0xFFFF & (add >> 16);
    
    DMA1_CH1_DST_LSW = 0x280C;      // is20 transmit right data register lsw

// DMA starts    
    temp = DMA1_CH1_TC_MSW;
	temp |= 0x8000;
	DMA1_CH1_TC_MSW = temp;


    return SUCCESS;
}

Uint16 set_dma0_ch1_i2s0_Rout(void)
{	
	Uint16 temp;
	Uint32 add;

    DMA0_CH1_TC_LSW = XMIT_BUFF_SIZE*2;
//    DMA0_CH1_TC_LSW = 8;

#if(AUTO_RELOAD ==1)            
    DMA0_CH1_TC_MSW = 0x3204;     //src incre, destination fix, sync, auto
#else    
    DMA0_CH1_TC_MSW = 0x2204;     //src incre, destination fix, sync, No auto
#endif
            
	temp = DMA1_CH10_EVENT_SRC;
    DMA0_CH10_EVENT_SRC = temp | 0x0100;   // I2S2 transmit event
    
    if(fSineWave ==1)
    {
        add = (Uint32)XmitR_Sine_1K;        
    }
    else
    {
        add = (Uint32)XmitR_Sine_2K;        
    }    
    add = (add<<1) + 0x10000;		//// change word address to byte address and add DARAM offset for DMA
    DMA0_CH1_SRC_LSW = (Uint16)add;
    
    DMA0_CH1_SRC_MSW = 0xFFFF & (add >> 16);
    
    DMA0_CH1_DST_LSW = 0x280C;      // is20 transmit right data register lsw

// DMA starts    
    temp = DMA0_CH1_TC_MSW;
	temp |= 0x8000;
	DMA0_CH1_TC_MSW = temp;


    return SUCCESS;
}


void enable_dma_int(void)
{
    DMA_MSK = 0xFFFF;     // enable all interrupts
    DMA_IFR = 0xFFFF;     // clear interrupt flags
}

#if 0
interrupt void DMA_Isr(void)
{   
    Uint16 temp,i;
    
    temp = IFR0;
    IFR0 = temp;  

	temp = DMA_IFR;
    DMA_IFR = temp;     // clear interrupt flags

#if(AUTO_RELOAD ==0) 
    if(temp&0xF000 != 0)   // ch 2 of DMA3
    {
        for(i=0; i < XMIT_BUFF_SIZE; i++)
        {
            if (XmitL_Sine[i] != RcvL_Sine[i])
            {
    	        Error_Count_L++;
    	        break;
            }
		}
        for(i=0; i < XMIT_BUFF_SIZE; i++)
        {
       		if (XmitR_Sine[i] != RcvR_Sine[i])
        	{
    	    	Error_Count_R++;
    		    break;
    	    }
	    }//for(temp=0; temp < XMIT_BUFF_SIZE; temp++)
        DMA_Done = 1;
    }
#endif    	    
	    
}
#endif
