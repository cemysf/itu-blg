;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    sine
; Processor:   C55x
; Description: Sine vector generation using polynomial evaluation.
;              C-callable
; History:	   07/07/2003 - d. elam fixed bug in q4.12 -> q1.15 conversion
; Copyright Texas instruments Inc, 1999
;****************************************************************

	 .CPL_on
 	.mmregs
	.asg	ar0, ar_x			;input vector
	.asg	ar1, ar_r			;output vector	
	.asg	ar5, ar_coeff		;pointer to coefficient table
	.asg	ar6, ar_coefftable	

;****************************************************************
	.def	_sine
	.text

_sine

      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  

; Set status registers and get arguments 
; --------------------------------------

	BSET	CPL	      ;set CPL
	BSET	FRCT		;set FRCT
	BSET	ACOV0		;set OVM
	BSET	SXMD		;set SXMD
	BSET 	SATD
	
	BCLR 	M40			;reset M40

	PSH   T2,T3
	PSHBOTH	XAR5		
	PSHBOTH	XAR6

	SUB	#1, T0, T2	;no: of inputes(AR2) - 1
	MOV	T2, BRC0	;block repeat counter set to inputs -1
    nop
	AMOV	#coeffs, XAR6	;pointer to coefficient table
	MOV XAR6, XAR5
	RPTB	loop-1

; If angle in 2nd and 4th quadrant then negate the result before removing
; sign bit
; -----------------------------------------------------------------------

	BTST	#14, *ar_x, TC1		;TC1=bit 14 of input

	MOV	*ar_x, AC0		;1st input(sign extended) in accumulator
	
	||MOV	ar_coefftable, ar_coeff	;initialize ar_coeff to beginning of table

        XCC     check1, TC1             ;if bit 14 is 1, negate and it in AC0
	NEG	AC0			;AC0 = -x
check1:
	AND 	#7FFFh, AC0		;remove sign bit from -x

; Start polynomial evaluation
; ---------------------------

	MOV	AC0, T3			;T3 = x
	||MOV	*ar_coeff+ <<#16, AC0	;AC0(high bits) = c5
	MOV	*ar_coeff+ <<#16, AC3	;AC3(high bits) = c4

	||BTST	#15, *ar_x+, TC1

	MOV	*ar_coeff+ <<#16, AC3
	||MACR AC0, T3, AC3, AC0

	MOV	*ar_coeff+ <<#16, AC3
	||MACR AC0, T3, AC3, AC0

	MOV	*ar_coeff+ <<#16, AC3
	||MACR AC0, T3, AC3, AC0

	MOV	*ar_coeff+ <<#16, AC3
	||MACR AC0, T3, AC3, AC0

	MACR AC0, T3, AC3, AC0

;changing the result from q4.12 to q1.15 format
; ---------------------------------------------		
        SFTS    AC0, #3  
			

; If angle in 3rd and 4th quadrant (negative angle), negate the result
; ---------------------------------------------------------------------

        XCC     check2, TC1
	NEG	AC0	
check2:
	MOV	HI(AC0), *ar_r+

loop:

; Return overflow flag
; --------------------

    .if  $isdefed("SI_BUGS")
	MOV	#0, T0	
	XCC  check3, overflow(AC0)	;clears ACOV0
	.else
	MOV	#0, T0	
	||XCCPART  check3, overflow(AC0)	;clears ACOV0
	.endif
	MOV	#1, T0				;overflow occured

; POP registers off stack and restore c environment
;--------------------------------------------------
check3:
	POPBOTH	XAR6
	POPBOTH	XAR5
	POP         T2,T3

	POP	mmap(ST2_55)
	POP	mmap(ST1_55)
      POP	mmap(ST0_55)
      
	
	RET

; Coefficient table for polynomial evaluation

	.data				;hex values in q4.12 format
coeffs:
	.word	0x1CCE			;1.800293	(coeff for x^5 = c5)
	.word	0x08B7			;0.5446778 	(coeff for x^4 = c4)
	.word	0xAACC			;-5.325196	(coeff for x^3 = c3)
	.word	0x0053			;0.02026367	(coeff for x^2 = c2)
	.word	0x3240			;3.140625	(coeff for x^1 = c1)
	.word	0x0000			;0		(coeff for x^0 = 0)
