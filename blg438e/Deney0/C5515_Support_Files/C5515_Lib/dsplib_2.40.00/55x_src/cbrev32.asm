;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;*********************************************************************
; Function:    cbrev32
; Processor:   C55xx
; Description: This function performs 32-bit bit-reversal of complex 
;			   data array x.
;              If x==y, in-place bit reversal is performed.
; Usage:    void cbrev32 (DATA *x, DATA *y, ushort n)
; Copyright Texas instruments Inc, 2002
;****************************************************************

		.mmregs  
		.cpl_on   

        .global _cbrev32   

_cbrev32:

;//-----------------------------------------------------------------------------
;// Context Save
;//-----------------------------------------------------------------------------

	PSH	mmap(ST2_55)		; preserve ST2 register  

;//-----------------------------------------------------------------------------
;// Initialize
;//-----------------------------------------------------------------------------

	BSET	AR1LC			; circular addressing for AR1
	.arms_off
	BCLR	ARMS			; reset ARMS bit

	MOV	T0, T1				; n in DR1
	SFTL T1, #1				; 2*n
	SFTL T1, #1				; 4*n
	MOV	mmap(T1), BK03		; circular buffer size is 4*n 
	MOV	mmap(AR1), BSA01	; circular buffer offset      
 
 	MOV	T0, T1				; n in DR1
	SUB	#1, T1
	MOV	mmap(T1), BRC0		; BRC0 = n - 1

	MOV	XAR1, AC0

	MOV	XAR0, AC1			; 
	MOV	#0, AR1				; output pointer (circular)
	SFTL T0,#1

	SUB	AC1, AC0		; compare input and output pointers 
	BCC	off_place, AC0 != #0	; if x<>y, do off-place bit reversal

;//-----------------------------------------------------------------------------
;// In-place bit reversal
;//-----------------------------------------------------------------------------
in_place: 

	BSET	AR0LC			; circular addressing for AR0
	MOV	#0, AR0

	RPTBLOCAL	loop1-1 
	MOV	dbl(*AR0+), AC0
	MOV dbl(*AR0-), AC3      
	AMOV	AR1, T1			; should be in parallel but CCS1.00b crashes
	MOV	dbl(*AR1+), AC1
	MOV dbl(*AR1-), AC2
	ASUB	AR0, T1			; should be in parallel but CCS1.00b crashes
 	XCCPART	check1, T1>=#0	; swap only if AR3 < AR2 
	||MOV	AC1, dbl(*AR0+)	; otherwise they are swapped already
check1:	
	XCCPART check2, T1>=#0
	||MOV AC2,dbl(*AR0+)
check2:
	XCCPART	check3, T1>=#0
	||MOV	AC0, dbl(*AR1+)
check3:
	XCCPART check4, T1>=#0
	|| MOV AC3, dbl(*(AR1+T0B))
check4:
	MAR *+AR1(-2)
loop1:

	B	end  
	
;//-----------------------------------------------------------------------------
;// Off-place bit reversal
;//-----------------------------------------------------------------------------
off_place:  						
 
	RPTBLOCAL	loop2-1            
	MOV	dbl(*AR0+), AC0
	MOV dbl(*AR0+), AC1
	MOV AC0, dbl(*AR1+)
	MOV	AC1, dbl(*(AR1+T0B))  
	MAR *+AR1(-2)
loop2:

;//-----------------------------------------------------------------------------
;// Context Restore
;//-----------------------------------------------------------------------------
end:
    BSET	ARMS			; restore C environment
	POP	mmap(ST2_55)		; restore ST2 register

	RET				; return   

	.end     


