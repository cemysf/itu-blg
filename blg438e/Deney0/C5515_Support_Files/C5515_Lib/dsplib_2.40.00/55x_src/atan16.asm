;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    atan16
; Processor:   C55xx
; Description: Arctangent implementation
; Usage:   short atan16( DATA *x, DATA *r, int NX)
;  NX : number of element of x and r
;  r[i]=atan(x[i]) with x and r in Q15 format
;  return 0
;
;  Copyright Texas instruments Inc, 2000
;****************************************************************
	.mmregs
	.cpl_on
	.arms_on
	;.model call=c55_std
	;.model mem=small

	.def	_atan16
;FRCT	.set	6			; FRCT bit position in ST1 (phase3)

_atan16:
;* AR0   assigned to _x
;* AR1   assigned to _r
;* T0   assigned to _nx
	SUB	#1, T0			;nx-1
	MOV	T0, BRC0		;repeat nx times
	AMOV	#atancoeffs, XAR2	;pointer on coeff
	BSET	FRCT			;fractional mode
	RPTBLOCAL	loop1-1
	MOV	*AR2+ << #16, AC0	;C5
	||MOV	*AR0+, T0		;input sample
	MOV	*AR2+ << #16, AC1	;C3
	||MPYR	T0, AC0
	MOV	*AR2+ << #16, AC1	;C1
	||MACR	AC0, T0, AC1, AC0
	MPYR	T0, AC0
	||ASUB	#3, AR2			;pointer on coeff
	MACR	AC0, T0, AC1, AC0
	MPYR	T0, AC0
	MOV	HI(AC0), *AR1+		;save result

loop1:

	BCLR	FRCT			;return to standard C
	
	MOV	#0, T0			;return OK value (no possible error)
	
	||RET

;*************************************************

	.data    

atancoeffs:		; coefficients obtained from polyfit function of matlab
				; for 0 <= x <= 1 ; C0+C1*x+C2*x*x+...
	.word 2596	; C5 Q15
;	.word 0     ; C4
	.word -9464 ; C3
;	.word 0     ; C2
	.word 32617 ; C1 
;	.word 0     ; C0

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
