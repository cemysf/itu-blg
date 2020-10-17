;***********************************************************
; Version 2.40.00                                           
;***********************************************************
;  Function:	log_10
;  Description: Calculate log base 10 of 16-bit Q15 number
;
;  Copyright Texas instruments Inc, 2000
;********************************************************************************

	.mmregs		; assign Memory-Mapped Register names as global symbols
	.def		_log_10

	.asg    #04000h, CST_4000
	.asg    #0DC56h, LB6
	.asg    #54adh, LB5
	.asg    #9e8ah, LB4
	.asg    #50d5h, LB3
	.asg    #0c056h, LB2
	.asg    #3ffdh, LB1
	.asg    #062dh, LB0
	.asg    #1h, CST_1                        
	.asg    #58B9h, CST_ln2

	.text    		; begin assembling into .text section
	
_log_10:            
    PSH	mmap(ST1_55)
	AADD	#-15, SP
	NOP
;initialization for Logarithm calculation  

	MOV	XSP, XAR2
	MOV	CST_4000, *AR2+
	MOV	LB6, *AR2+
	MOV	LB5, *AR2+
	MOV	LB4, *AR2+
	MOV	LB3, *AR2+
	MOV	LB2, *AR2+
	MOV	LB1, *AR2+
	MOV	LB0, *AR2+
	MOV	CST_1, *AR2+
	MOV	CST_ln2, *AR2

	MOV	T0, AC0
	SUB	#1, AC0
	MOV	AC0, mmap(BRC0)

	RPTB	loop1-1
**************
* Normalize x
**************
    MOV	SP, AR2
	MOV	*AR0+ << #16, AC0		;A = x << 16
	EXP	AC0, T0				;T = number of leading bits
	BCLR	FRCT
	SFTS	AC0, T0, AC1
    
***************************
* Polynomial approximation 
***************************
   
	SFTS	AC1, #-15, AC0		;A <- 2*M
	SUB	*AR2+ << #1, AC0		;A <- (2*M-1) Q15

	MOV	AC0, T1			        ;U <- (2*M-1) Q15 (between 0.0 and 1.0)

	MOV	*AR2+ << #16, AC0		;B6 
	MOV	*AR2+ << #16, AC1		;B5 load [(Q18)<<16]=Q34

	
	MOV	*AR2+ << #16, AC1		;B4 load
	||MACR	AC0, T1, AC1, AC0   ;A(32-16) <- B6*U + B5
						        ;Q34 + Q18 << 16 = Q34
	
	MOV	*AR2+ << #16, AC1		;B3 load
	||MACR	AC0, T1, AC1, AC0	;A <- (B6*U + B5)*U + B4
						        ;Q33 + Q17 << 16 = Q33

	MOV	*AR2+ << #16, AC1		;B2 load
	||MACR	AC0, T1, AC1, AC0	;A <- ((B6*U+B5)*U+B4)*U+B3
						        ;Q32 + Q16 << 16 = Q32
	
	MOV	*AR2+ << #16, AC1		;B1 load
	||MACR	AC0, T1, AC1, AC0	;A <- (((B6*U+B5)*U+B4)*U+B3)*U+B2
						        ;Q31 + Q15 << 16 = Q31

	MOV	*AR2 << #16, AC1		;B0 load
	||MACR	AC0, T1, AC1, AC0	;A <- ((((B6*U+B5)*U+B4)*U+B3)*U+B2)*U+B1
						        ;Q30 + Q14 << 16 = Q30

	SFTSC	AC0, #1
	MPY	T1, AC0
	ADD	*AR2+, AC0		; A <- (((((B6*U + B5)*U + B4)*U + B3)*U + B2)*U
					    ; + B1)*U + B0
					    ;Q30 + Q30 = Q30

*******************
* Process exponent
*******************
	NEG	T0, AC1			;AC1 <- number of leading bits
	SUB	*AR2+, AC1		;AC1 <- P-1
	MOV	AC1, T0
	SFTS	AC0, #-15
	MPYM	*AR2, T0, AC1			;AC1 <- ln2 * (P-1)

*************************
* Add both contributions
*************************

	ADD	AC1, AC0			; AC0 = <- f(2*M(x)-1) + (P(x)-1)*ln(2)

	AND	#7FFFh, AC0, AC1		;store low word of AC0

	MOV	#03797h, T1
	BSET	FRCT

	||SFTSC	AC0, #1				;shift for 17 mpy
	MPY	T1, AC0
	SFTSC	AC0, #-1			;Hi word in AC0

	SFTSC	AC1, #16			;process low word
	MPY	T1, AC1
	SFTSC	AC1, #-16			;Lo word in AC1

	ADD	AC1, AC0			;add words together
	MOV	AC0, dbl(*AR1+)
endlog	;BCLR	FRCT

loop1:

************************
* Return overflow flag
************************

	AADD	#15, SP
	POP	mmap(ST1_55)
	
	MOV	#0, T0
	XCC	check, overflow(AC0)
	MOV	#1, T0
check:

	RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
	
