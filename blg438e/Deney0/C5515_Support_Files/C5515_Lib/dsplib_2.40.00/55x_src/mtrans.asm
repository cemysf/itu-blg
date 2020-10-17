;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;****************************************************************
;  Function:	mtrans
;  Description: matrix multiply implementation
;  Usage: short mtrans(	DATA *x1,	AR0
;			short row1,	T0
;			short col1,	T1
;			DATA *r);	AR1
;
;  Copyright Texas instruments Inc, 2000
;****************************************************************
	.mmregs
	.text
	.def _mtrans
_mtrans:
	PSH	mmap(ST1_55)
	PSH	mmap(ST2_55)
					;XAR0 = x1
					;T0 = row1
					;T1 = col1
					;XAR1 = r
	
        MOV     T0,HI(AC0)

        .if  $isdefed("SI_BUGS")
	MPY	T1,AC0,AC1		;AC1 = row1*col1
        MOV	XAR1,XAR2		;XAR2 = r to ensure MDP
        .else
	MPY	T1,AC0,AC1		;AC1 = row1*col1
     || MOV	XAR1,XAR2		;XAR2 = r to ensure MDP
        .endif

	MOV	AR0,mmap(@BSA01)	;BSA01 = x1
	MOV	AR1,mmap(@BSA23)	;BSA23 = r
	MOV	AC1,mmap(@BK03)		;init block size
	MOV	#0,AR0			;AR0 = 0
	MOV	#0,AR2			;AR2 = 0
	BSET	AR0LC
	BSET	AR2LC
	SUB	#1,T1,T2
	MOV	T2,CSR			;inner loop CSR = col-1
	SUB	#1,T0,T2
	MOV	T2,BRC0			;outer loop BRC0 = row-1
	MOV	#0,T2
		
	
	RPTBLOCAL  loop			;for every row of x1
    	RPT	CSR			;  for every col of x1
	MOV	*AR0+,*(AR2+T0)
loop:   AMAR	*AR2+			;  next col of r	

	MOV	#0,T0			;return value TRUE
   	POP	mmap(ST2_55)
	POP	mmap(ST1_55)

	return

