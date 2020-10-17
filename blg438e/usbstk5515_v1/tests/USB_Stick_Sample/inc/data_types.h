#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#ifdef WIN32
#define restrict
#define Int40               Int64

typedef short               Int16;
typedef long                Int32;
typedef long long           Int64;
typedef unsigned short      Uint16;
typedef unsigned long       Uint32;
typedef unsigned long long  Uint64;
typedef float               Float32;
typedef double              Float64;

#else

#ifdef C55X
typedef short               Int16;
typedef long                Int32;
typedef long long           Int40;
typedef unsigned short      Uint16;
typedef unsigned long       Uint32;
typedef unsigned long long  Uint40;
typedef float               Float32;

#else /* C6x */
typedef short               Int16;
typedef int                 Int32;
typedef long                Int40;
typedef long long           Int64;
typedef unsigned short      Uint16;
typedef unsigned int        Uint32;
typedef unsigned long       Uint40;
typedef unsigned long long  Uint64;
typedef float               Float32;
typedef double              Float64;

#endif /* C55X */

#endif /* WIN32 */

#define SUCCESS     0
#define ERROR_I2S0_CONFIG       1
#define ERROR_I2S1_CONFIG       2
#define ERROR_I2S2_CONFIG       3
#define ERROR_I2S3_CONFIG       4
#define ERROR_DMA0_CONFIG       5
#define ERROR_DMA1_CONFIG       6
#define ERROR_DMA2_CONFIG       7
#define ERROR_DMA3_CONFIG       8

#define ERROR_DATA_I2S                  10
#define ERROR_DATA_DATA_PROCESS         11
#define ERROR_DATA_MMC_SD               12
#define ERROR_DATA_UART                 13
#define ERROR_DATA_USB                  14
#define ERROR_DATA_SRAM                 15
#define ERROR_DATA_NOR                  16



#endif /* __DATA_TYPES_H__ */
