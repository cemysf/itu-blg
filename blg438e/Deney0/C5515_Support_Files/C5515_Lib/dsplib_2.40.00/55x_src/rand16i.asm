;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Filename:	rand16init.asm
; Processor:   C55xx
; Description: Initializes seed for 16 bit random number generation routine
; Useage: void rand16init(void)
;                                                              
; Copyright Texas instruments Inc, 2000
;****************************************************************
;-----------------------------------------------------------------------------
; Use memory mapped register mnemonics
;-----------------------------------------------------------------------------

			.mmregs

;-----------------------------------------------------------------------------
; Reserve space in DATA memory for seed 
;-----------------------------------------------------------------------------
	 		.bss rndseed,1 
 			.def rndseed
		
;-----------------------------------------------------------------------------
; Define constants used in the random number generation algorithm
;-----------------------------------------------------------------------------

RNDSEED 	.set  1     			; seed value (i.e. rndnum(1) = 21845)

;-----------------------------------------------------------------------------
; Initialize Random Number Generator -	Load the SEED value
;-----------------------------------------------------------------------------

			.def	_rand16init
			.text

_rand16init:

		MOV		#RNDSEED, *(rndseed)

		RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor

	
