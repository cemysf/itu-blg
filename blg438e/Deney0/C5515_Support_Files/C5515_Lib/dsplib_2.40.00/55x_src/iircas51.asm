;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:	 iircas51
; Processor:   C55xx
; Description:  cascaded IIR direct form II using 5-coefs per biquad
;
; Copyright Texas instruments Inc, 2000
;
; History
; 2.40 Cleared XDP instead of DP register
;      Zhengting He - 10/25/2006
;*****************************************************************************
;
;
;	IIR Biquad Structure
;
;                          
;  x(n) ------.-----x-->+ -------> + -----.---------> y(n)
;             |    b0   |\        /|      |       
;           [z-1]       | |      | |    [z-1]     
;             |         | |      | |      |       
;             v         | |      | |      v       
;           x(n-1)--x---| |      | |--x-d(n-1)           
;             |    b1     |      |  -a1   |       
;             |           |      |        |       
;           [z-1]         |      |      [z-1]     
;             |           |      |        |       
;             v           |      |        v       
;           x(n-2)--x-----|      |---x--d(n-2)    
;                  b2              -a2            
;            
;                 "FF"             "FB"
;
;
;        "FB" = Feedback Terms
;        "FF" = Feedforward Terms
;
;
; Algorithm (for single biquad)
; -----------------------------
;  y(n)= b0*x(n) + b1*x(n-1) + b2*x(n-2) - a1*y(n-1) - a2*y(n-2)
; 
;
; Function Call
; -------------
;
;  short oflag = iircas51(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nbiq,
;                        ushort nx)
;
;   where:
; x[nx]: PASSED in XAR0.
;        Pointer to input vector of nx real elements.  
;        x(0) is the first input, 
;        while x(nx-1) is the last input.
;        
; h[5*nbiq]: PASSED in XAR1.
;        Pointer to filter coefficient vector with the following format:
;        H = b01 b11 b21 a11 a21 ....b0i b1i b2i a1i a2i
;         where i is the biquad index.
;         (i.e. a21: is the a2 coefficient of biquad 1). 
;         Pole (recursive) coefficients = a. 
;         Zero (non-recursive) coefficients = b
;
;        This array must be located in internal memory if it is 
;        accessed by the C55xx coefficient bus.
;
; r[nx]: PASSED in XAR2.
;        Pointer to output vector of nx real elements.  
;        In-place computation (r = x) is allowed.  r(0) is the first 
;        output, while r(nx-1) is the last output.
;
; dbuffer[4*nbiq]: PASSED in XAR3.
;        Pointer to delay buffer of length 4*nbiq.  See figure below for  
;        organization. In the case of multiple-buffering schemes, this 
;        array should be initialized to 0 for the first filter block only. 
;        Between consecutive blocks, the delay buffer preserves the 
;        previous elements needed.
;
;
; nbiq:  PASSED in T0.
;        The number of biquads making up the filter.  
;
; nx:    PASSED in T1.
;        Number of elements in the input and output vectors
;
; oflag: RETURNED in T0.
;        Overflow error flag  (returned value)
;         = 1 if a 32-bit data overflow occurred in an intermediate 
;             or final result.
;         = 0 if no such overflow occurred.
;
;
; Memory and Pointer Use Definition
; ---------------------------------
;
;              "x[nx]"                  "r[nx]"
;      AR0(x)--> x(0)            AR2(r)-->r(0)     first
;                x(1)                     r(1)
;                x(2)                     r(2)
;                 :                        :
;                 :                        :
;                x(nx-1)                  r(nx-1)  last
;
;
;      "dbuffer[4*nbiq]"            "h[5*nbiq]"
;                                 AR1(h)->b01
;      AR3(xn)-->x11                      b11 
;                x12                      b21
;                 :                       a11
;                x1n                      a21
;                x21                      b02
;                x22                      b12
;                 :                       b22
;                x2n                      a12
;      AR4(yn)-->y11                      a22
;                y12                       :
;                 :                       b0i
;                y1n                      b1i
;                y21                      b2i
;                y22                      a1i
;                 :                       a2i
;                y2n
;               
;
;      Def: xij/yij/aij/bij  where i = delay #
;                                  j = biquad #


	.arms_off
	.cpl_off
	.mmregs
;******************************************
;*       Assigns
;******************************************
	.def	_iircas51

;******************************************
;*       Constant Defines
;******************************************

;******************************************
;*       Variable Declarations
;******************************************

;**********************************************************************
; Program section
;**********************************************************************
	.text
_iircas51
;Context save

	PSH	mmap(ST0_55)
	PSH	mmap(ST1_55)
	PSH	mmap(ST2_55)
	PSH	mmap(ST3_55)

	BCLR	CPL			;DP relative addressing

;	PSH	mmap(DP)
;	MOV	#0, DP
;   ADDED REGARDING THE BUG REPORT, ZHENGTING
	PSH mmap(DP)
	PSH mmap(DPH)
	AMOV #0, XDP

	.dp	0

	PSH	@T3_L
	PSHBOTH	XAR4
	PSHBOTH	XAR7

;initialization
	BSET	SXMD			;sign extension enable
	BCLR	SATD			;D-unit saturate disable
	BSET	FRCT			;fractional mode enable
	BCLR	SATA			;A-unit saturate disable


;setup circular addressing
	MOV	T0, T3			;compute 2*nbiq
	SFTS	T3, #1
	MOV	@T3_L, BK03		;init AR0-3 circular buf size (2*nbiq)
	MOV	@T3_L, BK47		;init AR4-7 circular buf size (2*nbiq)

	BSET	AR3LC			;init AR3 = circular (dbuffer)
	MOV	@AR3_L, BSA23		;init AR2-3 circular start addr: dbuffer(1)

	BSET	AR4LC			;init AR4 = circular (dbuffer)
	MOV	XAR3, XAR4		;adjust AR4 to buffer start
	ADD	T3, AR4
	MOV	@AR4_L, BSA45		;init AR45 circ start addr: dbuffer(1+nbiq)

	MOV	#0, AR3		;init AR3 offset to x(n) buffer start
	MOV	#0, AR4		;init AR4 offset to y(n) buffer start

	SUB	#1, T1, T3		;compute nx-1
	MOV	T3, BRC0		;init outer loop counter (nx-1)

	MOV	XAR1, XAR7		;save original value to reinitialize coeff buffer pntr

	SUB	#1, T0, T3		;init inner loop counter (#bi-quads-1)
	MOV	T3, BRC1

	ADD	#1, T0, T1		;index for buffer reset

; Kernel
;  XAR0: x[] input
;  XAR1: h[] coefficients
;  XAR2: r[] result
;  XAR3: dbuffer[x]
;  XAR4: dbuffer[y]
;  XAR7: reinit XAR1

	RPTBLOCAL	loop1-1		;outer loop: process a new input

	MOV	*AR0+ << #16, AC1	; HI(AC1) = x(n)
	||RPTBLOCAL	loop2-1		;inner loop: process a bi-quad

	MPYM	*AR1+, AC1, AC0		; AC0 = b0*x(n)

	MACM	*AR1+, *(AR3+T0), AC0	; AC0 += b1*x(n-1)

	MACM	*AR1+, *AR3, AC0	; AC0 += b2*x(n-2)

	MOV	HI(AC1), *AR3		; x(n) replaces x(n-2) 
	||AADD	T1, AR3			; point to next x(n-1)

	MASM	*AR1+, *(AR4+T0), AC0	; AC0 -= a0*y(n-1) 

	MASM	*AR1+, *AR4, AC0	; AC0 -= a1*y(n-2) 

	MOV	rnd(HI(AC0)), *AR4	; y(n) replaces y(n-2)
	||AADD	T1, AR4			;point to next y(n-1)

	MOV	AC0, AC1		;input to next biquad

loop2:

	MOV	XAR7, XAR1		;reinitialize coeff pointer

	MOV	rnd(HI(AC0)), *AR2+	;store result to output buffer

loop1:

; Signal overflow
	MOV	#0, T0
	XCC	check1, overflow(AC0)
	MOV	#1, T0
check1:



;Context restore
	POPBOTH	XAR7
	POPBOTH	XAR4
	POP	@T3_L
;	POP	mmap(DP_L)
;   ZHENGTING ADDED
	POP mmap(DPH)
	POP mmap(DP)

	POP	mmap(ST3_55)
	POP	mmap(ST2_55)
	POP	mmap(ST1_55)
	POP	mmap(ST0_55)

	RET	
	
