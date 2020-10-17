*****************************************************************************
*  Copyright (c) 2008 -2010 Texas Instruments, Inc. All Rights Reserved          *
*  This is proprietary information, not to be published -- TI INTERNAL DATA *
*****************************************************************************

         .mmregs
         .include "lpva200.inc"
         
         .C54CM_off
         .CPL_off
         .ARMS_off

         .text   

        .global _i2s0_read_CR
        .global _i2s0_write_CR
        .global _i2s0_read_SRGR
        .global _i2s0_write_SRGR
        .global _i2s0_read_TXL_LSW
        .global _i2s0_write_TXL_LSW
        .global _i2s0_read_TXL_MSW
        .global _i2s0_write_TXL_MSW
        .global _i2s0_read_TXR_LSW
        .global _i2s0_write_TXR_LSW
        .global _i2s0_read_TXR_MSW
        .global _i2s0_write_TXR_MSW
        .global _i2s0_read_INTR
        .global _i2s0_read_INT_MASK
        .global _i2s0_write_INT_MASK
        .global _i2s0_read_RXL_LSW
        .global _i2s0_write_RXL_LSW
        .global _i2s0_read_RXL_MSW
        .global _i2s0_write_RXL_MSW
        .global _i2s0_read_RXR_LSW
        .global _i2s0_write_RXR_LSW
        .global _i2s0_read_RXR_MSW
        .global _i2s0_write_RXR_MSW
        .global _i2s1_read_CR
        .global _i2s1_write_CR
        .global _i2s1_read_SRGR
        .global _i2s1_write_SRGR
        .global _i2s1_read_TXL_LSW
        .global _i2s1_write_TXL_LSW
        .global _i2s1_read_TXL_MSW
        .global _i2s1_write_TXL_MSW
        .global _i2s1_read_TXR_LSW
        .global _i2s1_write_TXR_LSW
        .global _i2s1_read_TXR_MSW
        .global _i2s1_write_TXR_MSW
        .global _i2s1_read_INTR
        .global _i2s1_read_INT_MASK
        .global _i2s1_write_INT_MASK
        .global _i2s1_read_RXL_LSW
        .global _i2s1_write_RXL_LSW
        .global _i2s1_read_RXL_MSW
        .global _i2s1_write_RXL_MSW
        .global _i2s1_read_RXR_LSW
        .global _i2s1_write_RXR_LSW
        .global _i2s1_read_RXR_MSW
        .global _i2s1_write_RXR_MSW
        .global _i2s2_read_CR
        .global _i2s2_write_CR
        .global _i2s2_read_SRGR
        .global _i2s2_write_SRGR
        .global _i2s2_read_TXL_LSW
        .global _i2s2_write_TXL_LSW
        .global _i2s2_read_TXL_MSW
        .global _i2s2_write_TXL_MSW
        .global _i2s2_read_TXR_LSW
        .global _i2s2_write_TXR_LSW
        .global _i2s2_read_TXR_MSW
        .global _i2s2_write_TXR_MSW
        .global _i2s2_read_INTR
        .global _i2s2_read_INT_MASK
        .global _i2s2_write_INT_MASK
        .global _i2s2_read_RXL_LSW
        .global _i2s2_write_RXL_LSW
        .global _i2s2_read_RXL_MSW
        .global _i2s2_write_RXL_MSW
        .global _i2s2_read_RXR_LSW
        .global _i2s2_write_RXR_LSW
        .global _i2s2_read_RXR_MSW
        .global _i2s2_write_RXR_MSW
        .global _i2s3_read_CR
        .global _i2s3_write_CR
        .global _i2s3_read_SRGR
        .global _i2s3_write_SRGR
        .global _i2s3_read_TXL_LSW
        .global _i2s3_write_TXL_LSW
        .global _i2s3_read_TXL_MSW
        .global _i2s3_write_TXL_MSW
        .global _i2s3_read_TXR_LSW
        .global _i2s3_write_TXR_LSW
        .global _i2s3_read_TXR_MSW
        .global _i2s3_write_TXR_MSW
        .global _i2s3_read_INTR
        .global _i2s3_read_INT_MASK
        .global _i2s3_write_INT_MASK
        .global _i2s3_read_RXL_LSW
        .global _i2s3_write_RXL_LSW
        .global _i2s3_read_RXL_MSW
        .global _i2s3_write_RXL_MSW
        .global _i2s3_read_RXR_LSW
        .global _i2s3_write_RXR_LSW
        .global _i2s3_read_RXR_MSW
        .global _i2s3_write_RXR_MSW
        .global _enable_i2s0
        .global _enable_i2s1
        .global _enable_i2s2
        .global _enable_i2s3
        .global _disable_i2s0
        .global _disable_i2s1
        .global _disable_i2s2
        .global _disable_i2s3





 
        
;//==============================================================================
;// I2S0 registers
;//==============================================================================
_i2s0_read_CR:
    T0 = *port(I2S0_CR_LSW)
    return

_i2s0_write_CR:
    *port(I2S0_CR_LSW) = T0
    return    

_i2s0_read_SRGR:
    T0 = *port(I2S0_SRGR)
    return

_i2s0_write_SRGR:
    *port(I2S0_SRGR) = T0
    return    

_i2s0_read_TXL_LSW:
    T0 = *port(I2S0_TXW0_LSW)
    return

_i2s0_write_TXL_LSW:
    *port(I2S0_TXW0_LSW) = T0
    return    

_i2s0_read_TXL_MSW:
    T0 = *port(I2S0_TXW0_MSW)
    return

_i2s0_write_TXL_MSW:
    *port(I2S0_TXW0_MSW) = T0
    return    

_i2s0_read_TXR_LSW:
    T0 = *port(I2S0_TXW1_LSW)
    return

_i2s0_write_TXR_LSW:
    *port(I2S0_TXW1_LSW) = T0
    return    

_i2s0_read_TXR_MSW:
    T0 = *port(I2S0_TXW1_MSW)
    return

_i2s0_write_TXR_MSW:
    *port(I2S0_TXW1_MSW) = T0
    return      


_i2s0_read_INTR:
    T0 = *port(I2S0_IR)
    return

_i2s0_read_INT_MASK:
    T0 = *port(I2S0_IMCR)
    return

_i2s0_write_INT_MASK:
    *port(I2S0_IMCR) = T0
    return 

_i2s0_read_RXL_LSW:
    T0 = *port(I2S0_RXW0_LSW)
    return

_i2s0_write_RXL_LSW:
    *port(I2S0_RXW0_LSW) = T0
    return    

_i2s0_read_RXL_MSW:
    T0 = *port(I2S0_RXW0_MSW)
    return

_i2s0_write_RXL_MSW:
    *port(I2S0_RXW0_MSW) = T0
    return    

_i2s0_read_RXR_LSW:
    T0 = *port(I2S0_RXW1_LSW)
    return

_i2s0_write_RXR_LSW:
    *port(I2S0_RXW1_LSW) = T0
    return    

_i2s0_read_RXR_MSW:
    T0 = *port(I2S0_RXW1_MSW)
    return

_i2s0_write_RXR_MSW:
    *port(I2S0_RXW1_MSW) = T0
    return 


;//==============================================================================
;// I2S1 registers
;//==============================================================================
_i2s1_read_CR:
    T0 = *port(I2S1_CR_LSW)
    return

_i2s1_write_CR:
    *port(I2S1_CR_LSW) = T0
    return    

_i2s1_read_SRGR:
    T0 = *port(I2S1_SRGR)
    return

_i2s1_write_SRGR:
    *port(I2S1_SRGR) = T0
    return    

_i2s1_read_TXL_LSW:
    T0 = *port(I2S1_TXW0_LSW)
    return

_i2s1_write_TXL_LSW:
    *port(I2S1_TXW0_LSW) = T0
    return    

_i2s1_read_TXL_MSW:
    T0 = *port(I2S1_TXW0_MSW)
    return

_i2s1_write_TXL_MSW:
    *port(I2S1_TXW0_MSW) = T0
    return    

_i2s1_read_TXR_LSW:
    T0 = *port(I2S1_TXW1_LSW)
    return

_i2s1_write_TXR_LSW:
    *port(I2S1_TXW1_LSW) = T0
    return    

_i2s1_read_TXR_MSW:
    T0 = *port(I2S1_TXW1_MSW)
    return

_i2s1_write_TXR_MSW:
    *port(I2S1_TXW1_MSW) = T0
    return      


_i2s1_read_INTR:
    T0 = *port(I2S1_IR)
    return

_i2s1_read_INT_MASK:
    T0 = *port(I2S1_IMCR)
    return

_i2s1_write_INT_MASK:
    *port(I2S1_IMCR) = T0
    return 

_i2s1_read_RXL_LSW:
    T0 = *port(I2S1_RXW0_LSW)
    return

_i2s1_write_RXL_LSW:
    *port(I2S1_RXW0_LSW) = T0
    return    

_i2s1_read_RXL_MSW:
    T0 = *port(I2S1_RXW0_MSW)
    return

_i2s1_write_RXL_MSW:
    *port(I2S1_RXW0_MSW) = T0
    return    

_i2s1_read_RXR_LSW:
    T0 = *port(I2S1_RXW1_LSW)
    return

_i2s1_write_RXR_LSW:
    *port(I2S1_RXW1_LSW) = T0
    return    

_i2s1_read_RXR_MSW:
    T0 = *port(I2S1_RXW1_MSW)
    return

_i2s1_write_RXR_MSW:
    *port(I2S1_RXW1_MSW) = T0
    return 

;//==============================================================================
;// I2S2 registers
;//==============================================================================
_i2s2_read_CR:
    T0 = *port(I2S2_CR_LSW)
    return

_i2s2_write_CR:
    *port(I2S2_CR_LSW) = T0
    return    

_i2s2_read_SRGR:
    T0 = *port(I2S2_SRGR)
    return

_i2s2_write_SRGR:
    *port(I2S2_SRGR) = T0
    return    

_i2s2_read_TXL_LSW:
    T0 = *port(I2S2_TXW0_LSW)
    return

_i2s2_write_TXL_LSW:
    *port(I2S2_TXW0_LSW) = T0
    return    

_i2s2_read_TXL_MSW:
    T0 = *port(I2S2_TXW0_MSW)
    return

_i2s2_write_TXL_MSW:
    *port(I2S2_TXW0_MSW) = T0
    return    

_i2s2_read_TXR_LSW:
    T0 = *port(I2S2_TXW1_LSW)
    return

_i2s2_write_TXR_LSW:
    *port(I2S2_TXW1_LSW) = T0
    return    

_i2s2_read_TXR_MSW:
    T0 = *port(I2S2_TXW1_MSW)
    return

_i2s2_write_TXR_MSW:
    *port(I2S2_TXW1_MSW) = T0
    return      


_i2s2_read_INTR:
    T0 = *port(I2S2_IR)
    return

_i2s2_read_INT_MASK:
    T0 = *port(I2S2_IMCR)
    return

_i2s2_write_INT_MASK:
    *port(I2S2_IMCR) = T0
    return 

_i2s2_read_RXL_LSW:
    T0 = *port(I2S2_RXW0_LSW)
    return

_i2s2_write_RXL_LSW:
    *port(I2S2_RXW0_LSW) = T0
    return    

_i2s2_read_RXL_MSW:
    T0 = *port(I2S2_RXW0_MSW)
    return

_i2s2_write_RXL_MSW:
    *port(I2S2_RXW0_MSW) = T0
    return    

_i2s2_read_RXR_LSW:
    T0 = *port(I2S2_RXW1_LSW)
    return

_i2s2_write_RXR_LSW:
    *port(I2S2_RXW1_LSW) = T0
    return    

_i2s2_read_RXR_MSW:
    T0 = *port(I2S2_RXW1_MSW)
    return

_i2s2_write_RXR_MSW:
    *port(I2S2_RXW1_MSW) = T0
    return     


;//==============================================================================
;// I2S3 registers
;//==============================================================================
_i2s3_read_CR:
    T0 = *port(I2S3_CR_LSW)
    return

_i2s3_write_CR:
    *port(I2S3_CR_LSW) = T0
    return    

_i2s3_read_SRGR:
    T0 = *port(I2S3_SRGR)
    return

_i2s3_write_SRGR:
    *port(I2S3_SRGR) = T0
    return    

_i2s3_read_TXL_LSW:
    T0 = *port(I2S3_TXW0_LSW)
    return

_i2s3_write_TXL_LSW:
    *port(I2S3_TXW0_LSW) = T0
    return    

_i2s3_read_TXL_MSW:
    T0 = *port(I2S3_TXW0_MSW)
    return

_i2s3_write_TXL_MSW:
    *port(I2S3_TXW0_MSW) = T0
    return    

_i2s3_read_TXR_LSW:
    T0 = *port(I2S3_TXW1_LSW)
    return

_i2s3_write_TXR_LSW:
    *port(I2S3_TXW1_LSW) = T0
    return    

_i2s3_read_TXR_MSW:
    T0 = *port(I2S3_TXW1_MSW)
    return

_i2s3_write_TXR_MSW:
    *port(I2S3_TXW1_MSW) = T0
    return      


_i2s3_read_INTR:
    T0 = *port(I2S3_IR)
    return

_i2s3_read_INT_MASK:
    T0 = *port(I2S3_IMCR)
    return

_i2s3_write_INT_MASK:
    *port(I2S3_IMCR) = T0
    return 

_i2s3_read_RXL_LSW:
    T0 = *port(I2S3_RXW0_LSW)
    return

_i2s3_write_RXL_LSW:
    *port(I2S3_RXW0_LSW) = T0
    return    

_i2s3_read_RXL_MSW:
    T0 = *port(I2S3_RXW0_MSW)
    return

_i2s3_write_RXL_MSW:
    *port(I2S3_RXW0_MSW) = T0
    return    

_i2s3_read_RXR_LSW:
    T0 = *port(I2S3_RXW1_LSW)
    return

_i2s3_write_RXR_LSW:
    *port(I2S3_RXW1_LSW) = T0
    return    

_i2s3_read_RXR_MSW:
    T0 = *port(I2S3_RXW1_MSW)
    return

_i2s3_write_RXR_MSW:
    *port(I2S3_RXW1_MSW) = T0
    return 
                        
;//==============================================================================
;// Function: _enable_i2s0
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void enable_i2s0(void);  
;//============================================================================== 

_enable_i2s0:
    AC0 = *port(#I2S0_CR_LSW)
    AC0 |= 0x8000
    *port(#I2S0_CR_LSW)=AC0
    return

;//==============================================================================
;// Function: _enable_i2s1
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void enable_i2s1(void);  
;//============================================================================== 

_enable_i2s1:
    AC0 = *port(#I2S1_CR_LSW)
    AC0 |= 0x8000
    *port(#I2S1_CR_LSW)=AC0
    return

;//==============================================================================
;// Function: _enable_i2s2
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void enable_i2s2(void);  
;//============================================================================== 

_enable_i2s2:
    AC0 = *port(#I2S2_CR_LSW)
    AC0 |= 0x8000
    *port(#I2S2_CR_LSW)=AC0
    return

;//==============================================================================
;// Function: _enable_i2s3
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void enable_i2s3(void);  
;//============================================================================== 

_enable_i2s3:
    AC0 = *port(#I2S3_CR_LSW)
    AC0 |= 0x8000
    *port(#I2S3_CR_LSW)=AC0
    return

;//==============================================================================
;// Function: _disable_i2s0
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void disable_i2s0(void);  
;//============================================================================== 

_disable_i2s0:
    AC0 = *port(#I2S0_CR_LSW)
    AC0 &= 0x7FFF
    *port(#I2S0_CR_LSW)=AC0
    return

;//==============================================================================
;// Function: _disable_i2s1
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void disable_i2s1(void);  
;//============================================================================== 

_disable_i2s1:
    AC0 = *port(#I2S1_CR_LSW)
    AC0 &= 0x7FFF
    *port(#I2S1_CR_LSW)=AC0
    return

;//==============================================================================
;// Function: _disable_i2s2
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void disable_i2s2(void);  
;//============================================================================== 

_disable_i2s2:
    AC0 = *port(#I2S2_CR_LSW)
    AC0 &= 0x7FFF
    *port(#I2S2_CR_LSW)=AC0
    return

;//==============================================================================
;// Function: _disable_i2s3
;//------------------------------------------------------------------------------
;// Description: 
;// Prototype: void disable_i2s3(void);  
;//============================================================================== 

_disable_i2s3:
    AC0 = *port(#I2S3_CR_LSW)
    AC0 &= 0x7FFF
    *port(#I2S3_CR_LSW)=AC0
    return

    .end