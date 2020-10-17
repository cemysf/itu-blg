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

#ifndef _I2S_H_
#define _I2S_H_

Uint16  i2s0_read_CR( void);
void i2s0_write_CR( Uint16  data);
Uint16  i2s0_read_SRGR( void);
void i2s0_write_SRGR( Uint16  data);
Uint16  i2s0_read_TXL_LSW( void);
void i2s0_write_TXL_LSW( Uint16  data);
Uint16  i2s0_read_TXL_MSW( void);
void i2s0_write_TXL_MSW( Uint16  data);
Uint16  i2s0_read_TXR_LSW( void);
void i2s0_write_TXR_LSW( Uint16  data);
Uint16  i2s0_read_TXR_MSW( void);
void i2s0_write_TXR_MSW( Uint16  data);
Uint16  i2s0_read_INTR( void);
Uint16  i2s0_read_INT_MASK( void);
void i2s0_write_INT_MASK( Uint16  data);
Uint16  i2s0_read_RXL_LSW( void);
void i2s0_write_RXL_LSW( Uint16  data);
Uint16  i2s0_read_RXL_MSW( void);
void i2s0_write_RXL_MSW( Uint16  data);
Uint16  i2s0_read_RXR_LSW( void);
void i2s0_write_RXR_LSW( Uint16  data);
Uint16  i2s0_read_RXR_MSW( void);
void i2s0_write_RXR_MSW( Uint16  data);
Uint16  i2s1_read_CR( void);
void i2s1_write_CR( Uint16  data);
Uint16  i2s1_read_SRGR( void);
void i2s1_write_SRGR( Uint16  data);
Uint16  i2s1_read_TXL_LSW( void);
void i2s1_write_TXL_LSW( Uint16  data);
Uint16  i2s1_read_TXL_MSW( void);
void i2s1_write_TXL_MSW( Uint16  data);
Uint16  i2s1_read_TXR_LSW( void);
void i2s1_write_TXR_LSW( Uint16  data);
Uint16  i2s1_read_TXR_MSW( void);
void i2s1_write_TXR_MSW( Uint16  data);
Uint16  i2s1_read_INTR( void);
Uint16  i2s1_read_INT_MASK( void);
void i2s1_write_INT_MASK( Uint16  data);
Uint16  i2s1_read_RXL_LSW( void);
void i2s1_write_RXL_LSW( Uint16  data);
Uint16  i2s1_read_RXL_MSW( void);
void i2s1_write_RXL_MSW( Uint16  data);
Uint16  i2s1_read_RXR_LSW( void);
void i2s1_write_RXR_LSW( Uint16  data);
Uint16  i2s1_read_RXR_MSW( void);
void i2s1_write_RXR_MSW( Uint16  data);
Uint16  i2s2_read_CR( void);
void i2s2_write_CR( Uint16  data);
Uint16  i2s2_read_SRGR( void);
void i2s2_write_SRGR( Uint16  data);
Uint16  i2s2_read_TXL_LSW( void);
void i2s2_write_TXL_LSW( Uint16  data);
Uint16  i2s2_read_TXL_MSW( void);
void i2s2_write_TXL_MSW( Uint16  data);
Uint16  i2s2_read_TXR_LSW( void);
void i2s2_write_TXR_LSW( Uint16  data);
Uint16  i2s2_read_TXR_MSW( void);
void i2s2_write_TXR_MSW( Uint16  data);
Uint16  i2s2_read_INTR( void);
Uint16  i2s2_read_INT_MASK( void);
void i2s2_write_INT_MASK( Uint16  data);
Uint16  i2s2_read_RXL_LSW( void);
void i2s2_write_RXL_LSW( Uint16  data);
Uint16  i2s2_read_RXL_MSW( void);
void i2s2_write_RXL_MSW( Uint16  data);
Uint16  i2s2_read_RXR_LSW( void);
void i2s2_write_RXR_LSW( Uint16  data);
Uint16  i2s2_read_RXR_MSW( void);
void i2s2_write_RXR_MSW( Uint16  data);
Uint16  i2s3_read_CR( void);
void i2s3_write_CR( Uint16  data);
Uint16  i2s3_read_SRGR( void);
void i2s3_write_SRGR( Uint16  data);
Uint16  i2s3_read_TXL_LSW( void);
void i2s3_write_TXL_LSW( Uint16  data);
Uint16  i2s3_read_TXL_MSW( void);
void i2s3_write_TXL_MSW( Uint16  data);
Uint16  i2s3_read_TXR_LSW( void);
void i2s3_write_TXR_LSW( Uint16  data);
Uint16  i2s3_read_TXR_MSW( void);
void i2s3_write_TXR_MSW( Uint16  data);
Uint16  i2s3_read_INTR( void);
Uint16  i2s3_read_INT_MASK( void);
void i2s3_write_INT_MASK( Uint16  data);
Uint16  i2s3_read_RXL_LSW( void);
void i2s3_write_RXL_LSW( Uint16  data);
Uint16  i2s3_read_RXL_MSW( void);
void i2s3_write_RXL_MSW( Uint16  data);
Uint16  i2s3_read_RXR_LSW( void);
void i2s3_write_RXR_LSW( Uint16  data);
Uint16  i2s3_read_RXR_MSW( void);
void i2s3_write_RXR_MSW( Uint16  data);
void enable_i2s0(void);
void enable_i2s1(void);
void enable_i2s2(void);
void enable_i2s3(void);
void disable_i2s0(void);
void disable_i2s1(void);
void disable_i2s2(void);
void disable_i2s3(void);

///////////////////////////////////////////////////////////
Uint16 set_i2s2_master(void);
Uint16 set_i2s0_master(void);
Uint16 set_i2s0_slave(void);
#define USE_DMA 	1

#endif
