;****************************************************************************************
;    File Name   : aic_test_main.asm
;    Author      : Sunil Kamath
;
;    Version     : 2
;    Date        : 30 April 2008
;    Update      : with Ping Pong Buffering
;
;    Description : Code for playback using I2S2 and DMA1 to AIC3254
;
;****************************************************************************************
        .mmregs
        ;.global  BOOT_START, _SETUP, no_isr, i2c_PutData8, Config_DMA, _AIC3254_init
        ;.global  ISR_DMA, ISR_XMT2, ISR_RCV2

        .global  _AIC3254_init

        .include "lpva200.inc"

        .text
        ;.copy    "setup_da200.inc"                            ; setup code

        .C54CM_off
        .CPL_off
        .ARMS_off
 
;****************************************************************************************
;   Define constants
;****************************************************************************************
I2C_CLKDIV_VAL   .set     35
AIC3254_I2C_ADDR .set    0x18


DO_I2S_MASTER   .set     0        ; DO_I2S_MASTER = 1 to use I2S in master mode   
                                  ; DO_I2S_MASTER = 0 to use I2S in slave mode
DO_48K          .set     1        ; DO_48K = 1 to use 48 KHz sampling frequency  
                                  ; DO_48K = 0 to use 12 KHz sampling frequency

;****************************************************************************************
        .text 
;****************************************************************************************
;****************************************************************************************
;   Configure AIC3254
;****************************************************************************************
_AIC3254_init:
;****************************************************************************************
; Configure I2C
;****************************************************************************************
 .if 1
        ; Reset all Modules
        ;*port(#0x1C04) = #0x0020;
        ;*port(#0x1C05) = #0x00FF;

        ; Set GPIO26 as output
		T0 = *port(#0x1C00)
        T0 |= #0x003F
        *port(#0x1C00) = T0
        repeat(#9)
        NOP_16

        T0 = *port(#0x1C07)
        T0 |= #0x0400
        *port(#0x1C07) = T0
        repeat(#9)
        NOP_16
        ; Set GPIO26 = 0
        T0 = *port(#0x1C0B)
        T0 &= #0xFBFF
        *port(#0x1C0B) = T0
        repeat(#99)
        NOP_16
        ; Set GPIO26 = 1
        T0 = *port(#0x1C0B)
        T0 |= #0x0400
        *port(#0x1C0B) = T0
        repeat(#9)
        NOP_16

        ; Initialize IIC
        *port(#I2C_PSC)   = #0x0004            ; Set prescaler to divide by 4+1=5
                                               ; I2C CLK = 49.156 MHZ / 5 = 9.8312 MHz
        *port(#I2C_CLKL)  = #(I2C_CLKDIV_VAL)  ; CPU clock divided by 35+5 for low period 
        *port(#I2C_CLKH)  = #(I2C_CLKDIV_VAL)  ; CPU clock divided by 35+5 for high period
                                               ;   SCL_High_Period = (1/9.8312M) *(35+5) = 4.07us
                                               ;   SCL_Low_Period = (1/9.8312) *(35+5) = 4.07us
											   ;   1/(4.07u+4.07u) = 122.9 KHz
        *port(#I2C_OAR)   = #0x002F            ; I2C Address - 5515 is set to 01011xx
        *port(#I2C_MDR)   = #0x0400            ; Place I2C module in reset
        repeat(#(8999))
        NOP_16

        *port(#I2C_MDR)   = #0x0420            ; master, transmitter,out of reset, 7-bit address
        *port(#I2C_EMDR)  = #0x000             ; Backward compatibility mode free data mode disabled

        *port(#I2C_SAR)   = #AIC3254_I2C_ADDR  ; I2C Address for AIC3254

;****************************************************************************************
; Configure AIC3254
;****************************************************************************************
	    ; Point to page 0
        AC1 = #0
        AR1 = #0x0
        call i2c_WriteData8

        ;reset codec
        AC1 = #1
        AR1 = #0x1
        call i2c_WriteData8

	    ; Point to page 1
        AC1 = #0
        AR1 = #0x1
        call i2c_WriteData8
        AC1 = #0
;        call i2c_ReadData8

        ;Disable crude AVDD generation from DVDD
        AC1 = #1
        AR1 = #0x08
        call i2c_WriteData8
        AC1 = #1
;        call i2c_ReadData8

        ;Enable Analog Blocks and LDO
        AC1 = #2
        AR1 = #0x01
        call i2c_WriteData8

		;***********************************************************************
        ;* PLL and Clocks config and Power Up                                  
		;***********************************************************************
	    ; Point to page 0
        AC1 = #0
        AR1 = #0x0
        call i2c_WriteData8

 .if (!DO_I2S_MASTER) ;AIC is master running off of 12 MHz crystal
        ;BCLK and WCLK is set as op to AIC3254(Master)
        AC1 = #27
        AR1 = #0x0D
        call i2c_WriteData8

        ;PLL setting: PLLCLK <- MCLK and CODEC_CLKIN <-PLL CLK
        AC1 = #4
        AR1 = #0x03
        call i2c_WriteData8

        ;PLL setting: J=8
        AC1 = #6
        AR1 = #0x08
        call i2c_WriteData8

        ;PLL setting: HI_BYTE(D) for D=0x0780 (or 1920 decimal)
        AC1 = #7
        AR1 = #0x07
        call i2c_WriteData8

        ;PLL setting: LO_BYTE(D) for D=0x0780
        AC1 = #8
        AR1 = #0x80
        call i2c_WriteData8

	 .if (DO_48K) ;for 48 KHz sampling
	        ;For 32 bit clocks per frame in Master mode ONLY
            ;BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
	        AC1 = 30
	        AR1 = 0x88
	        call i2c_WriteData8
	 .else ;for 12 KHz sampling
	        ;For 32 bit clocks per frame in Master mode ONLY
            ;BCLK=DAC_CLK/N =(12288000/32) = 384 KHz = 32*fs
	        AC1 = 30
	        AR1 = 0xA0
	        call i2c_WriteData8
     .endif
        
		;PLL setting: Power up PLL, P=1 and R=1
        AC1 = #5
        AR1 = #0x91
        call i2c_WriteData8

 .else  ;For AIC Slave running off of 768 kHz or 1.536 MHz BCLK supplied by I2S
        ;BCLK and WCLK is set as ip to AIC3254(slave)
        AC1 = #27
        AR1 = #0x00
        call i2c_WriteData8

        ;PLL setting: PLLCLK <- BCLK and CODEC_CLKIN <-PLL CLK
        AC1 = #4
        AR1 = #0x07
        call i2c_WriteData8

        ;PLL setting: J=32
        AC1 = #6
        AR1 = #0x20
        call i2c_WriteData8

        ;PLL setting: HI_BYTE(D) for D=0x0 (or 0 decimal)
        AC1 = #7
        AR1 = #0x00
        call i2c_WriteData8

        ;PLL setting: LO_BYTE(D) for D=0x0
        AC1 = #8
        AR1 = #0x00
        call i2c_WriteData8

	 .if (DO_48K) ;for 48 KHz sampling
			;PLL setting: Power up PLL, P=1 and R=2
	        AC1 = #5
	        AR1 = #0x92
	        call i2c_WriteData8
	 .else ;for 12 KHz sampling
			;PLL setting: Power up PLL, P=1 and R=4
	        AC1 = #5
	        AR1 = #0x94
	        call i2c_WriteData8
     .endif
 .endif

 .if (DO_48K) ;for 48 KHz sampling
		;Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
	    AC1 = #13
	    AR1 = #0x00
	    call i2c_WriteData8

		;Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
	    AC1 = #14
	    AR1 = #0x80
	    call i2c_WriteData8
 .else ;for 12 KHz sampling
		;Hi_Byte(DOSR) for DOSR = 512 decimal or 0x0200 DAC oversamppling
	    AC1 = #13
	    AR1 = #0x02
	    call i2c_WriteData8

		;Lo_Byte(DOSR) for DOSR = 512 decimal or 0x0200
	    AC1 = #14
	    AR1 = #0x00
	    call i2c_WriteData8
 .endif

		;AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
	    AC1 = #20
	    AR1 = #0x80
	    call i2c_WriteData8

		;Power up NDAC and set NDAC value to 8
	    AC1 = #11
	    AR1 = #0x88
	    call i2c_WriteData8

		;Power up MDAC and set MDAC value to 2
	    AC1 = #12
	    AR1 = #0x82
	    call i2c_WriteData8

		;Power up NADC and set NADC value to 8
	    AC1 = #18
	    AR1 = #0x88
	    call i2c_WriteData8

 .if (DO_48K) ;for 48 KHz sampling
		;Power up MADC and set MADC value to 2
	    AC1 = #19
	    AR1 = #0x82
	    call i2c_WriteData8
 .else ;for 12 KHz sampling
		;Power up MADC and set MADC value to 8
	    AC1 = #19
	    AR1 = #0x88
	    call i2c_WriteData8
 .endif


		;***********************************************************************
        ;* DAC ROUTING and Power Up                                            
		;***********************************************************************
        ;Select page 1
        AC1 = 0
        AR1 = 0x01
        call i2c_WriteData8

        ;LDAC AFIR routed to HPL
        AC1 = 0xC
        AR1 = 0x08
        call i2c_WriteData8

        ;RDAC AFIR routed to HPR
        AC1 = 0xD
        AR1 = 0x08
        call i2c_WriteData8

        ;Select page 0
        AC1 = 0
        AR1 = 0x00
        call i2c_WriteData8

        ;Left vol=right vol
        AC1 = 64
        AR1 = 0x02
        call i2c_WriteData8

        ;Left DAC gain to 0dB VOL; Right tracks Left
        AC1 = 65
        AR1 = 0x00
        call i2c_WriteData8

        ;Power up left,right data paths and set channel
        AC1 = 63
        AR1 = 0xD4
        call i2c_WriteData8

        ;Select page 1
        AC1 = 0
        AR1 = 0x01
        call i2c_WriteData8

        ;Unmute HPL , 0dB gain
        AC1 = 0x10
        AR1 = 0x00
        call i2c_WriteData8

        ;Unmute HPR , 0dB gain
        AC1 = 0x11
        AR1 = 0x00
        call i2c_WriteData8

        ;Power up HPL,HPR
        AC1 = 9
        AR1 = 0x30
        call i2c_WriteData8

		;Select page 0
        AC1 = 0
        AR1 = 0x00
        call i2c_WriteData8

		@BRC0_L = #0x02FF || mmap()
		localrepeat {
			repeat(#0xFFFF)
			NOP_16
			NOP_16
		}

		;***********************************************************************
        ;* ADC ROUTING and Power Up                                            
		;***********************************************************************
		;Select page 1
	    AC1 = #0
	    AR1 = #0x01
	    call i2c_WriteData8

 .if 0 ;STEREO 2 Jacks are not connected properly on board A15
		;IN3_L to LADC_P through 40 kohm
	    AC1 = #0x34
	    AR1 = #0x0C
	    call i2c_WriteData8

		;IN3_R to RADC_P through 40 kohmm
	    AC1 = #0x37
	    AR1 = #0x0C
	    call i2c_WriteData8
 .else  ;STEREO 1 Jack
		;IN2_L to LADC_P through 40 kohm
	    AC1 = #0x34
	    AR1 = #0x30
	    call i2c_WriteData8

		;IN2_R to RADC_P through 40 kohmm
	    AC1 = #0x37
	    AR1 = #0x30
	    call i2c_WriteData8
 .endif

		;CM_1 (common mode) to LADC_M through 40 kohm
	    AC1 = #0x36
	    AR1 = #0x03
	    call i2c_WriteData8

		;CM_1 (common mode) to RADC_M through 40 kohm
	    AC1 = #0x39
	    AR1 = #0xC0
	    call i2c_WriteData8

		;MIC_PGA_L unmute
	    AC1 = #0x3B
	    AR1 = #0x00
	    call i2c_WriteData8

		;MIC_PGA_R unmute
	    AC1 = #0x3C
	    AR1 = #0x00
	    call i2c_WriteData8

        ;Select page 0
        AC1 = 0
        AR1 = 0x00
        call i2c_WriteData8

        ;Powerup Left and Right ADC
        AC1 = 0x51
        AR1 = 0xC0
        call i2c_WriteData8

        ;Unmute Left and Right ADC
        AC1 = 0x52
        AR1 = 0x00
        call i2c_WriteData8

        ;Dummy read
        AC1 = 9
        AR1 = 0xABAB
;        call i2c_ReadData8
 .endif

i2c_WriteData8:
	    
		; Data count register = 2 for 1)address + 2)data
		*port(#I2C_CNT) = #0x0002

		; Disable interrupts
		*port(#I2C_IMR) = #0000

        repeat(#99)
		NOP_16

	    ; Place I2C as transmitter
	    *port(#I2C_MDR) = #0010011000100000b        ; Master transit with Start
		                  ;0~~~~~~~~~~~~~~~ NACK MOD - Master Receiver Mode: 
	                      ;                 1 -> the I2C sends NACK to transmitter during acknowledge cycle.
	                      ;                 0 -> the I2C sends ACK to transmitter during acknowledge cycle.
	                      ;~0~~~~~~~~~~~~~~ FREE: 0-> Disable free-run 1 -> I2C runs free during debugger breakpoint.
	                      ;~~1~~~~~~~~~~~~~ STT - Start Condition Bit: 1 -> (master mode) generates start condition (STP = 0).
	                      ;~~~0~~~~~~~~~~~~ Reserved (?)
	                      ;~~~~1~~~~~~~~~~~ STP: Set to 1 to generate STOP condition.
	                      ;~~~~~1~~~~~~~~~~ MST: 1 -> I2C is in master mode.
	                      ;~~~~~~1~~~~~~~~~ TRX - Transmitter: 0 -> I2C is in receiver mode 
	                                        ; MST|TRX = 10 -> master receiver mode.
	                                        ; MST|TRX = 11 -> master transmitter mode.
	                      ;~~~~~~~0~~~~~~~~ XA - Expanded Address: 0 -> 7-bit address mode, 1 -> 10-bit address mode.
	                      ;~~~~~~~~0~~~~~~~ RM - Repeat Mode
	                                        ; RM|STT|STP = 110 -> (Re) Start: S-A-D-D-D-D... continuous
	                      ;~~~~~~~~~0~~~~~~ DLB - Digital Loopback Mode: 1 -> I2C in digital loopback mode.
	                      ;~~~~~~~~~~1~~~~~ nIRS: 1 -> I2C not in reset, 0 -> I2C in reset.
	                      ;~~~~~~~~~~~0~~~~ START byte mode: 0 -> I2C in not in START byte mode.
	                      ;~~~~~~~~~~~~0~~~ 1 -> I2C is in free data format (Figure 6d).
	                      ;~~~~~~~~~~~~~000 BC - Bit Count, number of bits which are yet to be received/tranmsitted. 
        repeat(#99)
		NOP_16
	    call i2c_wait_for_slave_ack 
		call i2c_wait_for_tx

	    ; Place Register Address in TX data register
	    AC1 = AC1 & #0x00FF
	    *port(#I2C_DXR) = AC1	            ; place address
        repeat(#99)
		NOP_16
	    call i2c_wait_for_slave_ack 
	    call i2c_wait_for_tx
	        
	    AC2 = AR1 & 0x00FF
	    *port(#I2C_DXR) = AC2				; write data
        repeat(#99)
		NOP_16
	    call i2c_wait_for_slave_ack 

        repeat(#99)
		NOP_16

        return

;****************************************************************************************
;	i2c_ReadData8 - Reads 8-bits
;****************************************************************************************
i2c_ReadData8:

		; Data count register = 2 for 1)address + 2)data
		*port(#I2C_CNT) = #0x0000

	    ; Place I2C as transmitter
        *port(#I2C_MDR) = #0010001010100000b        ; Master transit with Start
		                  ;0~~~~~~~~~~~~~~~ NACK MOD - Master Receiver Mode: 
	                      ;                 1 -> the I2C sends NACK to transmitter during acknowledge cycle.
	                      ;                 0 -> the I2C sends ACK to transmitter during acknowledge cycle.
	                      ;~0~~~~~~~~~~~~~~ FREE: 0-> Disable free-run 1 -> I2C runs free during debugger breakpoint.
	                      ;~~1~~~~~~~~~~~~~ STT - Start Condition Bit: 1 -> (master mode) generates start condition (STP = 0).
	                      ;~~~0~~~~~~~~~~~~ Reserved (?)
	                      ;~~~~0~~~~~~~~~~~ STP: Set to 1 to generate STOP condition.
	                      ;~~~~~1~~~~~~~~~~ MST: 1 -> I2C is in master mode.
	                      ;~~~~~~1~~~~~~~~~ TRX - Transmitter: 0 -> I2C is in receiver mode 
	                                        ; MST|TRX = 10 -> master receiver mode.
	                                        ; MST|TRX = 11 -> master transmitter mode.
	                      ;~~~~~~~0~~~~~~~~ XA - Expanded Address: 0 -> 7-bit address mode, 1 -> 10-bit address mode.
	                      ;~~~~~~~~1~~~~~~~ RM - Repeat Mode
	                                        ; RM|STT|STP = 110 -> (Re) Start: S-A-D-D-D-D... continuous
	                      ;~~~~~~~~~0~~~~~~ DLB - Digital Loopback Mode: 1 -> I2C in digital loopback mode.
	                      ;~~~~~~~~~~1~~~~~ nIRS: 1 -> I2C not in reset, 0 -> I2C in reset.
	                      ;~~~~~~~~~~~0~~~~ START byte mode: 0 -> I2C in not in START byte mode.
	                      ;~~~~~~~~~~~~0~~~ 1 -> I2C is in free data format (Figure 6d).
	                      ;~~~~~~~~~~~~~000 BC - Bit Count, number of bits which are yet to be received/tranmsitted. 
        repeat(#99)
		NOP_16
	    call i2c_wait_for_slave_ack 
		call i2c_wait_for_tx

	    ; Place Register Address in TX data register
	    AC1 = AC1 & #0x00FF
	    *port(#I2C_DXR) = AC1	            ; place address
        repeat(#99)
		NOP_16
	    call i2c_wait_for_slave_ack 
	    call i2c_wait_for_tx
	        
        ; Place I2C in receive mode
	    *port(#I2C_MDR) = #0000010010100000b        ; Master transit with Start
		                  ;0~~~~~~~~~~~~~~~ NACK MOD - Master Receiver Mode: 
	                      ;                 1 -> the I2C sends NACK to transmitter during acknowledge cycle.
	                      ;                 0 -> the I2C sends ACK to transmitter during acknowledge cycle.
	                      ;~0~~~~~~~~~~~~~~ FREE: 0-> Disable free-run 1 -> I2C runs free during debugger breakpoint.
	                      ;~~0~~~~~~~~~~~~~ STT - Start Condition Bit: 1 -> (master mode) generates start condition (STP = 0).
	                      ;~~~0~~~~~~~~~~~~ Reserved (?)
	                      ;~~~~0~~~~~~~~~~~ STP: Set to 1 to generate STOP condition.
	                      ;~~~~~1~~~~~~~~~~ MST: 1 -> I2C is in master mode.
	                      ;~~~~~~0~~~~~~~~~ TRX - Transmitter: 0 -> I2C is in receiver mode 
	                                        ; MST|TRX = 10 -> master receiver mode.
	                                        ; MST|TRX = 11 -> master transmitter mode.
	                      ;~~~~~~~0~~~~~~~~ XA - Expanded Address: 0 -> 7-bit address mode, 1 -> 10-bit address mode.
	                      ;~~~~~~~~1~~~~~~~ RM - Repeat Mode
	                                        ; RM|STT|STP = 110 -> (Re) Start: S-A-D-D-D-D... continuous
	                      ;~~~~~~~~~0~~~~~~ DLB - Digital Loopback Mode: 1 -> I2C in digital loopback mode.
	                      ;~~~~~~~~~~1~~~~~ nIRS: 1 -> I2C not in reset, 0 -> I2C in reset.
	                      ;~~~~~~~~~~~0~~~~ START byte mode: 0 -> I2C in not in START byte mode.
	                      ;~~~~~~~~~~~~0~~~ 1 -> I2C is in free data format (Figure 6d).
	                      ;~~~~~~~~~~~~~000 BC - Bit Count, number of bits which are yet to be received/tranmsitted. 

        ; Set NACK to finish read cycle
;	    *port(#I2C_MDR) = #1000010010100000b        ; Master transit with Start
		                  ;1~~~~~~~~~~~~~~~ NACK MOD - Master Receiver Mode: 
	                      ;                 1 -> the I2C sends NACK to transmitter during acknowledge cycle.
	                      ;                 0 -> the I2C sends ACK to transmitter during acknowledge cycle.
	                      ;~0~~~~~~~~~~~~~~ FREE: 0-> Disable free-run 1 -> I2C runs free during debugger breakpoint.
	                      ;~~0~~~~~~~~~~~~~ STT - Start Condition Bit: 1 -> (master mode) generates start condition (STP = 0).
	                      ;~~~0~~~~~~~~~~~~ Reserved (?)
	                      ;~~~~0~~~~~~~~~~~ STP: Set to 1 to generate STOP condition.
	                      ;~~~~~1~~~~~~~~~~ MST: 1 -> I2C is in master mode.
	                      ;~~~~~~0~~~~~~~~~ TRX - Transmitter: 0 -> I2C is in receiver mode 
	                                        ; MST|TRX = 10 -> master receiver mode.
	                                        ; MST|TRX = 11 -> master transmitter mode.
	                      ;~~~~~~~0~~~~~~~~ XA - Expanded Address: 0 -> 7-bit address mode, 1 -> 10-bit address mode.
	                      ;~~~~~~~~1~~~~~~~ RM - Repeat Mode
	                                        ; RM|STT|STP = 110 -> (Re) Start: S-A-D-D-D-D... continuous
	                      ;~~~~~~~~~0~~~~~~ DLB - Digital Loopback Mode: 1 -> I2C in digital loopback mode.
	                      ;~~~~~~~~~~1~~~~~ nIRS: 1 -> I2C not in reset, 0 -> I2C in reset.
	                      ;~~~~~~~~~~~0~~~~ START byte mode: 0 -> I2C in not in START byte mode.
	                      ;~~~~~~~~~~~~0~~~ 1 -> I2C is in free data format (Figure 6d).
	                      ;~~~~~~~~~~~~~000 BC - Bit Count, number of bits which are yet to be received/tranmsitted. 

        repeat(#99)
		NOP_16
        ; Generate start condition
	    *port(#I2C_MDR) = #1010010010100000b        ; Master transit with Start
		                  ;0~~~~~~~~~~~~~~~ NACK MOD - Master Receiver Mode: 
	                      ;                 1 -> the I2C sends NACK to transmitter during acknowledge cycle.
	                      ;                 0 -> the I2C sends ACK to transmitter during acknowledge cycle.
	                      ;~0~~~~~~~~~~~~~~ FREE: 0-> Disable free-run 1 -> I2C runs free during debugger breakpoint.
	                      ;~~1~~~~~~~~~~~~~ STT - Start Condition Bit: 1 -> (master mode) generates start condition (STP = 0).
	                      ;~~~0~~~~~~~~~~~~ Reserved (?)
	                      ;~~~~0~~~~~~~~~~~ STP: Set to 1 to generate STOP condition.
	                      ;~~~~~1~~~~~~~~~~ MST: 1 -> I2C is in master mode.
	                      ;~~~~~~0~~~~~~~~~ TRX - Transmitter: 0 -> I2C is in receiver mode 
	                                        ; MST|TRX = 10 -> master receiver mode.
	                                        ; MST|TRX = 11 -> master transmitter mode.
	                      ;~~~~~~~0~~~~~~~~ XA - Expanded Address: 0 -> 7-bit address mode, 1 -> 10-bit address mode.
	                      ;~~~~~~~~1~~~~~~~ RM - Repeat Mode
	                                        ; RM|STT|STP = 110 -> (Re) Start: S-A-D-D-D-D... continuous
	                      ;~~~~~~~~~0~~~~~~ DLB - Digital Loopback Mode: 1 -> I2C in digital loopback mode.
	                      ;~~~~~~~~~~1~~~~~ nIRS: 1 -> I2C not in reset, 0 -> I2C in reset.
	                      ;~~~~~~~~~~~0~~~~ START byte mode: 0 -> I2C in not in START byte mode.
	                      ;~~~~~~~~~~~~0~~~ 1 -> I2C is in free data format (Figure 6d).
	                      ;~~~~~~~~~~~~~000 BC - Bit Count, number of bits which are yet to be received/tranmsitted. 

        repeat(#99)
		NOP_16
	    call i2c_wait_for_slave_ack 
        call i2c_wait_for_data

	    AC2 = *port(#I2C_DRR)				; read data
	    AR1 = AC2 & 0x00FF

	    ; Place I2C as transmitter
	    *port(#I2C_MDR) = #1010011010100000b        ; Master transit with Start
		                  ;0~~~~~~~~~~~~~~~ NACK MOD - Master Receiver Mode: 
	                      ;                 1 -> the I2C sends NACK to transmitter during acknowledge cycle.
	                      ;                 0 -> the I2C sends ACK to transmitter during acknowledge cycle.
	                      ;~0~~~~~~~~~~~~~~ FREE: 0-> Disable free-run 1 -> I2C runs free during debugger breakpoint.
	                      ;~~1~~~~~~~~~~~~~ STT - Start Condition Bit: 1 -> (master mode) generates start condition (STP = 0).
	                      ;~~~0~~~~~~~~~~~~ Reserved (?)
	                      ;~~~~0~~~~~~~~~~~ STP: Set to 1 to generate STOP condition.
	                      ;~~~~~1~~~~~~~~~~ MST: 1 -> I2C is in master mode.
	                      ;~~~~~~1~~~~~~~~~ TRX - Transmitter: 0 -> I2C is in receiver mode 
	                                        ; MST|TRX = 10 -> master receiver mode.
	                                        ; MST|TRX = 11 -> master transmitter mode.
	                      ;~~~~~~~0~~~~~~~~ XA - Expanded Address: 0 -> 7-bit address mode, 1 -> 10-bit address mode.
	                      ;~~~~~~~~1~~~~~~~ RM - Repeat Mode
	                                        ; RM|STT|STP = 110 -> (Re) Start: S-A-D-D-D-D... continuous
	                      ;~~~~~~~~~0~~~~~~ DLB - Digital Loopback Mode: 1 -> I2C in digital loopback mode.
	                      ;~~~~~~~~~~1~~~~~ nIRS: 1 -> I2C not in reset, 0 -> I2C in reset.
	                      ;~~~~~~~~~~~0~~~~ START byte mode: 0 -> I2C in not in START byte mode.
	                      ;~~~~~~~~~~~~0~~~ 1 -> I2C is in free data format (Figure 6d).
	                      ;~~~~~~~~~~~~~000 BC - Bit Count, number of bits which are yet to be received/tranmsitted. 


	    ; I2C Set back ACK_enable
	    *port(#I2C_MDR) = #1010011010100000b        ; Master transit with Start
		                  ;1~~~~~~~~~~~~~~~ NACK MOD - Master Receiver Mode: 
	                      ;                 1 -> the I2C sends NACK to transmitter during acknowledge cycle.
	                      ;                 0 -> the I2C sends ACK to transmitter during acknowledge cycle.
	                      ;~0~~~~~~~~~~~~~~ FREE: 0-> Disable free-run 1 -> I2C runs free during debugger breakpoint.
	                      ;~~1~~~~~~~~~~~~~ STT - Start Condition Bit: 1 -> (master mode) generates start condition (STP = 0).
	                      ;~~~0~~~~~~~~~~~~ Reserved (?)
	                      ;~~~~0~~~~~~~~~~~ STP: Set to 1 to generate STOP condition.
	                      ;~~~~~1~~~~~~~~~~ MST: 1 -> I2C is in master mode.
	                      ;~~~~~~1~~~~~~~~~ TRX - Transmitter: 0 -> I2C is in receiver mode 
	                                        ; MST|TRX = 10 -> master receiver mode.
	                                        ; MST|TRX = 11 -> master transmitter mode.
	                      ;~~~~~~~0~~~~~~~~ XA - Expanded Address: 0 -> 7-bit address mode, 1 -> 10-bit address mode.
	                      ;~~~~~~~~1~~~~~~~ RM - Repeat Mode
	                                        ; RM|STT|STP = 110 -> (Re) Start: S-A-D-D-D-D... continuous
	                      ;~~~~~~~~~0~~~~~~ DLB - Digital Loopback Mode: 1 -> I2C in digital loopback mode.
	                      ;~~~~~~~~~~1~~~~~ nIRS: 1 -> I2C not in reset, 0 -> I2C in reset.
	                      ;~~~~~~~~~~~0~~~~ START byte mode: 0 -> I2C in not in START byte mode.
	                      ;~~~~~~~~~~~~0~~~ 1 -> I2C is in free data format (Figure 6d).
	                      ;~~~~~~~~~~~~~000 BC - Bit Count, number of bits which are yet to be received/tranmsitted. 


	    *port(#I2C_MDR) = #0010111010100000b ; Stop I2S transmission
        repeat(#1999)
		NOP_16

        return

;****************************************************************************************
;   i2c_wait_for_bus_busy - Waits for bus to be unused
;****************************************************************************************
i2c_wait_for_bus_busy:
	    T1 = *port(#I2C_STR)             ; wait for bus busy flag set (BB)
	    T0 = T1 & #ICBB_FLAG
	    if ( T0 != #0 ) goto i2c_wait_for_bus_busy ; bus is being used
	    return

;****************************************************************************************
;   i2c_wait_for_slave_ack - Waits for Slave ACK
;****************************************************************************************
i2c_wait_for_slave_ack:
	    T1 = *port(#I2C_STR)             ; wait for ack flag cleared (NACK)
	    T0 = T1 & #ICNACK_FLAG
	    if ( T0 != #0 ) goto i2c_wait_for_slave_ack ; still no ack
	    *port(#I2C_STR) = #ICNACK_FLAG    ; clear NACK
	    return

;****************************************************************************************
;   i2c_wait_for_tx - Waits for Data Transmit
;****************************************************************************************
i2c_wait_for_tx:
	    T1 = *port(#I2C_STR)             ; wait for transmit flag set (ICXRDY)
	    T0 = T1 & #ICXRDY_FLAG
	    if ( T0 == #0 ) goto i2c_wait_for_tx ; still in transmission
	    *port(#I2C_STR) = #ICXRDY_FLAG    ; clear ICXRDY
	    return

;****************************************************************************************
;   i2c_wait_for_data - Waits for Data receive
;****************************************************************************************
i2c_wait_for_data:
	    T1 = *port(#I2C_STR)             ; wait for transmit flag set (ICRRDY)
	    T0 = T1 & #ICRRDY_FLAG
	    if ( T0 == #0 ) goto i2c_wait_for_data ; still in transmission
	    *port(#I2C_STR) = #ICRRDY_FLAG    ; clear ICRRDY
	    return

;****************************************************************************************
;   i2c_wait_for_register_access - Waits for register access ready
;****************************************************************************************
i2c_wait_for_register_access:
	    T1 = *port(#I2C_STR)             ; wait for register access ready (ARDY)
	    T0 = T1 & #ICBB_FLAG
	    if ( T0 == #0 ) goto i2c_wait_for_register_access ; registers are being used
	    return

;****************************************************************************************
;   i2c_wait_for_stop - Waits for stop condition
;****************************************************************************************
i2c_wait_for_stop:
	    T1 = *port(#I2C_STR)             ; wait for stop condition (SCD)
	    T0 = T1 & #ICSCD_FLAG
	    if ( T0 == #0 ) goto i2c_wait_for_stop ; no stop yet
	    *port(#I2C_STR) = #ICSCD_FLAG    ; clear SCD
	    return

;****************************************************************************************
