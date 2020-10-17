*****************************************************************************
*  Copyright (c) 2005  Texas Instruments, Inc. All Rights Reserved          *
*  This is proprietary information, not to be published -- TI INTERNAL DATA *
*****************************************************************************

         .mmregs
         .include "lpva200.inc"
         
         
         .C54CM_off
         .CPL_off
         .ARMS_off
   
;**********************************************************************************
;        predefined stack operation modes  
;**********************************************************************************
;        USE_RETA     : 2x16-bit fast return mode (RETA used)
;        NO_RETA      : 2x16-bit slow return mode (RETA not used)
;        C54X_STK     : 32-bit fast return mode 

;**********************************************************************************    
         ;.global _DMA_Isr 
         ;.global _SAR_Isr 
         ;.global _I2S0_TX_Isr
         ;.global _I2S1_RX_Isr
         .global _RTC_Isr
		 .global _Timer_isr
   
             
;**********************************************************************************
        .sect "vector"
        .align  256         
;**********************************************************************************

;****************************************************************************
;* Other interrupt vector definitions go here
;****************************************************************************
	.def	_RST
_RST:		.ivec    reset_isr, USE_RETA; Reset / Software Interrupt #0

NMI:		.ivec    reset_isr				; Nonmaskable Interrupt

INT0:		.ivec    dummy_isr				; External User Interrupt #0 

INT1:		.ivec    dummy_isr				; External User Interrupt #1

TINT0:		.ivec    _Timer_isr				; Timer #0 / Software Interrupt #4

;PROG0:		.ivec    _I2S0_TX_Isr			; Programmable 0 Interrupt
PROG0:		.ivec    dummy_isr			; Programmable 0 Interrupt

UART:		.ivec    dummy_isr				; IIS #1 Receive Interrupt

PROG1:		.ivec    dummy_isr				; Programmable 1 Interrupt

;DMA:		.ivec    _DMA_Isr                ; DMA Interrupt
DMA:		.ivec    dummy_isr                ; DMA Interrupt

PROG2:		.ivec    dummy_isr			; Programmable 2 Interrupt

COPROCFFT:  .ivec    dummy_isr			; Coprocessor FFT Module Interrupt

;PROG3:		.ivec    _I2S1_RX_Isr			; Programmable 3 Interrupt
PROG3:		.ivec    dummy_isr			; Programmable 3 Interrupt

LCD:		.ivec	 dummy_isr				; LCD Interrupt

SARADC:		.ivec    dummy_isr				; SAR ADC Interrupt

XMIT2:		.ivec	 dummy_isr		    ; I2S2 Tx Interrupt

RCV2:		.ivec	 dummy_isr		    ; I2S2 Rx Interrupt

XMIT3:		.ivec	 dummy_isr		    ; I2S3 Tx Interrupt

RCV3:		.ivec	 dummy_isr		    ; I2S3 Rx Interrupt

RTC:		.ivec    _RTC_Isr				; RTC interrupt

SPI:    	.ivec    dummy_isr				; SPI Receive Interrupt

USB:		.ivec    dummy_isr				; USB Transmit Interrupt

GPIO:		.ivec    dummy_isr				; GPIO Interrupt

EMIF:	    .ivec    dummy_isr			    ; EMIF Interrupt

I2C:		.ivec    dummy_isr				; IIC interrupt

BERRIV:
IV24:		.ivec	 dummy_isr   ; Bus error interrupt

;    .ref  _DLOGINT_isr 
DLOGIV:
IV25:		.ivec   dummy_isr  ; Data log (RTDX) interrupt

;	.ref _RTOSINT_isr
RTOSIV:
IV26:		.ivec dummy_isr  ; Real-time OS interrupt
IV27:		.ivec dummy_isr  ; General-purpose software-only interrupt
IV28:		.ivec dummy_isr  ; General-purpose software-only interrupt
IV29:		.ivec dummy_isr  ; General-purpose software-only interrupt
IV30:		.ivec dummy_isr  ; General-purpose software-only interrupt
IV31:		.ivec dummy_isr  ; General-purpose software-only interrupt


;****************************************************************************
;* Reset 
;****************************************************************************

		.text
		.def reset_isr
		.ref _c_int00
		
        .align 2		
reset_isr:
	;	*port(#0x1C01) = #0x0				; Clear idles
		bit (ST1, #11) = #1					; Disable interrupts
    	@IVPD_L = #(_RST >> 8) || mmap()
    	@IVPH_L = #(_RST >> 8) || mmap()
	   	 bit(ST3,#7) = #0		; Clear bus error interrupts
	   	 bit(ST3,#2) = #0		; turn on clockout port
	   	 bit(ST1,#13) = #0		; shut off XF port

		@#IFR0_L = #0xffff || mmap() ; clear all pending interrupts
		@#IFR1_L = #0xffff || mmap()

		*port(#IDLE_ICR) = #(RESERVED_ICR|IPORT_IDLE|HWA_IDLE|DPORT_IDLE)
		idle

;**********************************************************************************
;     Reset all peripherals
;**********************************************************************************
	*port(#0x1C04) = 0x1
	nop_16
	*port(#0x1C05) = 0x00FB	; Reset all peripherals
	nop_16


;**********************************************************************************
;     Enalbe EMIF
;**********************************************************************************

    *port(IDLE_PCGCR) = #0x0

    ;/* Config EMIF - System Control Regsiter */
    *port(#0x1C33) = #0x0  

    ;// for SRAM in memory card (Async_CE1)
    ;/* Config EMIF - ASYNC Regsiters */
    *port(#0x1004) = #0x0080     
    *port(#0x1005) = #0x00E4     

	;/* Configure as 16-bit data bus */    
    ;// Async4 ==> Async_CE1 (SRAM)	
    *port(#0x101C) = #0x40AD     
    *port(#0x101D) = #0x0020     

    ;// Async3 ==> Async_CE0(Flash)
    *port(#0x1018) = #0xFFFD     
    *port(#0x1019) = #0x3FFF     


    ;// do not assign Async_CE0 and Async_CE1 for NAND
    *port(#0x1060) = #0x0003     
    
    ;// Turn off page mode for all Chip Selects
    *port(#0x1068) = #0xFCFC     
    *port(#0x1069) = #0xFCFC     

	goto	_c_int00
		
********************************************************************************
** Name     : no_isr                                                          **
**                                                                            **
** Purpose  : Spurious interrupt handler                                      **
**                                                                            **
** Author   :                                                                 **
**                                                                            **
********************************************************************************
             .text   
no_isr:      goto no_isr 


dummy_isr:
    return_int
 
    
    .end