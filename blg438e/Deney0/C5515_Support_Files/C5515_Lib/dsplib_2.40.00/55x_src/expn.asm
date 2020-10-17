;***********************************************************
; Version 2.40.00                                           
;***********************************************************
;  Function:	expn
;  Description: exponent vector evaluation via polynomial approximation
;
;  Copyright Texas instruments Inc, 2000
;
;  History
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;   Zhengting He - 10/25/2006
;********************************************************************************

	.mmregs

; Table containing the coefficients for the polynomial

	.data    
expn_coeffs:			; hex values in q4.12

	.word	0x0039	;0.0139		(coef for x^5 = c5)
	.word	0x008f	;0.0348		(coef for x^4 = c4)
	.word	0x02ba	;0.1705		(coef for x^3 = c3)
	.word	0x07fc	;0.4990		(coef for x^2 = c2)
	.word	0x1000	;1.0001		(coef for x^1 = c1)
	.word	0x1000	;1.0000		(coef for x^0 = c0)


;****************************************************************
	.global	_expn
	.text

; Get arguments and set modes
; ---------------------------

_expn:
	BSET	FRCT			;set FRCT on
	BSET	SATD			
	BSET	SXMD	

	SUB	#1, T0			;b = n-1
	MOV	T0, mmap(BRC0)		;BRC = n-1

	RPTB	loop 			;repeat n times

; Start polynomial evaluation
; ---------------------------

; this should be moved out from the loop and rewound
; back to beginning by t1 register. It is not possible yet with beta tools.

	AMAR	*(#expn_coeffs), XAR4	;pointer to coeff table

	MOV	*AR0+, T0		;t = x(sign-extended)
	MOV	dbl(*AR4+), pair(HI(AC0))

	MOV	*AR4+ << #16, AC1
	||MACR	AC0, T0, AC1, AC0	;a = ah*t + b
					;  = c5*x + c4
					;bh = c3  point to c2

	MOV	*AR4+ << #16, AC1	
	||MACR	AC0, T0, AC1, AC0	;a = ah*t + b
					;  = (c5*x + c4)*x + c3
					;  =  c5*x^2 + c4*x + c3
					; bh = c2	point to c1

	MOV	*AR4+ << #16, AC1	
	||MACR	AC0, T0, AC1, AC0	;a = ah*t + b
					;   = (c5*x^2+c4*x+c3)*x + c2
					;   = c5*x^3+c4*x^2+c3*x + c2
					; bh = c1	point to c0

	MOV	*AR4+ << #16, AC1	
	||MACR	AC0, T0, AC1, AC0	;a = ah*t + b
					;   = (c5*x^3+c4*x^2+c3*x + c2)*x + c1
					;   = c5*x^4+c4*x^3+c3*x^2+c2*x +c1
					; bh = c0	point to c(-1)

	MAC	AC0, T0, AC1, AC0	; a = ah*t + b				
					;   = (c5*x^4+c4*x^3+c3*x^2 + c2*x+c1)*x + c0
					;   = c5*x^5+c4*x^4+c3*x^3+c2*x^2 +c1*x + c0


	MOV	HI(AC0), *AR1+		;store q4.12 output
loop:

; Return overflow flag
; --------------------
; bug: original code put return value in AC0
; fix: put to T0
	MOV	#0, T0
	XCC	check, overflow(AC0)
	MOV	#1, T0
check:

	BCLR	FRCT
	BCLR	SATD

	RET
;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor	
