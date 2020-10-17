/**********************************************************************
**+-----------------------------------------------------------------+**
**|                            ****                                 |**
**|                            ****                                 |**
**|                            ******o***                           |**
**|                      ********_///_****                          |**
**|                      ***** /_//_/ ****                          |**
**|                       ** ** (__/ ****                           |**
**|                           *********                             |**
**|                            ****                                 |**
**|                            ***                                  |**
**|                                                                 |**
**|   Copyright (c) 2006 - 2010    Texas Instruments Incorporated   |**
**|                        ALL RIGHTS RESERVED                      |**
**|                                                                 |**
**| Permission is hereby granted to licensees of Texas Instruments  |**
**| Incorporated (TI) products to use this computer program for     |**
**| the sole purpose of implementing a licensee product based       |**
**| on TI products.No other rights to reproduce, use, or            |**
**| disseminate this computer program, whether in part or in whole, |**
**| are granted.TI makes no representation or warranties with       |**
**| respect to the performance of this computer program, and        |**
**| specifically disclaims any responsibility for any damages,      |**
**| special or consequential,connected with the use of this program.|**
**|                                                                 |**
**+-----------------------------------------------------------------+**
**********************************************************************/
#include "data_types.h"
#include "timer.h"
#include "register_cpu.h"

Uint16 fTimer =0;

void Timer0Init(void)
{

	/*  Timer0 Initialization */
// timer interval 0.5sec (2Hz)
// prescale = 1011 (devide by 4096)
// 98.304M/4096 = 24K 
// 24K/12K = 2Hz (12K = 0x2EE0)

	/* TIM0 EN | AutoReload disable | Prescale = 0(100/2 = 50MHz) ==> 20nsec */
	*CPU_TIM0_CTRL = 0x802E; 	// autoReload
    //*CPU_TIM0_CTRL = 0x802C; 	// disable autoReload

	*CPU_TIM0_PLWR = 0x2EE0;
	*CPU_TIM0_PHWR = 0x0000; 

	*CPU_TIM0_CLWR = 0x0000;
	*CPU_TIM0_CHWR = 0x0000;
	
	/*  Clearing timer Aggregation register*/
	*CPU_TIMINT_AGGR = 0x0007;

	/*  enable timer0 int flag*/
	*CPU_TIM0_IER = 0x0001;
}

void StartTimer0(void)
{
	/* Start the Timer 0*/
	*CPU_TIM0_CTRL = *CPU_TIM0_CTRL | 0x0001; 
}


interrupt void Timer_isr(void)
{

    // clear timer int flag
    IFR0 = IFR0&0x0010; 
    
	/*  clear timer0 int flag*/
	*CPU_TIM0_IER = 0x0001;
	    
	/*	Clear Timer0 bit in Timer Aggregate register*/
	*CPU_TIMINT_AGGR = *CPU_TIMINT_AGGR | 0x0001 ;	

	fTimer=1;
    //StartTimer0();
}

