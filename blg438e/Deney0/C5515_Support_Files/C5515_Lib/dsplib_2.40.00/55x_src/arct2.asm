;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;****************************************************************
; Function:    atan2_16
; Processor:   C55xx
; Description: arctangent 2 implementation
; Usage:    short atan2( DATA *x2, DATA *x1, DATA *r, int *NX)
;   r[i]=arctangent(x1[i]/x2[i]) Q15 format
;   NX=number of elements in x1,x2,r
;   x1,x2 input
;   r result
;   return 0 if ok; 1 if error
;   
;  Copyright Texas instruments Inc, 2000
;****************************************************************
	.mmregs
	.cpl_on
	.arms_on
	;.model call=c55_std
;	.model mem=small

	.def	_atan2_16
;FRCT	.set	6			; FRCT bit position in ST1 (phase3)
;SATD	.set	9			; SATD bit position in ST1 (phase3)


_atan2_16:
; LOCAL VARIABLE
SP_NUM		.SET	0
;* AR0   assigned to _x
;* AR1   assigned to _y
;* AR2   assigned to _r
;* T0   assigned to _nx
	
	AADD	#-1, SP			;space for local variable
	SUB	#1, T0			;nx - 1
	MOV	T0, BRC0		;repeat nx times
	BSET	FRCT			;fractional mode set
	BSET	SATD			;saturation mode on
	RPTB	loop1-1
	MOV	*AR0 << #16, AC0
	||MOV	*AR1 << #16, AC1
	ABS	AC0
	MOV	HI(AC0), *SP(#SP_NUM)
	||ABS	AC1
	MAX	AC1, AC0
	BCC	XGTY, CARRY
	CALL	atan2
	||MANT	AC0, AC1
	::NEXP	AC0, T1
	SUB	#16384 << #16, AC0
	NEG	AC0
	||B	QUAD
XGTY
	MOV	HI(AC1), *SP(#SP_NUM)
	CALL	atan2
	||MANT	AC0, AC1
	::NEXP	AC0, T1

QUAD
	BTST	#15, *AR0+, TC1
    .if  $isdefed("SI_BUGS")
	XCC	check_1, TC1
    .else
	XCCPART	check_1, TC1
    .endif
	SUB	#32767 << #16, AC0
check_1:
    .if  $isdefed("SI_BUGS")
	XCC	check_2, TC1
    .else
	XCCPART	check_2, TC1
    .endif
	NEG	AC0
check_2:
	BTST	#15, *AR1+, TC1
    .if  $isdefed("SI_BUGS")
	XCC	check_3, TC1
    .else
	XCCPART	check_3, TC1
    .endif
	NEG	AC0
check_3:
	MOV	HI(AC0), *AR2+	

loop1:

	AADD	#1, SP
	BCLR	FRCT			;fractional mode reset
	BCLR	SATD			;saturation mode off
	MOV	#0, T0			;returned value
	||RET

;*************************************************


*****************************************************************************
; INPUT VALUE IN AC1,T1,SP_NUM
; RETURN AC1
; USE: AC0,AC1
; FRCT = 1
atan2:
	SFTS	AC1, #-1, AC2
	XOR	#1FFFh << #16, AC2
	||MOV	HI(AC1), T0

; COMPUTE 2^28/X
; Calculate Ym = 2*Ym - Ym^2*X
	.LOOP	2
; Ym: AC2_h ; X: T0
	MPY	T0, AC2, AC3
	SFTS	AC2, #-1, AC0
	MPY	AC2, AC3
	SUB	AC3, AC0
	SFTS	AC0, #2, AC2
	.ENDLOOP

; LAST ITERATION
	MPY	T0, AC2, AC3
	SFTS	AC0, #1
	MPY	AC2, AC3
	AMOV	#atancoeffs, XAR3
	SUB	AC3, AC0

	MPYM	*SP(#(SP_NUM + 1)), AC0, AC2
	SFTS	AC2, #3
	||NEG	T1
	SFTL	AC2, T1
	ADD	AC2, AC2

	SFTS	AC2, #-16
	||MOV	*AR3+ << #16, AC0
	MOV	AC2, T0
	||MOV	*AR3+ << #16, AC1
	MOV	*AR3+ << #16, AC1
	||MACR	AC0, T0, AC1, AC0
	MOV	*AR3+ << #16, AC1
	||MACR	AC0, T0, AC1, AC0
	MOV	*AR3+ << #16, AC1
	||MACR	AC0, T0, AC1, AC0
	MACR	AC0, T0, AC1, AC0
	MPYR	T0, AC0

	SFTS	AC0, #-1
	||RET

********************************************************************************

	.data    

atancoeffs:
	.word 0xfda8 ; C5 -0.009159*2*32767.999*x^5
	.word 0x118b ; C4 +0.068542*2*32767.999*x^4
	.word 0xde7c ; C3 -0.130908*2*32767.999*x^3    
	.word 0x00d9 ; C2 +0.003314*2*32767.999*x^2
	.word 0x5179 ; C1 +0.318253*2*32767.999*x^1
;	.word 0x0000 ; C0 0*x^0

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor


	

