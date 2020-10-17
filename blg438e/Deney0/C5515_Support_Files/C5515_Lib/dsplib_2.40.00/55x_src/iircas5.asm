;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:	 iircas5
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
;                  d(n)         
;  x(n) ---> + -----.-----x-- + --> y(n)
;           /|      |    b0   |\
;          | |    [z-1]       | |
;          | |      |         | |
;          | |      v         | | 
;          | |--x-d(n-1)--x---| |         
;          |  -a1   |    b1     | 
;          |        |           |
;          |      [z-1]         |
;          |        |           |
;          |        v           |
;          |---x--d(n-2)--x-----|
;            -a2         b2 
;
;              "FB"   "FF"
;
;
;        "FB" = Feedback Terms
;        "FF" = Feedforward Terms
;
;
; Algorithm (for single biquad)
; -----------------------------
;  d(n) = x(n) - a1*d(n-1) - a2*d(n-2)
;  y(n) = b0*d(n) + b1*d(n-1) + b2*d(n-2)
; 
;
; Function Call
; -------------
;
;  short oflag = iircas4(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nbiq,
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
;        H = a11 a21 b21 b01 b11 ....a1i a2i b2i b0i b1i
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
; dbuffer[2*nbiq]: PASSED in XAR3.
;        Pointer to delay buffer of length 2*nbiq.  See figure below for  
;        organization. In the case of multiple-buffering schemes, this 
;        array should be initialized to 0 for the first filter block only. 
;        Between consecutive blocks, the delay buffer preserves the 
;        previous elements needed.
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
;      "dbuffer[2*nbiq]"            "h[5*nbiq]"
;                                 AR1(h)->a11
;      AR3(dn)-->d11                      a21 
;                d12                      b21
;                 :                       b01
;                d1n                      b11
;                d21                      a12
;                d22                      a22
;                 :                       b22
;                d2n                      b02
;                                         b12
;                                          :
;                                         a1i
;                                         a2i
;                                         b2i
;                                         b0i
;                                         b1i
;
;      Def: dij / aij / bij  where i = delay #
;                                  j = biquad #


	.arms_off
	.cpl_off
	.mmregs
;******************************************
;*       Assigns
;******************************************
	.def	_iircas5

;******************************************
;*       Constant Defines
;******************************************
SCALE	.set	0

;******************************************
;*       Variable Declarations
;******************************************

;**********************************************************************
; Program section
;**********************************************************************
	.text
_iircas5
;Context save
	PSH	mmap(ST0_55)

	PSH	mmap(ST1_55)

	PSH	mmap(ST2_55)

	PSH	mmap(ST3_55)


	BCLR	CPL		;DP relative addressing

	;PSH	mmap(DP)
	;MOV	#0, DP		;set DP=0 for mmreg accesses
;   ADDED REGARDING THE BUG REPORT, ZHENGTING
	PSH mmap(DP)
	PSH mmap(DPH)
	AMOV #0, XDP

	.dp 0    

	PSH	T2
	PSH	T3
	PSHBOTH	XAR5
	PSHBOTH	XAR7

;Initialization
	BSET	SXMD		;sign extention enable
	BCLR	SATD		;D-unit saturate disable
	BSET	FRCT		;fractional mode enable
	BCLR	SATA		;A-unit saturate disable
    

; Setup circular addressing
	MOV	T0, T3		;compute 2*nbiq
	SFTS	T3, #1
	MOV	@T3, BK03	;init AR0-3 circular buf size (2*nbiq)

	BSET	AR3LC		;init AR3 = circular (dbuffer)
	MOV	@AR3, BSA23	;init AR2-3 circular start addr: dbuffer(0)

   
  	MOV #0, AR3               
	SUB	#1, T1, T3	;compute nx-1
	MOV	T3, BRC0	;init outer loop counter (nx-1)                

	MOV	XAR1, XAR7	;save original value to reinitialize coeff buffer pntr
	
	SUB	#1, T0, T3	;init inner loop counter (#bi-quads-1)
	MOV	T3, BRC1   

	MOV	#SCALE, T2	;scale factor
	
; Kernel
;  XAR0: x[] input
;  XAR1: h[] coefficients
;  XAR2: r[] result
;  XAR3: dbuffer[] 
;  XAR7: reinit XAR1

	RPTBLOCAL	loop1-1		; Outer Loop: Process a new input

	MOV	*AR0+ << #16, AC0	; HI(AC0) = x(n)
	||RPTBLOCAL	loop2-1		; Inner Loop: Process a bi-quad

	MASM  T3= *(AR3+T0), *AR1+, AC0	; AC0 -= a1*d(n-1)      (1)

	MASM T3= *AR3, *AR1+, AC0	; AC0 -= a2*d(n-2)      (2)

	MPYM	*AR1+, T3, AC0		; AC0 = b2*d(n-2)       (3)
	::MOV	HI(AC0 << T2), *AR3	;  d(n) replaces d(n-2)
           
	MACM	*(AR3+T0), *AR1+, AC0	; AC0 += b0*d(n)        (4)
                                      
	MACM	*AR3+, *AR1+, AC0	; AC0 += b1*d(n-1)      (5)
					;   input to next biquad

loop2:

	MOV	XAR7, XAR1		; reinitialize coeff pointer

	MOV	rnd(HI(AC0)), *AR2+	; store result to output buffer

loop1:

;Signal overflow
	MOV	#0, T0
	XCC	check1, overflow(AC0)
	MOV	#1, T0
check1:


;Context restore
	POPBOTH	XAR7
	POPBOTH	XAR5
	POP	T3
	POP	T2
	;POP	mmap(DP)
;   ZHENGTING ADDED
	POP mmap(DPH)
	POP mmap(DP)

	POP	mmap(ST3_55)
	POP	mmap(ST2_55)
	POP	mmap(ST1_55)
	POP	mmap(ST0_55)

	RET


 
