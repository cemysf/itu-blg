;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:     Complex block fir
; Processor:   C55xx
; Description: Implements complex finite impulse response filter using
;              dual-MAC approach.  C-callable.
;
; Useage: ushort oflag = firs(DATA *x,
;                             DATA *h,
;                             DATA *r,
;                             DATA *dbuffer,
;                             ushort nx,
;                             ushort nh)
;
;		
;	State of the registers after the call:
;
;	XAR0 contains *x
;	XAR1 contains *h
;     XAR2 contains *r
;	XAR3 contains *dbuffer
;	T0   contains nx
;     T1   contains nh
;
; Cycles: Core: 
;         Overhead:
;
; Code Size: 
;
;
; Copyright Texas instruments Inc, 1999
;----------------------------------------------------------------
; Revision History:
; 1.00  C. Iovescu  01/05/00 - Original release.
; 2.10	Rishi  08/03/2001 - optimized the code for benchmark.
;
;****************************************************************
	.ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ
ST2mask  .set  0000000100010000b    ;circular pointers


;----------------------------------------------------------------
; Assign auxiliary registers for temporaries and address
; calculations.
;----------------------------------------------------------------
	.asg     AR0, x_ptr           ;linear pointer
      .asg     CDP, h_ptr           ;circular pointer
      .asg     AR2, r_ptr           ;linear pointer
      .asg     AR4, db_ptr          ;circular pointer

	.asg     BSAC, h_base        ;base addr for h_ptr
	.asg     BKC, h_sz           ;circ buffer size for h_sz

	.asg     BSA45, db_base       ;base addr for db_ptr
      .asg     XAR4, xdb_base       ;extended base addr for db_ptr
      .asg     BK47, db_sz          ;circ buffer size for db_ptr
      .asg     BK47_L, db_sz_L      ;for memory mapped access

	.asg     BRC1, inner_cnt       ;inner loop count
      .asg     BRC0, outer_cnt      ;outer loop count

	.asg     T0, oflag


	.def    _cfir

        .text

_cfir:

        PSH	mmap(ST3_55)

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP - #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

;
; Save any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to save for this function

;
; Configure the status registers as needed.
;----------------------------------------------------------------

	AND	#001FFh, mmap(ST0_55)	;clear all ACOVx,TC1, TC2, C

	OR	#04140h, mmap(ST1_55)	;set CPL, SXMD, FRCT
      
	AND	#0F9DFh, mmap(ST1_55)	;clear M40, SATD, 54CM

	AND	#07A00h, mmap(ST2_55)	;clear ARMS, RDM, CDPLC, AR[0-7]LC
      
	AND	#0FFDDh, mmap(ST3_55)	;clear SATA, SMUL


;-----------------------------------------------------------------------
; Copy arguments to local locations and set registers
;
;-----------------------------------------------------------------------
; x pointer - passed in its destination register, need do nothing

; h pointer
	MOV	mmap(AR1), h_base	;base address of coefficients
	MOV XAR1, XCDP

	MOV	#0, h_ptr		;point to first coefficient
	||SFTL	T1, #1			;multiply by 2 because complex numbers

	MOV	mmap(T1), h_sz		;coefficient array size

; r pointer - passed in its destination register, need do nothing

; db pointer
	MOV	XAR3, xdb_base		;db array address
	AMAR	*AR3+			;align pointer to index location
	MOV	*AR3+, db_ptr		;index of oldest db entry
	MOV	mmap(AR3), db_base	;base address for db_ptr

	MOV	mmap(T1), db_sz		;db_sz = 2*nh

;	ADD	#2, mmap(db_sz)		;db_sz = 2*(nh+1)


; Set circular/linear ARx behavior
	OR	#ST2mask, mmap(ST2_55)	;config circ/linear pointers

;
; Setup loop counts
;----------------------------------------------------------------
	SFTL	T1, #-1			;restore original value
	SUB	#1, T0			;T0 = nx-1
	MOV	T0, outer_cnt		;outer loop executes nx times


	SUB	#3, T1			;T0 = nh-3
	MOV	T1, inner_cnt		;inner loop executes nh-2 times
;
; Setup index registers
;--------------------------------------------------------------------

	AMOV	#1, T0
	AMOV	#2, T1
	
; copy the first value from the input buffer to the delay buffer
	MOV	dbl(*x_ptr+), AC0
	MOV	AC0, dbl(*db_ptr)

	
	RPTBLOCAL	loop1-1			;start the outer loop

;BENCHMARK KERNEL ******************************************************




;First tap
	
	MPY	*db_ptr, *h_ptr+, AC0	
	::MPY	*db_ptr(T0), *h_ptr+, AC1	

	MAS	*db_ptr(T0), *h_ptr+, AC0
	::MAC	*(db_ptr+T1), *h_ptr+, AC1

;Taps 2 through N_TAP
	||RPTBLOCAL	loop2-1

	MAC	*db_ptr, *h_ptr+, AC0		;part 1 of dual MAC, real
	::MAC	*db_ptr(T0), *h_ptr+, AC1	;part 1 of dual MAC, imag
	MAS	*db_ptr(T0), *h_ptr+, AC0		
	::MAC	*(db_ptr+T1), *h_ptr+, AC1

loop2:

	MAC	*db_ptr, *h_ptr+, AC0		;part 1 of dual MAC, real
	::MAC	*db_ptr(T0), *h_ptr+, AC1	;part 1 of dual MAC, imag
	MASR	*db_ptr(T0), *h_ptr+, AC0		
	::MACR	*db_ptr, *h_ptr+, AC1

	
	MOV	HI(AC0), *r_ptr+		;store result real part
	
; copy the first value from the input buffer to the delay buffer
	MOV	dbl(*x_ptr+), AC0
	MOV	AC0, dbl(*db_ptr)

 
	MOV	HI(AC1), *r_ptr+		;store result imag part

loop1:						;end of outer loop




;TERMINATION *************************************************;


;
; Update the db entry point
;----------------------------------------------------------------

	MOV	db_ptr, *-AR3			;update 1st element of db array

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	||MOV	#0, oflag			;clear oflag

	XCCPART	check1, overflow(AC0)
	||MOV	#1, oflag			;overflow occurred
check1:

	XCCPART	check2, overflow(AC1)
	||MOV	#1, oflag
check2:



; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
	BCLR	FRCT				;clear FRCT

	AND	#0FE00h, mmap(ST2_55)		;clear CDPLC and AR[7-0]LC
      
	BSET	ARMS				;set ARMS

;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to restore for this function

       POP	mmap(ST3_55)


;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

;
; Return to calling function
;----------------------------------------------------------------
	RET					;return to calling function

;----------------------------------------------------------------
;End of file

