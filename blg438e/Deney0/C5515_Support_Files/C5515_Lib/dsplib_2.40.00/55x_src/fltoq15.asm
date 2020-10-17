;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:	fltoq15
; Processor:   C55xx
; Description: convert IEEE floating point to Q15"
; Copyright Texas instruments Inc, 2000
; Note:
; 1. optimize the code by using AR0, AR1 directly
; 
; T2 registered is pushed and poped.
;  Zhengting He 10/25/2006
;****************************************************************

        .ARMS_off                     ;enable assembler for ARMS=0
        .CPL_on                       ;enable assembler for CPL=1
	.mmregs


;----------------------------------------------------------------
; Function definition:
;----------------------------------------------------------------

	.global	_fltoq15

_fltoq15:


;----------------------------------------------------------------
; Prologue: establish local frame, reset sign extension mode
;----------------------------------------------------------------
    PSH     T2
;   ZHENGTING ADDED TO PUSH T2 (SAVE)

	AADD	#-13, SP
	BCLR	SXMD

;----------------------------------------------------------------
; Process function arguments
;----------------------------------------------------------------

;	MOV	AR0, AR2
;	MOV	AR1, AR3
	||MOV	T0, AC1
	SUB	#1, AC1
	MOV	AC1, mmap(BRC0)

;----------------------------------------------------------------
; Store function constants
;----------------------------------------------------------------

	MOV	#127, *SP(#5)
	MOV	#15, *SP(#6)
	MOV	#32768 << #16, AC1
	MOV	HI(AC1 << #0), *SP(#7)
	NOT	AC1
	MOV	AC1, dbl(*SP(#0))
	MOV	#32768, *SP(#7)
	MOV	#1, *SP(#8)
	MOV	#32767, *SP(#9)
	MOV40	dbl(*AR0+), AC0
	
;----------------------------------------------------------------
; Convert each element of vector A, to Q15 format
; Pre-Load first vector element
;----------------------------------------------------------------

	||RPTB	end_loop-1

loop_start:

	AND	#32768 << #16, AC0, AC1
	MOV	HI(AC1 << #0), *SP(#11)
	MOV40	dbl(*SP(#0)), AC1
	AND	AC1, AC0
	BCC	zero, AC0 == 0
	AND	#32640 << #16, AC0, AC1
	MOV	*(#(12)) << #-7, AC1
	SUB	*SP(#5), AC1

;----------------------------------------------------------------
; If unbiased exponent is >= 0, then value is too large to
; represent in Q15 format
;----------------------------------------------------------------

	BCC	too_large, AC1 >= #0

;----------------------------------------------------------------
; If exponent (abs) exp > abs(min_exp) then value is too small
; to represent in Q15 format. (min_exp = -15, since 2^-15 is
; least significant bit of Q15 number
;----------------------------------------------------------------

	MOV	AC1 << #0, *SP(#3)
	ABS	AC1
	SUB	*SP(#6), AC1
	
	BCC	too_small, AC1 > #0

;----------------------------------------------------------------
; Shift floating point mantissa to keep only the most significant
; 15 bits. The implied 1 of the IEEE floating point format is ORed
; in as most significant bit.
;----------------------------------------------------------------

	MOV	*SP(#11), AC1
	SFTSC	AC0, #-7
	MOV	*(#(8)) << #-1, AC0
	AND	#65504, mmap(ST1)
	MOV	*SP(#3), T2
	OR	*SP(#7), AC0
	SFTS	AC0, T2
	XCC	check1, AC1 != #0
	NEG	AC0
check1:

P4_9:
	B	store_result

too_small:
	MOV	#2, *SP(#10)

zero:
	MOV	#0, AC0
	B	store_result

too_large:
	MOV	*SP(#11), AC1
	MOV	#1, *SP(#4)
	MOV	*SP(#9), AC0
	XCC	check2, AC1 > #0
	ADD	*SP(#8), AC0
check2:

store_result:
	MOV	AC0 << #0, *AR1+
	MOV40	dbl(*AR0+), AC0

end_loop:

;----------------------------------------------------------------
; Return to calling program. Set error conditions on return"
;----------------------------------------------------------------"

Epilogue:

	MOV	*SP(#4), T0
	OR	*SP(#10), T0

	AADD	#13, SP

	POP     T2
; ZHENGTING ADDED TO RESTORE T2

	BSET	SXMD
	RET
	


