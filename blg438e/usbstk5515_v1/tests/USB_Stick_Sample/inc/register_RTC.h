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
#ifndef _REG_RTC_H_
#define _REG_RTC_H_

//****************************************************************************************
//        RTC Register Addresses
//****************************************************************************************
#define RTC_MSEC             *(ioport volatile unsigned *)0x1904        // RTC MilliSeconds Register
#define RTC_SEC              *(ioport volatile unsigned *)0x1908        // RTC Seconds Register
#define RTC_MIN              *(ioport volatile unsigned *)0x190C        // RTC Minutes Register
#define RTC_HOUR             *(ioport volatile unsigned *)0x1910        // RTC Hours Register
#define RTC_DAY              *(ioport volatile unsigned *)0x1914        // RTC Days Register
#define RTC_MONTH            *(ioport volatile unsigned *)0x1918        // RTC Months Register
#define RTC_YEAR             *(ioport volatile unsigned *)0x191C        // RTC Years Register

#define RTC_MSECAL           *(ioport volatile unsigned *)0x1905        // RTC MilliSeconds Alarm Register
#define RTC_SECAL            *(ioport volatile unsigned *)0x1909        // RTC Seconds Alarm Register
#define RTC_MINAL            *(ioport volatile unsigned *)0x190D        // RTC Minutes Alarm Register
#define RTC_HOURAL           *(ioport volatile unsigned *)0x1911        // RTC Hours Alarm Register
#define RTC_DAYAL            *(ioport volatile unsigned *)0x1915        // RTC Days Alarm Register
#define RTC_MONTHAL          *(ioport volatile unsigned *)0x1919        // RTC Months Alarm Register
#define RTC_YEARAL           *(ioport volatile unsigned *)0x191D        // RTC Years Alarm Register

#define RTC_CTR             *(ioport volatile unsigned *)0x1900        // RTC Control Register
#define RTC_UPDT            *(ioport volatile unsigned *)0x1901        //RTC Update Register
#define RTC_STAT            *(ioport volatile unsigned *)0x1920        //RTC Status Register
#define RTC_STAT_PWRUP      *(ioport volatile unsigned *)0x1921        //RTC Status Powerup Register
#define RTC_INT             *(ioport volatile unsigned *)0x1924        //RTC Interrupt Control Register
#define RTC_COMP            *(ioport volatile unsigned *)0x1928        //RTC Oscillator Drift Compensation Register
#define RTC_OSC             *(ioport volatile unsigned *)0x192c        //RTC Oscillator Register
#define RTC_LDORTCWAKE      *(ioport volatile unsigned *)0x1930        //RTC Power Management Control Register
#define RTC_PMGT            *(ioport volatile unsigned *)0x1930        //RTC Power Management Control Register
#define RTC_SCRATCH0_LSW    *(ioport volatile unsigned *)0x1960        //RTC Scratch 0 Register
#define RTC_SCRATCH0_MSW    *(ioport volatile unsigned *)0x1961        //RTC Scratch 0 Register
#define RTC_SCRATCH1_LSW    *(ioport volatile unsigned *)0x1964        //RTC Scratch 1 Register
#define RTC_SCRATCH1_MSW    *(ioport volatile unsigned *)0x1965        //RTC Scratch 0 Register


//----------------------------------------------------------------------------------------
//    RTC INT Register Bit Field Settings
//----------------------------------------------------------------------------------------
#define RTC_PER_INT_MSEC_EN     1b<<0           // RTC periodic interrupt millisecond enable
#define RTC_PER_INT_MSEC_DIS    0b<<0           // RTC periodic interrupt millisecond disable
#define RTC_PER_INT_SEC_EN      1b<<1           // RTC periodic interrupt seconds enable
#define RTC_PER_INT_SEC_DIS     0b<<1           // RTC periodic interrupt seconds disable
#define RTC_PER_INT_MIN_EN      1b<<2           // RTC periodic interrupt minutes enable
#define RTC_PER_INT_MIN_DIS     0b<<2           // RTC periodic interrupt minutes disable
#define RTC_PER_INT_HOUR_EN     1b<<3           // RTC periodic interrupt hours enable
#define RTC_PER_INT_HOUR_DIS    0b<<3           // RTC periodic interrupt hours disable
#define RTC_PER_INT_DAY_EN      1b<<4           // RTC periodic interrupt days enable
#define RTC_PER_INT_DAY_DIS     0b<<4           // RTC periodic interrupt days disable
#define RTC_EXT_INT_EN          1b<<5           // RTC external event interrupt enable
#define RTC_EXT_INT_DIS         0b<<5           // RTC external event interrupt disable
#define RTC_ALARM_INT_EN        1b<<15          // enable RTC alarm interrupt
#define RTC_ALARM_INT_DIS       0b<<15          // disable RTC alarm interrupt


//----------------------------------------------------------------------------------------
//    RTC LDORTCWAKE Register Bit Field Settings
//----------------------------------------------------------------------------------------
#define RTC_CLKOUT_DIS      0b              // RTC ClockOut is disabled
#define RTC_CLKOUT_EN       1b              // RTC ClockOut is enabled
#define PM_SHUTDOWN         1b<<1           // Shuts down Power Management
#define BG_SHUTDOWN         1b<<2           // Shuts down Bandgap
#define WAKEUP_DIR_OUT      1b<<3           // WAKEUP pin set as output
#define WAKEUP_DIR_IN       0b<<3           // WAKEUP pin set as output
#define WAKEUP_DATAOUT      1b<<4           // Wakeup Dataout is open drain


    
#endif
