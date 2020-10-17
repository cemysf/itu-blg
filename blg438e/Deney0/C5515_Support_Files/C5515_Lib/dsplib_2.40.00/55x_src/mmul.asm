;***********************************************************
; Version 2.40.00                                           
;***********************************************************
;  Function:	mmul
;  Description: matrix multiply implementation
;  Usage:   short mmul(	DATA *x1,	XAR0
;			short row1,	T0
;			short col1,	T1
;			DATA *x2,	XAR1
;			short row2,	XAR2
;			short col2,	XAR3
;			DATA *r);	XAR4
;
;  Copyright Texas instruments Inc, 2000
; History
; 2.10.1 - clear C54CM bit at the begining. Li Yuan 08/08/01
;                
;****************************************************************
	.mmregs
	.text
	.def _mmul
_mmul:
	PSH	mmap(ST1_55)
	PSH	mmap(ST2_55)				
	PSHBOTH	XAR5	
	PSHBOTH	XAR6				
					;XAR0 = x1
					;T0 = row1
					;T1 = col1
					;XAR1 = x2
					;XAR2 = row2
					;XAR3 = col2
					;XAR4 = r				          

; clear 54CM
	BCLR	C54CM			;clear C54 compatible mode
;---------------------------------------------------					
; Verify that the dimensions of the input matrices are legal, i.e. input1 
; row size = input2 column size; else return input1 as output
;---------------------------------------------------					
	MOV	T0, T2			;T2 = row1
	MOV	T1, T0			;T0 = col1
	SUB	AR2, T0			;T0 = col1 - row2
	BCC	mmulend, T0!=#0		;return value FALSE

; Setup temps
	BSET	FRCT			;fractional mode set
	MOV	AR3, T0			;T0 = col2
					;T1 = col1
					;T2 = row1

; test if usage of Dual-MAC or Single-MAC
	SUB	#3, T1, T3
	BCC	mmul_single_mac, T3<#0
	SUB	#4, T2, T3
	BCC	mmul_single_mac, T3<#0

;---------------------------------------------------					
; Dual-MAC implementation for large matrices
; col1>=3 && row1>=4
;---------------------------------------------------
mmul_dual_mac:
					;---- pointers ----
	MOV	XAR0, XAR3		;XAR0 = &x1(1,1) (reload reg for XAR2, XAR3)
	MOV	XAR0, XAR2		;XAR2 = &x1(1,1)
	AADD	T1, AR3			;XAR3 = &x1(2,1)
	MOV	XAR1, XCDP		;XCDP = &x2(1,1)
	MOV	XAR4, XAR5		;XAR5 = &r(1,1)
	MOV	XAR1, XAR4		;XAR4 = &x2(1,1) (reload reg for XCDP)
	MOV	XAR5, XAR6		;XAR6 = &r(1,1) (reload reg for XAR5)

					;---- loop counters ----
	SUB	#1, T0, T3		;
	MOV	T3, BRC0		;outer loop count: BRC0 = col2-1
	MOV	mmap(T2) << #-1, AC2	;
	SUB	#1, AC2			;
	MOV	mmap(AC2L), BRC1	;mid loop count: BRS1 = (row1>>1)-1
	BTST	#0, mmap(T2), TC1	;if(row1==even) TC0=0 else TC0=1
	SUB	#3, T1, T3		;
	MOV	T3, CSR			;inner loop count: CSR = col1-3

; Perform Matrix Multiply

	RPTB	loop1-1

		;----- if(row1==odd) do first row of x using single MAC, then go to Dual MAC
	BCC	L1, !TC1
	MPYM	*AR2+, *(CDP+T0), AC0
	||RPT	CSR			;||
	MACM	*AR2+, *(CDP+T0), AC0
	MACMR	*AR2+, *(CDP+T0), AC0
	MOV	HI(AC0), *(AR5+T0)	;store to r
	||AADD	T1, AR3			;|| AR3 points to next row of x1
	MOV	AR4, CDP		;CDP points to same column of x2

L1:		;----- do an even number of rows of x using Dual MAC 
	RPTBLOCAL	loop2-1
	MPY	*AR2+, *(CDP+T0), AC0	;first iteration
	::MPY	*AR3+, *(CDP+T0), AC1	;
	||RPT	CSR			;||
	MAC	*AR2+, *(CDP+T0), AC0
	::MAC	*AR3+, *(CDP+T0), AC1
	MACR	*AR2+, *(CDP+T0), AC0	;last iteration
	::MACR	*AR3+, *(CDP+T0), AC1
	MOV	HI(AC0), *(AR5+T0)	;store to r
	||AADD	T1, AR2			;|| AR2 points to next row of x1
	MOV	HI(AC1), *(AR5+T0)	;store to r
	||AADD	T1, AR3			;|| AR3 points to next row of x1
	MOV	AR4, CDP		;CDP points to same column of x2

loop2:

	AMAR	*AR4+			;AR4 points to next column of x2
	||MOV	AR0, AR2		;|| AR2 points to x1(1,1)
	AMAR	*CDP+			;CDP points to next column of x2
	||MOV	AR0, AR3		;||
	AMAR	*AR6+			;AR6 points to next column of r
	AADD	T1, AR3			;AR3 points to x1(2,1)					
	||MOV	AR6, AR5		;|| AR5 points to next column of r

loop1:

	B	mmulret

;---------------------------------------------------					
; Single-MAC implementation for small matrices
; col1<3 || row1<4
;---------------------------------------------------
mmul_single_mac:
					;---- pointers ----
	MOV	XAR0, XAR2		;XAR2 = &x1(1,1)  XAR0 = &x1(1,1) for reload
	MOV	XAR1, XAR3		;XAR3 = &x2(1,1)  XAR1 = &x2(1,1) for reload
	MOV	XAR4, XAR5		;XAR5 = &r(1,1)   XAR4 = &r(1,1) for reload

					;---- loop counters ----
	SUB	#1, T0, T3		;
	MOV	T3, BRC0		;outer loop count: BRC0 = col2-1
	SUB	#1, T2, T3		;
	MOV	T3, BRC1		;mid loop count: BRC1 = row1-1
	SUB	#1, T1, T3		;
	MOV	T3, CSR			;inner loop count: CSR = col1-1

; Perform Matrix Multiply

	RPTBLOCAL	loop3-1

	RPTBLOCAL	loop4-1
	MOV	#0, AC0			;clear AC0
	||RPT	CSR			;
	MACM	*AR2+, *(AR3+T0), AC0
	ROUND	AC0			;round result
	MOV	HI(AC0), *(AR5+T0)	;store result to r
	||MOV	AR1, AR3		;AR3 points back to beginning of same column of x2

loop4:

	AMAR	*AR1+			;AR1 points to next column of x2
	||MOV	AR0, AR2		;AR2 points to x1(1,1)
	AMAR	*AR4+			;AR4 points to next column of r
	||MOV	AR1, AR3		;AR3 points to next column of x2
	MOV	AR4, AR5		;AR5 points to next column of r					

loop3:

mmulret:	
	MOV	#0, T0			;return value TRUE

mmulend:
	POPBOTH	XAR6
	POPBOTH	XAR5
	POP	mmap(ST2_55)
	POP	mmap(ST1_55)

	RET

