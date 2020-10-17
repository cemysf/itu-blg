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
#ifndef _REG_DMA_H_
#define _REG_DMA_H_

//****************************************************************************************
//         DMA 0
//**************************************************************************
//**************************************************************************
//        DMA0 Ch0 Register Addresses
//**************************************************************************
#define DMA0_CH0_SRC_LSW        *(ioport volatile unsigned *)0x0c00    // DMA0 Channel 0 Source LSW Address
#define DMA0_CH0_SRC_MSW        *(ioport volatile unsigned *)0x0c01    // DMA0 Channel 0 Source MSW Address
#define DMA0_CH0_DST_LSW        *(ioport volatile unsigned *)0x0c02    // DMA0 Channel 0 Destination LSW Address
#define DMA0_CH0_DST_MSW        *(ioport volatile unsigned *)0x0c03    // DMA0 Channel 0 Destination MSW Address
#define DMA0_CH0_TC_LSW         *(ioport volatile unsigned *)0x0c04    // DMA0 Channel 0 Length / Transfer Control LSW Register
#define DMA0_CH0_TC_MSW         *(ioport volatile unsigned *)0x0c05    // DMA0 Channel 0 Transfer Control MSW Register

//**************************************************************************
//        DMA0 Ch1 Register Addresses
//**************************************************************************
#define DMA0_CH1_SRC_LSW        *(ioport volatile unsigned *)0x0c20    // DMA0 Channel 1 Source LSW Address
#define DMA0_CH1_SRC_MSW        *(ioport volatile unsigned *)0x0c21    // DMA0 Channel 1 Source MSW Address
#define DMA0_CH1_DST_LSW        *(ioport volatile unsigned *)0x0c22    // DMA0 Channel 1 Destination LSW Address
#define DMA0_CH1_DST_MSW        *(ioport volatile unsigned *)0x0c23    // DMA0 Channel 1 Destination MSW Address
#define DMA0_CH1_TC_LSW         *(ioport volatile unsigned *)0x0c24    // DMA0 Channel 1 Length / Transfer Control LSW Register
#define DMA0_CH1_TC_MSW         *(ioport volatile unsigned *)0x0c25    // DMA0 Channel 1 Transfer Control MSW Register

//**************************************************************************
//        DMA0 Ch2 Register Addresses
//**************************************************************************
#define DMA0_CH2_SRC_LSW        *(ioport volatile unsigned *)0x0c40    // DMA0 Channel 2 Source LSW Address
#define DMA0_CH2_SRC_MSW        *(ioport volatile unsigned *)0x0c41    // DMA0 Channel 2 Source MSW Address
#define DMA0_CH2_DST_LSW        *(ioport volatile unsigned *)0x0c42    // DMA0 Channel 2 Destination LSW Address
#define DMA0_CH2_DST_MSW        *(ioport volatile unsigned *)0x0c43    // DMA0 Channel 2 Destination MSW Address
#define DMA0_CH2_TC_LSW         *(ioport volatile unsigned *)0x0c44    // DMA0 Channel 2 Length / Transfer Control LSW Register
#define DMA0_CH2_TC_MSW         *(ioport volatile unsigned *)0x0c45    // DMA0 Channel 2 Transfer Control MSW Register

//**************************************************************************
//        DMA0 Ch3 Register Addresses
//**************************************************************************
#define DMA0_CH3_SRC_LSW        *(ioport volatile unsigned *)0x0c60    // DMA0 Channel 3 Source LSW Address
#define DMA0_CH3_SRC_MSW        *(ioport volatile unsigned *)0x0c61    // DMA0 Channel 3 Source MSW Address
#define DMA0_CH3_DST_LSW        *(ioport volatile unsigned *)0x0c62    // DMA0 Channel 3 Destination LSW Address
#define DMA0_CH3_DST_MSW        *(ioport volatile unsigned *)0x0c63    // DMA0 Channel 3 Destination MSW Address
#define DMA0_CH3_TC_LSW         *(ioport volatile unsigned *)0x0c64    // DMA0 Channel 3 Length / Transfer Control LSW Register
#define DMA0_CH3_TC_MSW         *(ioport volatile unsigned *)0x0c65    // DMA0 Channel 3 Transfer Control MSW Register

//****************************************************************************************
//         DMA 1
//**************************************************************************
//        DMA1 Ch0 Register Addresses
//**************************************************************************
#define DMA1_CH0_SRC_LSW        *(ioport volatile unsigned *)0x0D00    // DMA1 Channel 0 Source LSW Address
#define DMA1_CH0_SRC_MSW        *(ioport volatile unsigned *)0x0D01    // DMA1 Channel 0 Source MSW Address
#define DMA1_CH0_DST_LSW        *(ioport volatile unsigned *)0x0D02    // DMA1 Channel 0 Destination LSW Address
#define DMA1_CH0_DST_MSW        *(ioport volatile unsigned *)0x0D03    // DMA1 Channel 0 Destination MSW Address
#define DMA1_CH0_TC_LSW         *(ioport volatile unsigned *)0x0D04    // DMA1 Channel 0 Length / Transfer Control LSW Register
#define DMA1_CH0_TC_MSW         *(ioport volatile unsigned *)0x0D05    // DMA1 Channel 0 Transfer Control MSW Register

//**************************************************************************
//        DMA1 Ch1 Register Addresses
//**************************************************************************
#define DMA1_CH1_SRC_LSW        *(ioport volatile unsigned *)0x0D20    // DMA1 Channel 1 Source LSW Address
#define DMA1_CH1_SRC_MSW        *(ioport volatile unsigned *)0x0D21    // DMA1 Channel 1 Source MSW Address
#define DMA1_CH1_DST_LSW        *(ioport volatile unsigned *)0x0D22    // DMA1 Channel 1 Destination LSW Address
#define DMA1_CH1_DST_MSW        *(ioport volatile unsigned *)0x0D23    // DMA1 Channel 1 Destination MSW Address
#define DMA1_CH1_TC_LSW         *(ioport volatile unsigned *)0x0D24    // DMA1 Channel 1 Length / Transfer Control LSW Register
#define DMA1_CH1_TC_MSW         *(ioport volatile unsigned *)0x0D25    // DMA1 Channel 1 Transfer Control MSW Register

//**************************************************************************
//        DMA1 Ch2 Register Addresses
//**************************************************************************
#define DMA1_CH2_SRC_LSW        *(ioport volatile unsigned *)0x0D40    // DMA1 Channel 2 Source LSW Address
#define DMA1_CH2_SRC_MSW        *(ioport volatile unsigned *)0x0D41    // DMA1 Channel 2 Source MSW Address
#define DMA1_CH2_DST_LSW        *(ioport volatile unsigned *)0x0D42    // DMA1 Channel 2 Destination LSW Address
#define DMA1_CH2_DST_MSW        *(ioport volatile unsigned *)0x0D43    // DMA1 Channel 2 Destination MSW Address
#define DMA1_CH2_TC_LSW         *(ioport volatile unsigned *)0x0D44    // DMA1 Destination Address
#define DMA1_CH2_TC_MSW         *(ioport volatile unsigned *)0x0D45    // DMA1 Channel 2 Transfer Control MSW Register

//**************************************************************************
//        DMA1 Ch3 Register Addresses
//**************************************************************************
#define DMA1_CH3_SRC_LSW        *(ioport volatile unsigned *)0x0D60    // DMA1 Channel 3 Source LSW Address
#define DMA1_CH3_SRC_MSW        *(ioport volatile unsigned *)0x0D61    // DMA1 Channel 3 Source MSW Address
#define DMA1_CH3_DST_LSW        *(ioport volatile unsigned *)0x0D62    // DMA1 Channel 3 Destination LSW Address
#define DMA1_CH3_DST_MSW        *(ioport volatile unsigned *)0x0D63    // DMA1 Channel 3 Destination MSW Address
#define DMA1_CH3_TC_LSW         *(ioport volatile unsigned *)0x0D64    // DMA1 Destination Address
#define DMA1_CH3_TC_MSW         *(ioport volatile unsigned *)0x0D65    // DMA1 Channel 0 Transfer Control MSW Register

//****************************************************************************************
//         DMA 2
//**************************************************************************
//        DMA2 Ch0 Register Addresses
//**************************************************************************
#define DMA2_CH0_SRC_LSW        *(ioport volatile unsigned *)0x0E00    // DMA2 Channel 0 Source LSW Address
#define DMA2_CH0_SRC_MSW        *(ioport volatile unsigned *)0x0E01    // DMA2 Channel 0 Source MSW Address
#define DMA2_CH0_DST_LSW        *(ioport volatile unsigned *)0x0E02    // DMA2 Channel 0 Destination LSW Address
#define DMA2_CH0_DST_MSW        *(ioport volatile unsigned *)0x0E03    // DMA2 Channel 0 Destination MSW Address
#define DMA2_CH0_TC_LSW         *(ioport volatile unsigned *)0x0E04    // DMA2 Channel 0 Length / Transfer Control LSW Register
#define DMA2_CH0_TC_MSW         *(ioport volatile unsigned *)0x0E05    // DMA2 Channel 0 Transfer Control MSW Register

//**************************************************************************
//        DMA2 Ch1 Register Addresses
//**************************************************************************
#define DMA2_CH1_SRC_LSW        *(ioport volatile unsigned *)0x0E20    // DMA2 Channel 1 Source LSW Address
#define DMA2_CH1_SRC_MSW        *(ioport volatile unsigned *)0x0E21    // DMA2 Channel 1 Source MSW Address
#define DMA2_CH1_DST_LSW        *(ioport volatile unsigned *)0x0E22    // DMA2 Channel 1 Destination LSW Address
#define DMA2_CH1_DST_MSW        *(ioport volatile unsigned *)0x0E23    // DMA2 Channel 1 Destination MSW Address
#define DMA2_CH1_TC_LSW         *(ioport volatile unsigned *)0x0E24    // DMA2 Channel 1 Length / Transfer Control LSW Register
#define DMA2_CH1_TC_MSW         *(ioport volatile unsigned *)0x0E25    // DMA2 Channel 1 Transfer Control MSW Register

//**************************************************************************
//        DMA2 Ch2 Register Addresses
//**************************************************************************
#define DMA2_CH2_SRC_LSW        *(ioport volatile unsigned *)0x0E40    // DMA2 Channel 2 Source LSW Address
#define DMA2_CH2_SRC_MSW        *(ioport volatile unsigned *)0x0E41    // DMA2 Channel 2 Source MSW Address
#define DMA2_CH2_DST_LSW        *(ioport volatile unsigned *)0x0E42    // DMA2 Channel 2 Destination LSW Address
#define DMA2_CH2_DST_MSW        *(ioport volatile unsigned *)0x0E43    // DMA2 Channel 2 Destination MSW Address
#define DMA2_CH2_TC_LSW         *(ioport volatile unsigned *)0x0E44    // DMA2 Destination Address
#define DMA2_CH2_TC_MSW         *(ioport volatile unsigned *)0x0E45    // DMA2 Channel 2 Transfer Control MSW Register

//**************************************************************************
//        DMA2 Ch3 Register Addresses
//**************************************************************************
#define DMA2_CH3_SRC_LSW        *(ioport volatile unsigned *)0x0E60    // DMA2 Channel 3 Source LSW Address
#define DMA2_CH3_SRC_MSW        *(ioport volatile unsigned *)0x0E61    // DMA2 Channel 3 Source MSW Address
#define DMA2_CH3_DST_LSW        *(ioport volatile unsigned *)0x0E62    // DMA2 Channel 3 Destination LSW Address
#define DMA2_CH3_DST_MSW        *(ioport volatile unsigned *)0x0E63    // DMA2 Channel 3 Destination MSW Address
#define DMA2_CH3_TC_LSW         *(ioport volatile unsigned *)0x0E64    // DMA2 Destination Address
#define DMA2_CH3_TC_MSW         *(ioport volatile unsigned *)0x0E65    // DMA2 Channel 0 Transfer Control MSW Register

//****************************************************************************************
//         DMA 3
//**************************************************************************
//        DMA3 Ch0 Register Addresses
//**************************************************************************
#define DMA3_CH0_SRC_LSW        *(ioport volatile unsigned *)0x0F00    // DMA3 Channel 0 Source LSW Address
#define DMA3_CH0_SRC_MSW        *(ioport volatile unsigned *)0x0F01    // DMA3 Channel 0 Source MSW Address
#define DMA3_CH0_DST_LSW        *(ioport volatile unsigned *)0x0F02    // DMA3 Channel 0 Destination LSW Address
#define DMA3_CH0_DST_MSW        *(ioport volatile unsigned *)0x0F03    // DMA3 Channel 0 Destination MSW Address
#define DMA3_CH0_TC_LSW         *(ioport volatile unsigned *)0x0F04    // DMA3 Channel 0 Length / Transfer Control LSW Register
#define DMA3_CH0_TC_MSW         *(ioport volatile unsigned *)0x0F05    // DMA3 Channel 0 Transfer Control MSW Register

//**************************************************************************
//        DMA3 Ch1 Register Addresses
//**************************************************************************
#define DMA3_CH1_SRC_LSW        *(ioport volatile unsigned *)0x0F20    // DMA3 Channel 1 Source LSW Address
#define DMA3_CH1_SRC_MSW        *(ioport volatile unsigned *)0x0F21    // DMA3 Channel 1 Source MSW Address
#define DMA3_CH1_DST_LSW        *(ioport volatile unsigned *)0x0F22    // DMA3 Channel 1 Destination LSW Address
#define DMA3_CH1_DST_MSW        *(ioport volatile unsigned *)0x0F23    // DMA3 Channel 1 Destination MSW Address
#define DMA3_CH1_TC_LSW         *(ioport volatile unsigned *)0x0F24    // DMA3 Channel 1 Length / Transfer Control LSW Register
#define DMA3_CH1_TC_MSW         *(ioport volatile unsigned *)0x0F25    // DMA3 Channel 1 Transfer Control MSW Register

//**************************************************************************
//        DMA3 Ch2 Register Addresses
//**************************************************************************
#define DMA3_CH2_SRC_LSW        *(ioport volatile unsigned *)0x0F40    // DMA3 Channel 2 Source LSW Address
#define DMA3_CH2_SRC_MSW        *(ioport volatile unsigned *)0x0F41    // DMA3 Channel 2 Source MSW Address
#define DMA3_CH2_DST_LSW        *(ioport volatile unsigned *)0x0F42    // DMA3 Channel 2 Destination LSW Address
#define DMA3_CH2_DST_MSW        *(ioport volatile unsigned *)0x0F43    // DMA3 Channel 2 Destination MSW Address
#define DMA3_CH2_TC_LSW         *(ioport volatile unsigned *)0x0F44    // DMA3 Destination Address
#define DMA3_CH2_TC_MSW         *(ioport volatile unsigned *)0x0F45    // DMA3 Channel 2 Transfer Control MSW Register

//**************************************************************************
//        DMA3 Ch3 Register Addresses
//**************************************************************************
#define DMA3_CH3_SRC_LSW        *(ioport volatile unsigned *)0x0F60    // DMA3 Channel 3 Source LSW Address
#define DMA3_CH3_SRC_MSW        *(ioport volatile unsigned *)0x0F61    // DMA3 Channel 3 Source MSW Address
#define DMA3_CH3_DST_LSW        *(ioport volatile unsigned *)0x0F62    // DMA3 Channel 3 Destination LSW Address
#define DMA3_CH3_DST_MSW        *(ioport volatile unsigned *)0x0F63    // DMA3 Channel 3 Destination MSW Address
#define DMA3_CH3_TC_LSW         *(ioport volatile unsigned *)0x0F64    // DMA3 Destination Address
#define DMA3_CH3_TC_MSW         *(ioport volatile unsigned *)0x0F65    // DMA3 Channel 0 Transfer Control MSW Register

//****************************************************************************************
//   DMA Event Source Registers
//****************************************************************************************
#define DMA0_CH10_EVENT_SRC     *(ioport volatile unsigned *)0x1C1A
#define DMA0_CH32_EVENT_SRC     *(ioport volatile unsigned *)0x1C1B
#define DMA1_CH10_EVENT_SRC     *(ioport volatile unsigned *)0x1C1C     // DMA1 channel 0 and channel 1 Event Source Register
#define DMA1_CH32_EVENT_SRC     *(ioport volatile unsigned *)0x1C1D     // DMA1 channel 3 and channel 2 Event Source Register
#define DMA2_CH10_EVENT_SRC     *(ioport volatile unsigned *)0x1C36     // DMA2 channel 0 and channel 1 Event Source Register
#define DMA2_CH32_EVENT_SRC     *(ioport volatile unsigned *)0x1C37     // DMA2 channel 3 and channel 2 Event Source Register
#define DMA3_CH10_EVENT_SRC     *(ioport volatile unsigned *)0x1C38     // DMA3 channel 0 and channel 1 Event Source Register
#define DMA3_CH32_EVENT_SRC     *(ioport volatile unsigned *)0x1C39    // DMA3 channel 3 and channel 2 Event Source Register

//****************************************************************************************
//   DMA Interrupt
//****************************************************************************************
#define DMA_IFR     *(ioport volatile unsigned *)0x1C30    // DMA Interrupt Flag Register
#define DMA_MSK     *(ioport volatile unsigned *)0x1C31    // DMA Interrupt Mask Flag Register

// DMA_IFR             Address:  0x1C30 (IO space)       DMA Interrupt Flag Register
// +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
// |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
// +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
// |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
// +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
// | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
// +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   (Writing a '1' clears the bit; writing a '0' has no effect)
//   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMA0_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMA0_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMA0_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMA0_CH3_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |  |  |  |  |
//   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMA1_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMA1_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMA1_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |  +----------------------- [7]  DMA1_CH3_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  |  |
//   |  |  |  |  |  |  |  +-------------------------- [8]  DMA2_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  |  +----------------------------- [9]  DMA2_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  |  +-------------------------------- [10] DMA2_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |  +----------------------------------- [11] DMA2_CH3_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  |  |
//   |  |  |  +-------------------------------------- [12] DMA3_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  |  +----------------------------------------- [13] DMA3_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
//   |  +-------------------------------------------- [14] DMA3_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
//   +----------------------------------------------- [15] DMA3_CH3_INTF (0=no interrupt occured, 1=interrupt occured)


    
#endif
