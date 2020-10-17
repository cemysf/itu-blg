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
#ifndef _REG_SYS_H_
#define _REG_SYS_H_

//****************************************************************************************
//         SYSREG Registers:               (IO Space:  0x1C00 - 0x1CFF)
//**************************************************************************
#define PERIPHSEL0        *(ioport volatile unsigned *)0x1C00    // PERIPHSEL0 (Peripheral Pin Mapping Register 0)
#define IDLE_PCGCR        *(ioport volatile unsigned *)0x1C02    // Peripheral Clock Gating Control Register LSW
    // IDLE_PCGCR   Address:  0x1C02 (IO Space)           Peripheral Clock Gating Control Register LSW
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  IIS3_IDLE         (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SPI_IDLE          (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  UART_IDLE         (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMA0_IDLE         (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  MMCSD0_IDLE       (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  COPROC_IDLE       (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  I2C_IDLE          (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  MMCSD1_IDLE       (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  IIS0_IDLE         (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  |  +----------------------------- [9]  IIS1_IDLE         (0:clk active, 1:clk disabled)
    //   |  |  |  |  |  +-------------------------------- [10] TIMER0_IDLE       (0:clk active, 1:clk disabled)
    //   |  |  |  |  +----------------------------------- [11] EMIF_IDLE         (0:clk active, 1:clk disabled)
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] TIMER1_IDLE       (0:clk active, 1:clk disabled)
    //   |  |  +----------------------------------------- [13] TIMER2_IDLE       (0:clk active, 1:clk disabled)
    //   |  +-------------------------------------------- [14] IIS2_IDLE         (0:clk active, 1:clk disabled)
    //   +----------------------------------------------- [15] MASTER_CLK_DIS    (0:Master clock active, 1:all clks disabled)

//----------------------------------------------------------------------------------------
//        IDLE_PCGCR         Bit Fields
//----------------------------------------------------------------------------------------
#define IIS3_IDLE               1b<<0       // IIS3 Idle Control Bit
#define SPI_IDLE                1b<<1       // SPI Idle Control Bit
#define UART_IDLE               1b<<2       // UART Control Bit
#define DMA0_IDLE               1b<<3       // DMA0 Idle Control Bit
#define MMCSD0_IDLE             1b<<4       // MMCSD0 Idle Control Bit
#define COPROC_IDLE             1b<<5       // CoProcessor Idle Control Bit
#define I2C_IDLE                1b<<6       // I2C Idle Control Bit
#define MMCSD1_IDLE             1b<<7       // MMCSD0 Idle Control Bit
#define IIS0_IDLE               1b<<8       // I2S0 Idle Control Bit
#define IIS1_IDLE               1b<<9       // I2S1 Idle Control Bit
#define TIMER0_IDLE             1b<<10      // Timer 0 Idle Control Bit
#define EMIF_IDLE               1b<<11      // EMIF Idle Control Bit
#define TIMER1_IDLE             1b<<12      // Timer 1 Module Clock off
#define TIMER2_IDLE             1b<<13      // Timer 2 Module Clock off
#define IIS2_IDLE               1b<<14      // IIS2 Idle Control Bit
#define OSC_DISABLE             1b<<15      // Oscillator disable      (cory: use of this name should be discontinued... use 'MASTER_CLK_DIS')
#define MASTER_CLK_DIS          1b<<15      // Disables clock to ALL domains (can only wake via: RTC alarms, WAKEUP, INT0, INT1, & RESET)
#define RESERVED_PCGCR          0000000000000000b       // Reserved bits (MSB --> LSB)

#define IDLE_PCGCR_MSW        *(ioport volatile unsigned *)0x1C03    // Peripheral Clock Gating Control Register MSW
    // IDLE_PCGCR_MSW   Address:  0x1C03 (IO Space)           Peripheral Clock Gating Control Register MSW
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |r :r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  LCD_CG        (0:active, 1:disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SAR_CG        (0:active, 1:disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  USB_CG        (0:active, 1:disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMA1_CG       (0:active, 1:disabled)
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMA2_CG       (0:active, 1:disabled)
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMA3_CG       (0:active, 1:disabled)
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  ANAREG_CG     (0:active, 1:disabled) (note: SAR_CG==0 then this reg is ignored and the ANAREG clocks are forced ON).
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    //   |  |  |  |  |  |  +----------------------------- [9]  reserved
    //   |  |  |  |  |  +-------------------------------- [10] reserved
    //   |  |  |  |  +----------------------------------- [11] reserved
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] reserved
    //   |  |  +----------------------------------------- [13] reserved
    //   |  +-------------------------------------------- [14] reserved
    //   +----------------------------------------------- [15] reserved

//----------------------------------------------------------------------------------------
//        IDLE_PCGCR_MSW         Bit Fields
//----------------------------------------------------------------------------------------
#define LCD_IDLE               1b<<0       // LCD Idle Control Bit
#define SARADC_IDLE            1b<<1       // SAR A/D Idle Control Bit
#define USB_IDLE               1b<<2       // USB Idle Control Bit
#define DMA1_IDLE              1b<<3       // DMA1 Idle Control Bit
#define DMA2_IDLE              1b<<4       // DMA2 Idle Control Bit
#define DMA3_IDLE              1b<<5       // DMA3 Idle Control Bit
#define ANAREG_IDLE            1b<<6       // ANAREG Idle Control Bit
#define RESERVED_PCGCR_MSW     1111111110000000b       // Reserved bits

#define PER_RSTCOUNT        *(ioport volatile unsigned *)0x1C04    // Peripheral Software Reset Counter Register
#define PER_RESET        *(ioport volatile unsigned *)0x1C05    // Peripheral Reset Register
    // PER_RESET   Address:  0x1C05 (IO space)             Peripheral Reset Register
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+       Note:  Order matters.  Write to PeripheralsResetCount[15:0] first, then this register.
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |               ******* WRITES TO THIS REGISTER ********
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ResetEn_I2C                         (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  ResetEn_EMIF_Timers_RTC             (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ResetEn_Analog_SAR  (& TRIM!!!)     (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1)) (Customers should never reset this domain because of its effect on trim!!)
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  ResetEn_USB                         (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  ResetEn_DMA                         (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  ResetEn_MMCSD0_MMCSD1_IIS0_IIS1     (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  ResetEn_FFTCOP                      (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  ResetEn_LCD_IIS2_IIS3_UART_SPI      (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  HoldInReset_I2C                     (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   |  |  |  |  |  |  +----------------------------- [9]  HoldInReset_EMIF_TIMERS_RTC         (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   |  |  |  |  |  +-------------------------------- [10] HoldInReset_Analog_SAR  (& TRIM!!!) (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   |  |  |  |  +----------------------------------- [11] HoldInReset_USB                     (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] HoldInReset_DMA                     (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   |  |  +----------------------------------------- [13] HoldInReset_MMCSD0_MMCSD1_IIS0_IIS1 (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   |  +-------------------------------------------- [14] HoldInReset_FFTCOP                  (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   +----------------------------------------------- [15] HoldInReset_LCD_IIS2_IIS3_UART_SPI  (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |               ******* READS FROM THIS REGISTER ********
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ResetState_I2C                      (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  ResetState_EMIF_Timers_RTC          (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ResetState_Analog_SAR               (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  ResetState_USB                      (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  ResetState_DMA                      (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  ResetState_MMCSD0_MMCSD1_IIS0_IIS1  (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  ResetState_FFTCOP                   (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  ResetState_LCD_IIS2_IIS3_UART_SPI   (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  HoldInReset_I2C                     (read returns the value last written)
    //   |  |  |  |  |  |  +----------------------------- [9]  HoldInReset_EMIF_Timers_RTC         (read returns the value last written)
    //   |  |  |  |  |  +-------------------------------- [10] HoldInReset_Analog_SAR              (read returns the value last written)
    //   |  |  |  |  +----------------------------------- [11] HoldInReset_USB                     
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] HoldInReset_DMA                     (read returns the value last written)
    //   |  |  +----------------------------------------- [13] HoldInReset_MMCSD0_MMCSD1_IIS0_IIS1 (read returns the value last written)
    //   |  +-------------------------------------------- [14] HoldInReset_FFTCOP                  (read returns the value last written)
    //   +----------------------------------------------- [15] HoldInReset_LCD_IIS2_IIS3_UART_SPI  (read returns the value last written)

//----------------------------------------------------------------------------------------
//        PER_RESET      Bit Fields
//----------------------------------------------------------------------------------------
#define I2C_RST                          1b<<0       // I2C Reset Bit
#define EMIF_TIMERS_RTC_RST              1b<<1       // EMIF_TIMERS_RTC Reset Bit
#define SAR_RST                          1b<<2       // SAR Reset Bit
#define USB_RST                          1b<<3       // USB Reset Bit
#define DMA_RST                          1b<<4       // DMA Reset Bit
#define MMCSD0_MMCSD1_IIS0_IIS1_RST      1b<<5       // MMCSD0_MMCSD1_IIS0_IIS1 Reset Bit
#define FFTCOP_RST                       1b<<6       // FFT CoProcessor Reset Bit
#define LCD_IIS2_IIS3_UART_SPI_RST       1b<<7       // LCD_IIS2_IIS3_UART_SPI Reset Bit

#define CONFIG_MSW        *(ioport volatile unsigned *)0x1C1F    // Clock Configuration MSW Register
    // CONFIG_MSW   Address:  0x1C1F (IO space)           Clock Configuration MSW Register
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |r :r :r :r |r :r :r :r |r :r :r :r |rw:r :r :rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0:??: 0| 0:??: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SysClkSel        (0:PLL Bypassed (sysclk=osc), 1:PLL used (sysclk=pllout))
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  CLK_SEL_PIN      (read only - reads the state of the CLK_SEL pin; writes have no affect)
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Timer0ClkSel     (0:normal mode/same as all other peripherals (sysclk), 1:PLL used (Timer0clk <= pllout) (testmode for pll))
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  SysClkSelStatus[0]  (Read Only Status of Glitch-Free-Clock Mux's selected clk source:
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  SysClkSelStatus[1]   00:RTCXI, 01:PLL out, 10:CLKIN pin, 11:PLL out)   (note: bit1 is identical to CLK_SEL_PIN, bit0 is the pll used vs bypassed status)
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    //   |  |  |  |  |  |  +----------------------------- [9]  reserved
    //   |  |  |  |  |  +-------------------------------- [10] reserved
    //   |  |  |  |  +----------------------------------- [11] reserved
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] reserved
    //   |  |  +----------------------------------------- [13] reserved
    //   |  +-------------------------------------------- [14] reserved
    //   +----------------------------------------------- [15] reserved
#define PLL_CNTL1        *(ioport volatile unsigned *)0x1C20    // PLL Control Register #1
    // PLL_CNTL1   Address:  0x1C20 (IO space)       PLL Control Register #1
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |rw:r :rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 1| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  VP[0]           [VCO Feedback Divider, coarse adjust.
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  VP[1]              Total feedback divide by value is = {VP[9:0], VS[1:0]} + 4 ]
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  VP[2]
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  VP[3]
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  VP[4]
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  VP[5]
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  VP[6]
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  VP[7]
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  VP[8]
    //   |  |  |  |  |  |  +----------------------------- [9]  VP[9]
    //   |  |  |  |  |  +-------------------------------- [10] reserved
    //   |  |  |  |  +----------------------------------- [11] reserved
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] PWDN            [0:PLL is powered, 1:PLL powered down (everything in the pll powered down)]
    //   |  |  +----------------------------------------- [13] STANDBY         [0:PLL is active, 1:PLL is in standby (ibias remains powered for faster powerup).]
    //   |  +-------------------------------------------- [14] reserved
    //   +----------------------------------------------- [15] CLRZ            [0:clears LONG_LK_CNT counter & holds the charge on the LPF capacitor.  Normally, take CLRZ low while changing PLL programming to make smoother frequency transitions, thus its not required to bypass the pll while changing ratios.]
//****************************************************************************************
//    PLL Control 1 Control Register Bit Fields
//****************************************************************************************
#define PLL_PWRDN        1b << 12     // PLL powered down
#define PLL_POWERED      0b << 12     // PLL is powered
#define PLL_STANDBY      1b << 13     // PLL is in standby
#define PLL_ACTIVE       0b << 13     // PLL is active
#define CLRZ_LOW         0b << 15     // Clear CLRZ
#define CLRZ_HIGH        1b << 15     // Clear CLRZ
//****************************************************************************************

#define PLL_CNTL2        *(ioport volatile unsigned *)0x1C21    //  PLL Control Register #2
    // PLL_CNTL2   Address:  0x1C21 (IO space)       PLL Control Register #2
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |rw:r :rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  RP[0]           [Reference divider.  If RP_BYPASS==0, the divide by value is = RP[11:0] + 4 else it is = 1.]
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  RP[1]
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  RP[2]
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  RP[3]
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  RP[4]
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  RP[5]
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  RP[6]
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  RP[7]
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  RP[8]
    //   |  |  |  |  |  |  +----------------------------- [9]  RP[9]
    //   |  |  |  |  |  +-------------------------------- [10] RP[10]
    //   |  |  |  |  +----------------------------------- [11] RP[11]
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] VS[0]           [VCO Feedback Swallow divider, fine frequency adjust.  See 'VP' for equation.]
    //   |  |  +----------------------------------------- [13] VS[1]
    //   |  +-------------------------------------------- [14] reserved
    //   +----------------------------------------------- [15] RP_BYPASS       [0:use the reference divider, 1:bypass the reference divider (divide by 1)]
//****************************************************************************************
//    PLL Control 2 Control Register Bit Fields
//****************************************************************************************
#define VS_0              00b << 12       // VS[1:0]
#define VS_1              01b << 12
#define VS_2              10b << 12
#define VS_3              11b << 12
#define RP_BYPASS         1b  << 15       // bypass the reference divider
#define RP_ACTIVE         0b  << 15       // use the reference divider
//****************************************************************************************
#define PLL_CNTL3        *(ioport volatile unsigned *)0x1C22    //  PLL Control Register #3
    // PLL_CNTL3   Address:  0x1C22 (IO space)      PLL Control Register #3
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |rw:rw:rw:rw|rw:r :rw:rw|r :r :rw:rw|r :rw:rw:rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 0| 1: 0: 0: 0| 0: 0: 1: 1| 0: 0: 1: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  NARWZ           [Narrowband Mode Select - Selects the cutoff freq of the LPF Op-Amp Low-Pass-Filter.  In wideband, the 
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                            cutoff is higher and the LPF settling time is faster which allows for faster lock but more frequency
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                            error.  Narrowband mode has a lower freq cutoff for better freq error at the expense of slower lock 
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                            time.  NARWZ works in conjunction with EN_FASTSTART, CLRZ, & LONG_LK_CNT as shown below:
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   EN_FASTSTART    NARWZ   RESULT
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   ============    =====   ==============================================
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   0               0       Narrowband Mode (slower lock but better freq error)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   0               1       Wideband Mode (faster lock at the expense of freq error)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                   recommended --> 1               0       Auto Mode (From CLRZ going high (or POR), will be in Wideband Mode for LONG_LK_CNT (feedback) clock cycles and then automatically switch to Narrowband Mode)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   1               1       Wideband Mode (faster lock at the expense of freq error)                       ]
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  EN_FASTSTART    [Enables dynamically switching bandwidth for faster startup - 0:disabled, 1:enabled (recommended).]
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  LONG_LK_CNT     [0:16 clock counts (recommended), 1:64 clock counts till lock monitor value goes high after a powerdown or CLRZ reset.  Clocked by the output of the feedback divider.]
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  TESTLOCKMON     ['Stable' status monitor.  Output of LONG_LK_CNT counter.  0:not locked, 1:locked.  Note:  this really isn't a true LOCK or stability indicator.  It just helps as a rough indicator of when the PLL should be stable.]
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  LOW_CURR        [0:normal ibias currents used, 1:Reduces ibias current in half (recommended, but needs to be proven in si).  Note, in schematic its called 'SEL_VCOOUT_TEST'.  ]
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  EN_LP           [Lower Power Mode (lowers the drive strength of the LPF op-amp) but -may- cause instability. - 0:mode disabled, 1:mode enabled (recommended).  Testchips have shown this to always be useful, however we need to re-evaluate for Corazon's VCO freq range adjustments that have been made to this ckt.)]
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |                                                Charge Sharing Blocking Switches are used to prevent charge leakage out of the LPF capacitor thru the op-amp's bias input resistor.
    //   |  |  |  |  |  |  |  |                                                At 32 Khz, the clock period is much longer than is necessary to allow for settling, so charge blocking switches OPEN automatically,
    //   |  |  |  |  |  |  |  |                                                modulated by the phase detector error, to prevent the charge loss.  This results in much lower sideband frequency error and much
    //   |  |  |  |  |  |  |  |                                                lower power.  Stan has a patent pending for this invention.  PD_SW_TOG_DEL & PD_SW_CLOSE are test mode signals to allow for debug
    //   |  |  |  |  |  |  |  |                                                if necessary.
    //   |  |  |  |  |  |  |  +-------------------------- [8]  PD_SW_TOG_DEL   [Charge Sharing Blocking Switches Test Control. 1:At power up switches are closed and at lock they toggle with phase detector error. 0:(recommended) allows PD switches to always toggle.]
    //   |  |  |  |  |  |  +----------------------------- [9]  PD_SW_CLOSE     [Charge Sharing Blocking Switches Test Control. 1:Always closes phase detector switches, no toggling. 0:(recommended) allows switches to be toggled by phase detector error.]
    //   |  |  |  |  |  +-------------------------------- [10] reserved
    //   |  |  |  |  +----------------------------------- [11] EN_LOW_JIT      [Disables test paths that may cause jitter injection. - 0:mode disabled, 1:mode enabled (recommended) ]
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] EN_TP_SIGNALS   [To Be Removed.  0:(recommended) internal test points disabled, 1:internal test points enabled]
    //   |  |  +----------------------------------------- [13] ENABLE_VCODIV   [0: normal mode (recommended), 1:Enables the VCO input voltage to be directly controlled for test.  Must also select this path via the 'anareg_anatestmodesel_tr' register that enables the GPAIN3 pin to connect to the VCO input.  Note, signal name is misleading but this description is correct.]
    //   |  +-------------------------------------------- [14] CK_DISABLE      [0:clock on (recommended), 1:Turns off VCO output clocks to core applications.  Note: PCGCR bit 15 should normally be used for master clock gating rather than this bit.]
    //   +----------------------------------------------- [15] BYPASSPLL       [0:PLL is enabled (recommended), 1:PLL bypassed & VCO powered down.  Note: Not glitchfree switched.  Normally, the PLL should be bypassed with CONFIG_MSW bit 0 rather than this bit.]
//****************************************************************************************
//    PLL Control 3 Control Register Bit Fields
//****************************************************************************************
#define NARROWBAND         0b  << 0        // Narrowband mode
#define WIDEBAND           1b  << 0        // Wideband mode
#define FASTSTART_EN       1b  << 1        // Fast Start enabled
#define FASTSTART_DIS      0b  << 1        // Fast Start disabled
#define CLK_CNT_16         0b  << 2        // 16 clock count
#define CLK_CNT_64         1b  << 2        // 64 clock counts till lock monitor value goes high after a powerdown or CLRZ reset
#define LOW_CURRENT        1b  << 4        // Reduces ibias current in half
#define HIGH_CURRENT       0b  << 4        // normal ibias currents
#define LOW_POWER_EN       1b  << 5        // low power mode enabled
#define LOW_POWER_DIS      0b  << 5        // low power mode disabled
#define PD_SW_TOGGLE       0b  << 8        // allows PD switches to always toggle
#define PD_SW_PWUP_CL      1b  << 8        // Closes PD switches until lock, when they are opened and toggle
#define PD_SW_OPEN         0b  << 9        // allows switches to be toggled by phase detector error
#define LOW_JITTER_EN      1b  << 11       // low jitter enabled
#define VCO_CK_ENABLED     0b  << 14       // VCO output clock on
#define VCO_CK_DISABLED .set    0b  << 14       // Turns off VCO output clocks to core applications
#define PLL_ENABLED        0b  << 15       // PLL is enabled
#define PLL_BYPASS         1b  << 15       // PLL bypassed & VCO powered down
//****************************************************************************************

#define PLL_CNTL4        *(ioport volatile unsigned *)0x1C23    //  PLL Control Register #4
    // PLL_CNTL4   Address:  0x1C23 (IO space)      PLL Control Register #4
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  OP[0]         PLL Output Divider
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  OP[1]
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  OP[2]
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  OP[3]
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  OP[4]
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  OP[5]
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  OUTDIV2       THIS_IS_A_GUESS: (0:programmable divider enabled, 1:programmable divider bypassed & div-by-2 enabled)
    //   |  |  |  |  |  |  +----------------------------- [9]  OUTDIVIDE     THIS_IS_A_GUESS: (0:programmable divider bypassed & div-by-2 bypassed, 1:programmable divider enabled & div-by-2 enabled)
    //   |  |  |  |  |  +-------------------------------- [10] reserved
    //   |  |  |  |  +----------------------------------- [11] reserved
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] reserved
    //   |  |  +----------------------------------------- [13] reserved
    //   |  +-------------------------------------------- [14] reserved
    //   +----------------------------------------------- [15] reserved
//****************************************************************************************
//    PLL Control 4 Control Register Bit Fields
//****************************************************************************************
#define OUTDIV2_EN        0b  << 8        // programmable output divider enabled
#define OUTDIV2_DIS       1b  << 8        // programmable output divider bypassed
#define OUTDIV_EN         1b  << 9        // programmable output divider & div-2 enabled
#define OUTDIV_DIS        0b  << 9        // programmable output divider & div-2 bypassed
//****************************************************************************************


//****************************************************************************************
//        Clock Domain Registers
//****************************************************************************************
#define IDLE_ICR        *(ioport volatile unsigned *)0x0001    //  IDLE Control Register
    // IDLE_ICR   Address:  0x0001 (IO Space)             IDLE Control Register
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    // | 1: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  CPU_IDLE          (0:active, 1:idled)
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved, writes should set to 1
    //   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved, writes should set to 1
    //   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved, writes should set to 1
    //   |  |  |  |  |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  CLK_IDLE  *** reserved, writes should set to 0 ***
    //   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DPORT_IDLE        (0:active, 1:idled)
    //   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XPORT_IDLE        (0:active, 1:idled - CPUI must be idled too)
    //   |  |  |  |  |  |  |  |  +----------------------- [7]  MPORT_IDLE        (0:active, 1:idled - DMA must be idled too)
    //   |  |  |  |  |  |  |  |
    //   |  |  |  |  |  |  |  +-------------------------- [8]  IPORT_IDLE        (0:active, 1:idled)
    //   |  |  |  |  |  |  +----------------------------- [9]  HWA_IDLE          (0:active, 1:idled)
    //   |  |  |  |  |  +-------------------------------- [10] reserved
    //   |  |  |  |  +----------------------------------- [11] reserved
    //   |  |  |  |
    //   |  |  |  +-------------------------------------- [12] reserved
    //   |  |  +----------------------------------------- [13] reserved
    //   |  +-------------------------------------------- [14] reserved
    //   +----------------------------------------------- [15] reserved
//----------------------------------------------------------------------------------------
//        ICR Bit Fields
//----------------------------------------------------------------------------------------
#define CPU_IDLE           1b          // CPU Idle Control Bit
#define CLK_IDLE           1b<<4       // Clock Generator Idle Control Bit
#define DPORT_IDLE         1b<<5       // DPORT Idle Control Bit
#define XPORT_IDLE         1b<<6       // XPORT Idle Control Bit
#define MPORT_IDLE         1b<<7       // MPORT Idle Control Bit
#define IPORT_IDLE         1b<<8       // IPORT Idle Control Bit
#define HWA_IDLE           1b<<9       // HWA Idle Control Bit
#define RESERVED_ICR       1111110000001110b       // Reserved bits (UMA peripheral, DMA, cache)

#endif
