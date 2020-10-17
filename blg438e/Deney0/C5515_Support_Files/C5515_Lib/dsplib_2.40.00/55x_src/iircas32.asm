;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:	 iircas32
; Processor:   C55xx
; Description:  cascaded IIR direct form II using 5-coefs per biquad
;                using 32 bit coefficients and delay buffer
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
; x[nx]: PASSED in XAR0.					16 bit
;        Pointer to input vector of nx real elements.  
;        x(0) is the first input, 
;        while x(nx-1) is the last input.
;        
; h[2(5*nbiq)]: PASSED in XAR1.				32 bit
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
; r[nx]: PASSED in XAR2.					16 bit
;        Pointer to output vector of nx real elements.  
;        In-place computation (r = x) is allowed.  r(0) is the first 
;        output, while r(nx-1) is the last output.
;
; dbuffer[2*(2*nbiq + 2)]: PASSED in XAR3.	32 bit
;        Pointer to delay buffer of length 2*nbiq.  See figure below for  
;        organization. In the case of multiple-buffering schemes, this 
;        array should be initialized to 0 for the first filter block only. 
;        Between consecutive blocks, the delay buffer preserves the 
;        previous elements needed.
;
;        The first element in this array is special in that it 
;        contains the array index of the first buffer element in the 
;        delay buffer.  This is needed for multiple-buffering schemes, 
;        and should be initialized to zero (like all the other array 
;        entries) for the first block only.
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
;      "dbuffer[2*(2*nbiq+2)]"        "h[2*(5*nbiq)]"
;               index             AR1(h)->b21H
;               dummy                     b21L 
;       R3(dn)-->d21L                     b11H
;               d21H                      b11L
;               d11L                      b01H
;               d11H                      b01L
;               d22L                      a21H
;               d22H                      a21L
;               d12L                      a11H
;               d12H                      a11L
;                :                         :
;               d1nH                       :
;               extra 
;               dummy
;
;      Def: dij / aij / bij  where i = delay #
;                                  j = biquad #


	.arms_off
	.cpl_off
	.mmregs
;******************************************
;*       Assigns
;******************************************
	.def	_iir32

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
_iir32
;Context save
	psh mmap(ST0_55)
	psh mmap(ST1_55)
	psh mmap(ST2_55)
	psh mmap(ST3_55)

	bclr CPL, ST1_55				;DP relative addressing	
;	psh mmap(@DP)
;	mov #0, DP						;set DP=0 for mmreg accesses
;   ADDED REGARDING THE BUG REPORT, ZHENGTING
	PSH mmap(DP)
	PSH mmap(DPH)
	AMOV #0, XDP

	.dp 0    

	psh @T2
	psh @T3
	pshboth XAR5
	pshboth XAR7

;Initialization
	bset	SXMD, ST1_55			;sign extention enable
	bclr	SATD, ST1_55			;D-unit saturate disable
	bset	FRCT, ST1_55			;fractional mode enable
	bclr	SATA, ST3_55			;A-unit saturate disable
    
;Save pointer to index at dbuffer[0]    
	mov 	XAR3, XAR5

; Setup loop counters
	sub		#1, T1, T3				;compute nx-1
	mov		T3, BRC0				;init outer loop counter (nx-1)
	
	sub		#1, T0, T3				;init inner loop counter (#bi-quads-1)
	mov		T3, BRC1

; Setup circular addressing
	mov 	#4, T3					;size of single biquad delay buffer
    mov		@T3, BK03				;init AR0-3 circular buf size (2 delay elements)
	bset	AR3LC, ST2_55			;init AR3 = circular (dbuffer)
; 	add		#2, AR3					;adjust AR3 to buffer start
;	mov		@AR3, BSA23				;init AR2-3 circular start addr: dbuffer[2]
	mov		*AR5, AR3				;init AR3 offset to buffer start
	add		#2, AR5					;adjust AR5 to buffer start address (d20L)

	mov		XAR1, XAR7				;save coeff buffer start address to reinit pntr

; Setup offset registers
	mov		#3, T0					;b0 bypass index
	mov		#5, T1					;b0 pick up index
	mov		#SCALE, T2				;scale factor          
	
; Kernel
;  XAR0: x[] input (16 bit)
;  XAR1: h[] coefficients (32 bit: H/L)
;  XAR2: r[] result (16 bit)
;  XAR3: dbuffer[] (32 bit: H/L)
;  XAR5: dbuffer d2jL pointer 
;  XAR7: reinit XAR1
;
;                                                               
; BIQUAD's are calculated as follows                            
;    tmp = b2*d[n-2] + b1*d[n-1]                                
;    d[n] = x[n] or y[n]   (depending on BIQUAD)                
;    d[n] = d[n] - a2*d[n-2] - a1*d[n-1] 
;    store new d[n]                        
;    y[n] = b0*d[n] + tmp
;    store y[n]
;
; Note: u---L * u---L not needed for 32 bit result. 
;        Saves one MAC per tap.
;----------------------------------------------------------------                                                               
	rptb outer					; Outer Loop: Process a new input
;  for(i=0; i<nx; i++)
	 mov		@AR5, T3		; Init BSA23 for 1st biquad (d20L)
	 mov		@T3, BSA23
; HI(AC0) = x(n)
	 mov		*AR0+ << #16, AC0	
	 ||  rptb inner				; Inner Loop: Process a bi-quad
;      for(j=0; j<nbiq; j++)

; AC2 = b2 * d[n-2]
		mpym	*AR1, uns(*AR3+), AC3		; b2jH * ud2jL
		mpym	*AR1+, *AR3, AC2            ; b2jH * d2jH
		macm	uns(*AR1+), *AR3+, AC3      ; ub2jL * d2jH
		add		AC3 << #-16, AC2
		
; AC2 += b1 * d[n-1]
		mpym	*AR1, uns(*AR3+), AC3		; b1jH * ud1jL
		macm	*AR1+, *AR3, AC2			; b1jH * d1jH
		macm	uns(*(AR1+T0)), *AR3+, AC3	; ub1jL * d1jH
		add		AC3 << #-16, AC2
;   AR3 circular addressing -> last d2jL
;   AR1+index -> a2jH 
;    (skip b0j temporarily)

; AC0 -= a2 * d[n-2]
		mpym	*AR1, uns(*AR3+), AC1		; a2jH * ud2jL
		masm	*AR1+, *AR3, AC0			; a2jH * d2jH
		macm	uns(*AR1+), *AR3+, AC1		; ua2jL * d2jH
		sub		AC1 << #-16, AC0

; d[n] = AC0 -= a1 * d[n-1]
		mpym	*AR1, uns(*AR3+), AC1		; a1jH * ud1jL
		masm	*AR1+, *AR3, AC0			; a1jH * d1jH
		macm	uns(*(AR1-T1)), *AR3+, AC1	; ua1jL * d1jH
		sub		AC1 << #-16, AC0
;   AR3 circular addressing -> last d2jL
;   AR1-index -> b0jH

;   Replace d[n-2] with new d[n]
		mov		AC0 << T2, *AR3+			; d0jL
		mov		HI(AC0 << T2), *AR3-		; d0jH

; AC0 = b0 * d[n]
		mpym	*AR1, uns(*AR3+), AC1		; b0jH * ud0jL
		mpym	*AR1+, *AR3, AC0			; b0jH * d0jH
		macm	uns(*AR1+), *AR3-, AC1		; ub0jL * d0jH
		add		AC1 << #-16, AC0
;   AR3 adjusted -> last d2jH

; y[n] = AC0 += AC2
;  or input to next biquad
		add		AC2, AC0

;   update AR1 -> b2jH
		add		#4, AR1
                                    
;   update BSA23 -> next biquad (d2jL)
		add		#4, T3
inner:
		mov		@T3, BSA23
;  end of inner loop

	 aadd		#2, AR3				; Adjust dbuffer offset for next sample
	 mov		XAR7, XAR1			; reinitialize coeff pointer
outer:
	 mov	rnd(HI(AC0)), *AR2+		; store result to output buffer
;  end of outer loop

;Signal overflow check
	mov		#0, T0
	xcc		next, overflow(AC0)
	  mov	#1, T0
next:	

    sub		#2, AR5
;Save last index value
	mov		AR3, *AR5		; save index to dbuffer[0]

;Context restore
	popboth	XAR7
	popboth	XAR5
	pop		@T3
	pop		@T2
;	pop		mmap(@DP)
;   ZHENGTING ADDED
	POP mmap(DPH)
	POP mmap(DP)
	pop		mmap(ST3_55)
	pop		mmap(ST2_55)
	pop		mmap(ST1_55)
	pop		mmap(ST0_55)
	 
	ret


 