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
#include <stdio.h>
#include "data_types.h"
#include "register_system.h"
#include "register_cpu.h"
#include "rtc.h"
#include "control.h"
#include "i2s.h"
#include "dma.h"
#include "timer.h"
#include "lcd.h"
#include "sar.h"
#include "usbstk5515.h"
#include "usbstk5515_led.h"

void InitSystem(void);
void ConfigPort(void);
void SYS_GlobalIntEnable(void);
void SYS_GlobalIntDisable(void);
void BlinkLED(void);
void GenerateAudioTone(void);

Uint16 fSineWave = 0;
Uint16 f1KToneOn =0;
Uint16 f2KToneOn =0;

extern Uint16 fTimer;
extern Uint16 Flag_RTC;
extern Uint16 Conunt_RTC;
extern Uint16 halfSecCnt;
extern void AIC3254_init(void);
extern Int16 oled_test();

void main(void)
{
	Uint16 temp, key, i;
	
    
    InitSystem();
    ConfigPort();

    SYS_GlobalIntEnable();
    
    IER0 = 0x0010;      // enable timer int      
    IER1 = 0x0004;      // enable RTC int
    Timer0Init();
	reset_RTC();
	enable_rtc_second_int();

	AIC3254_init();
	set_i2s0_slave();
    enable_i2s0();
	StartTimer0();
	
	SYS_EXBUSSEL = 0x6100;	 // Configure External bus
	oled_test();             // Set display
	USBSTK5515_ULED_init( ); // Configure user LEDs
    Init_SAR();              // Initialize SAR for switches
    USBSTK5515_ULED_setall( 0x00 );
    
    while(1)
    {
		//*(ioport volatile unsigned *)0x0001 = 0x03FF;
		//asm("	idle");

        BlinkLED();
		GenerateAudioTone();
#if 1		
		for ( i = 0 ; i < 4 ; i++ )
        {
            USBSTK5515_ULED_on( i );       // Turn on user LED i
            USBSTK5515_waitusec( 50000 );
        }
        for ( i = 0 ; i < 4 ; i++ )
        {
            USBSTK5515_ULED_off( i ); // Turn off user LED i
            USBSTK5515_waitusec( 50000 );
        }
#else
		/* Get Switch values an toggle LEDs accordingly */
    	key = Get_Sar_Key();
    	if((key == SW1))   // If SW1 pressed
    	{
    		USBSTK5515_ULED_toggle( 0 );  // Toggle DS2 (GREEN LED)
    	}
    	if((key == SW2))   // If SW2 pressed
    	{
    		USBSTK5515_ULED_toggle( 3 );  // Toggle DS5 (BLUE LED)
    	}
    	if((key == SW12))   // If SW1 and SW2 pressed
    	{
    		USBSTK5515_ULED_toggle( 1 );  // Toggle DS3 (RED LED)
    		USBSTK5515_ULED_toggle( 2 );  // Toggle DS4 (YELLOW LED)
    	}
#endif
	}

}

void InitSystem(void)
{
	Uint16 i;
// PLL set up from RTC
    // bypass PLL
    CONFIG_MSW = 0x0;

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

// clock gating
// enable all clocks
    IDLE_PCGCR = 0;
    IDLE_PCGCR_MSW = 0xFF84;
    

// reset peripherals
    PER_RSTCOUNT = 0x02;
    PER_RESET = 0x00fb;    
    for (i=0; i< 200; i++);
    
}

void ConfigPort(void)
{
    //  configure ports
    PERIPHSEL0 = 0x6900;        // parallel port: mode 6, serial port1: mode 2, serial port0: mode1 
    
}


void SYS_GlobalIntEnable(void)
{
    asm(" BIT (ST1, #ST1_INTM) = #0");
}

void SYS_GlobalIntDisable(void)
{
    asm(" BIT (ST1, #ST1_INTM) = #1");
}


static toggleLED(void)
{
	Uint16 temp;

    temp = ST1_55;
    if((temp&0x2000) == 0)
    {
        // turn on LED
        temp |= 0x2000;
    }
    else
    {
        // turn off LED
        temp &=0xDFFF;
    }
    ST1_55 = temp; 

}


void BlinkLED(void)
{
#if 1
	if(fSineWave==1)
	{
   		if(Flag_RTC ==1)
		{
      		Flag_RTC =0;
			toggleLED();
		}
	
	}
	else
	{
   		if(fTimer ==1)
		{
      		fTimer =0;
			toggleLED();
		}
	}


#else
   	if(Flag_RTC ==1)
	{
      Flag_RTC =0;
		toggleLED();
	}
#endif
}

void GenerateAudioTone(void)
{
	if(Conunt_RTC < 10)
	{
		if(f1KToneOn ==1)
			return;
		// 1KHz sine wave
		fSineWave = 1;
		f1KToneOn =1;
		f2KToneOn =0;
        set_dma0_ch0_stop();
    	set_dma0_ch1_stop();
        set_dma0_ch0_i2s0_Lout();
	    set_dma0_ch1_i2s0_Rout();
	}
	else if (Conunt_RTC < 20)
	{
		if(f2KToneOn ==1)
			return;
		// 2KHz sine wave
		fSineWave = 0;
		f1KToneOn =0;
		f2KToneOn =1;
        set_dma0_ch0_stop();
    	set_dma0_ch1_stop();
        set_dma0_ch0_i2s0_Lout();
	    set_dma0_ch1_i2s0_Rout();
	}
	else
	{
		Conunt_RTC =0;
		f1KToneOn =0;
		f2KToneOn =1;

	}
}
