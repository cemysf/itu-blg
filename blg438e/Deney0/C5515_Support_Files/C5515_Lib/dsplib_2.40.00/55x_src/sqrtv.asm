;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;***************************************************************
; Function :	sqrtv
; Processor:	C55x
; Description:   Square root of a 16-bit number
;		C-callable
; Copyright Texas instruments Inc, 2000
; History:
;		- Li Yuan 01/30/2002
; 		  fixed the bug where NX should be stored in register T0 instead of AR2.
; 		  fixed code to work in large block memory by correct XAR loading.
;       
;****************************************************************

	.CPL_on
	.mmregs 
	.def	_sqrt_16
_sqrt_16:


; Set Number Of Iterations of Sqrt Algorithm (N=5)
;------------------------------------------------
	MOV	#4, BRC1	;inner loop counter set to no: of iterations-1
		

; assign registers and set status bits
;-------------------------------------
	.asg AR4, AR_TBL
	.asg XAR4, XAR_TBL
	.asg AR0, AR_X		;input vector
	.asg AR1, AR_R		;output vector
	.asg AR5, AR_HEX5E00
	.asg BRC0, AR_N		;outer block repeat counter


	.asg 0, SP_ONE
	.asg 1, SP_XNORM
	
	PSHBOTH	XAR5
	PSHBOTH	XAR6
	PSH        T2, T3

	AADD	#-2, SP

; N=N-1
;------
				
;	SUB	#1, AR2, T2	;no: of inputs-1
	SUB	#1, T0, T2	;no: of inputs-1
	MOV	T2, AR_N	;Block repeat counter set to no: of inputs-1
	
; Initialize constants
;---------------------
	  				 	
	MOV	#05E00h, AR_HEX5E00
;	MOV	#SqrtTable, AR6   	;initialize square root lookup table
	AMOV	#SqrtTable, XAR6   	;initialize square root lookup table
      
	RPTB	loop1-1 		
	MOV	#01h, *sp(SP_ONE) 	; value to round the input

; Get next input value in array, x
; and round input value by adding 0x8000
;----------------------------------------------------------------

	MOV	*AR_X+ << #16, AC0	;load the input to AC0, shift left by 16 bits
	ADD	*sp(SP_ONE)<<#15, AC0	;round the input 
	 
; Normalize input value
;----------------------
	
	MANT	AC0, AC0
	::NEXP	AC0, T3		;normalize the input

	NEG	T3		;since the previous instruction gives the 
	;NOP			;negative of the exponent, negate it
	

; Use lookup table to find SQRT of exponent
; lookup table index == exponent
;------------------------------------------
;	||MOV	AR6, AC1			;AC1 points to sqrt table
	MOV	XAR6, AC1			;AC1 points to sqrt table
	ADD	T3, AC1   			;add	the exponent 				
	MOV	AC1, XAR_TBL      		;AR_TBL=exp+SqrtTable

	MOV	AR_HEX5E00, *AR_R    		; Initial value for Ynorm
;	||MOV	AR_HEX5E00, *AR_R    		; Initial value for Ynorm
	MOV	HI(AC0), *sp(SP_XNORM)   


; Load normalized estimate of square root
; Ynorm(new) = Ynorm(old) - (Ynorm(old)^2 - Xnorm)/2
;---------------------------------------------------
        
	RPTBLOCAL	loop2-1			; do 5 iterations
	
	MOV	*sp(SP_XNORM) << #15, AC0   
	SQSM	T3 = *AR_R, AC0 
	    
	ADD	*AR_R <<#16, AC0         
	MOV	HI(AC0), *AR_R         
	   
loop2:					;inner loop ends here

; Multiply sqrt(Ynorm) * sqrt(normalized_exponent)
; And round the result
;-------------------------------------------------

	MPYM	*AR_R, *AR_TBL, AC0  
	ADD	*sp(SP_ONE)<< #15, AC0   
	MOV	HI(AC0<<#1), *AR_R+        	; Store result in AR_R

loop1: 					;outer loop ends here
	
;Return overflow flag
;---------------------
    .if  $isdefed("SI_BUGS")
	MOV	#0, T0
	XCC	check1, overflow(AC0)
    .else
	MOV	#0, T0
	||XCCPART	check1, overflow(AC0)
	.endif
	MOV	#1, T0
check1:					

; Pop off registers and restore c environment
;--------------------------------------------

	AADD	#2, SP
      POP        T2, T3
	POPBOTH	XAR6
	POPBOTH	XAR5
	
	
;Return to calling function
;---------------------------	
	RET
	

; Square root lookup table
;-------------------------------------------------
; Ytable = 1/sqrt(2^n) values:
;
   	.data
	.def SqrtTable
SqrtTable:			
	.word	7FFFh		; 1/sqrt(2^0)  = 0.99997 
	.word	5A82h		; 1/sqrt(2^1)  = 0.70711 
	.word	4000h		; 1/sqrt(2^2)  = 0.50000 
	.word	2D41h		; 1/sqrt(2^3)  = 0.35355 
	.word	2000h		; 1/sqrt(2^4)  = 0.25000 
	.word	16A1h		; 1/sqrt(2^5)  = 0.17678
	.word	1000h		; 1/sqrt(2^6)  = 0.12500 
	.word	0B50h		; 1/sqrt(2^7)  = 0.08839
	.word	0800h		; 1/sqrt(2^8)  = 0.06250 
	.word	05A8h		; 1/sqrt(2^9)  = 0.04419 
	.word	0400h		; 1/sqrt(2^10) = 0.03125 
	.word	02D4h		; 1/sqrt(2^11) = 0.02210 
	.word	0200h		; 1/sqrt(2^12) = 0.01563 
	.word	016Ah		; 1/sqrt(2^13) = 0.01105 
	.word	0100h		; 1/sqrt(2^14) = 0.00781 
	.word	0000h	

