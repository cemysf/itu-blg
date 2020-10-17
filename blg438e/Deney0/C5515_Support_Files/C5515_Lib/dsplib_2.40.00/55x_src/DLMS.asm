;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:	dlms
; Processor:   C55xx
; Description: dlms fir filter
;
; Usage: short oflag = dlms(DATA *h, DATA *x, DATA *r, DATA *des,
;			DATA *dbuffer, DATA step, ushort nh, ushort nx)
;
; ...where
;	h[nh]		Pointer to coefficient vector of size nh
;			- h is stored in reverse order: h(n-1), ... h(0)
;	x[nx]		Pointer to input vector of size nx
;	r[xn]		Pointer to output data vector.
;			- r can be equal to x
;	des[nx]		Pointer to expected-output array
;	dbuffer[nh+2]	Pointer to delay buffer structure
;			- first element of structure is index into array
;			  of OLDEST data (to be overwritten with new)
;			- remaining elements are modulo-addressed for
;			  sample 0 to nh. NOTE that this delay buffer
;			  yields an array length of nh+1, which is used
;			  for Dual-MAC operations(not used here).
;	step		Scale factor to control adaptation rate = 2*mu
;	nh		Number of filter coefficients. Filter order = nh-1.
;	nx		Number of input samples to process (length of input
;			and output data vectors).
;	oflag	Overflow Flag
;			- If oflag = 1, a 32-bit overflow has occured
;			- If oflag = 0, a 32-bit overflow has not occured
;
;  Copyright Texas instruments Inc, 2000
;
; History:
; 2.10	Rishi  08/03/2001 - optimized the code for benchmark.
;****************************************************************
		.length 32767
        .cpl_on

	.asg	0, save_T3		; 2*mu*error(i) variable
	.asg	1, save_AR5
	.asg	2, ret_addr
	.asg	3, arg_nx

; register usage
;	XAR0-XAR4, T0 & T1 as well as accumulators are all available to callee
;	XAR0 through XAR4 are already loaded with *x, *h, *r, *des and *dbuffer
;	 respectively upon entry.
;	While T0 and T1 are loaded with the values of STEP and NH, respectively

	.asg	ar0, ar_input
	.asg	ar1, ar_coef
	.asg	ar2, ar_output
	.asg	ar3, ar_des
	.asg	ar4, ar_dbuffer
	.asg	ar5, ar_data
	.asg	T0, T_step
	.asg	T1, T_nh

;*****************************************************************************
	.def	_dlms

_dlms:

; Preserve registers
;-------------------
	PSH T3, AR5					;AR5 will be used for the index into dbuffer
								;T3 is needed for LMS instruction

; Set math and overflow modes
;---------------------------
; Status registers
	MOV #0, mmap(ST0_55)		;all fields cleared (OVx, C, TCx)
	OR #4140h, mmap(ST1_55)	;set CPL, FRCT, SXMD
	AND #07940h, mmap(ST1_55)	;clear BRAF, M40, SATD, C16, 54CM, ASM
	OR #0022h, mmap(ST2_55)	;AR1 & AR5 pointers put in circular mode
	BCLR ARMS					;disable ARMS bit in ST2
	BCLR SST					;make sure Saturate-on-STore bit in ST3 is disabled

;
; Get arguments
;---------------
	MOV *ar_dbuffer+, ar_data	;set AR5 to index in data array
								; of oldest input sample
	MOV mmap(AR4), BSA45		;set BSA45 to start of data buffer
								; NOTE that this is the SECOND
								; element of the dbuffer structure
	MOV mmap(AR1), BSA01		;copy start of coeffs to BSA01
	MOV #0, ar_coef 			;...then set AR0 to zero (1st coeff)
	ADD #-1, *SP(arg_nx)		;sub 1 from # of inputs for loopcount
	MOV *SP(arg_nx), BRC0		;set outer loop to number of inputs-1
	MOV mmap(T_nh), BK03		;load BK03 with # of coeffs for use w/ AR2
	AADD #1, T_nh
	MOV mmap(T_nh), BK47		;load BK03 with # of data samples (nh+1)
								; in delay-line for use w/ AR4
	ASUB #3, T_nh
	MOV mmap(T_nh), BRC1		;set inner loop to number of coeffs-2

; Loop through input data stream
;-------------------------------
StartSample:
	MOV #0, AC1					;clear AC1 for initial error term
 ||	RPTBLOCAL Outer_End-1			;...while starting outer loop
	 MOV  HI(AC1), T3			;place error term in T3
	 MOV *ar_input+, *ar_data+	;copy input -> state(0)
	 MPYM *ar_data+, T3, AC0	;place first update term in AC0
 ||	 MOV #0, AC1				;...while clearing FIR value
	 LMS *ar_coef, *ar_data, AC0, AC1	;AC0 = update coef
								;AC1 = start of FIR output
 ||  RPTBLOCAL Inner_End-1			;...while starting inner loop
	  MOV HI(AC0), *ar_coef+	;store updated coef
 ||	  MPYM *ar_data+, T3, AC0	;...while calculating next update term
	  LMS *ar_coef, *ar_data, AC0, AC1	;AC0 = update coef

Inner_End:
					;AC1 = update of FIR output
	 MOV HI(AC0), *ar_coef+		;store updated coef
 ||	 MOV rnd(HI(AC1)), *ar_output+	;...and store FIR output

	 SUB AC1, *ar_des+ << #16, AC2	;AC2 is error amount
 ||	 AMAR *ar_data+				;point to oldest data sample
	MPYR T_step, AC2, AC1		;place updated mu_error term in AC1

Outer_End:

	MOV ar_data, *-ar_dbuffer	;dbuffer.index = index of oldest data

; Return overflow flag
; --------------------
    ||	MOV #0, T0				;store zero for return value
	XCCPART OvrFlow, overflow(AC1)
    || 	MOV #1, T0				;return value 1 if overflow was encountered
OvrFlow:

;
; Restore stack to previous value
; Reset status regs to restore normal C operating environment
; Return to calling function
;----------------------------------------------------------------
	POP T3, AR5

;NO presumed values in ST0 by C-environment

	BCLR FRCT					;clear FRCT bit in ST1 for C-environment
	BSET ARMS					;set ARMS bit for C-environment
	AND #0F800h, mmap(ST2_55) 	;all pointers put in linear mode

;No presumed values of ST3 were modified

	RET							;return to calling function

        .end

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
