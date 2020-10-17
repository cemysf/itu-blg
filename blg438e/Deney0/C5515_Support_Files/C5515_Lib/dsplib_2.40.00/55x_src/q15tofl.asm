;***********************************************************
; Version 2.40.00                                           
;***********************************************************
;  Function:	q15tofl
;  Description: converts Q15 to IEEE floating point
;
;  Copyright Texas instruments Inc, 2000
;****************************************************************

        .ARMS_off                     ;enable assembler for ARMS=0
        .CPL_on                       ;enable assembler for CPL=1
	.mmregs


;----------------------------------------------------------------
; Function definition:
;----------------------------------------------------------------

	.global	_q15tofl

_q15tofl:


;----------------------------------------------------------------
; Prologue: establish local frame, reset sign extension mode
;----------------------------------------------------------------

	AADD	#-7, SP
	BCLR	SATD
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

	MOV	#127, *SP(#4)
	MOV	#32768, *SP(#5)
	MOV	#1, *SP(#6)

	MOV	#16383, *SP(#0)
	MOV	#65535, *SP(#1)
	
	BSET	SXMD	
	MOV	*AR0+ << #16, AC0

;----------------------------------------------------------------
; Convert each element of vector A, to Q15 format
; Pre-Load first vector element
;----------------------------------------------------------------
	
	||RPTB	end_loop

loop_start:
	BCC 	zero, AC0 == #0
	CMP	*(#(9))== #32767, TC2
	AND	#32768 << #16, AC0, AC1
	BCC	not_q_one, !TC2 
	MOV	#0 << #16, AC0
not_q_one:
	ABS	AC0

;----------------------------------------------------------------
; Shift right by one, since exp and norm never count shift into
; upper most bit (bit 31)
;----------------------------------------------------------------

	SFTSC	AC0, #-1
	EXP	AC0, T3
	MOV	HI(AC1 << #0), *SP(#2)
	SFTS	AC0, T3
	MOV	mmap(T3), AC1
	NEG	AC1
	ADD	*SP(#4), AC1
	MOV	AC1 << #0, *SP(#3)

;----------------------------------------------------------------
; Remove upper most bit as this becomes an implicit 1
; 2^exp * (1.f) where f is mantissa
;----------------------------------------------------------------

	MOV40	dbl(*SP(#0)), AC1
	AND	AC1, AC0
;	SFTSC	AC0, #-7
	MOV	*SP(#3) << #7, AC1
	OR	*SP(#2), AC1
	SFTSC	AC0, #-7
	MOV	*(#(11)) << #16, AC1
	OR	AC1, AC0

zero:
store_result:
	MOV	AC0, dbl(*AR1+)
	MOV	*AR0+ << #16, AC0

end_loop:

;----------------------------------------------------------------
; Return to calling program.
;----------------------------------------------------------------

Epilogue:
	
	MOV	#0, T0
	
	XCCPART	check, overflow(AC0)
	||MOV	#1, T0

	AADD	#7, SP
check:

	BSET	SXMD	

	RET	



