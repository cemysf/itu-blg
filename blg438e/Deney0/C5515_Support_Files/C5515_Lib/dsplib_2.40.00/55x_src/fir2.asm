;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    fir2
; Processor:   C55xx
; Description: Implements finite impulse response filter using
;              dual-MAC approach.  C-callable.
;
; Useage: ushort oflag = firs(DATA *x,
;                             DATA *h,
;                             DATA *r,
;                             DATA *dbuffer,
;                             ushort nx,
;                             ushort nh)
;
; Copyright Texas instruments Inc, 2000
; History:
; 2.10	Rishi  08/03/2001 - optimized the code for benchmark.
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


; Register usage
; --------------
      .asg     AR0, x_ptr           ;linear pointer
      .asg     AR1, db_ptr1         ;circular pointer
      .asg     AR2, r_ptr           ;linear pointer
      .asg     AR3, db_ptr2         ;circular pointer
      .asg     CDP, h_ptr           ;circular pointer

      .asg     BSA01, db_base1      ;base addr for db_ptr1
      .asg     XAR1, xdb_base1      ;extended base addr for db_ptr1
      .asg     BSA23, db_base2      ;base addr for db_ptr2
      .asg     BK03, db_sz          ;circ buffer size for db_ptr1 and db_ptr2
      .asg     BK03_L, db_sz_L      ;for memory mapped access
      .asg     BSAC, h_base         ;base addr for h_ptr
      .asg     XCDP, xh_base        ;extended base addr for h_ptr
      .asg     BKC, h_sz            ;circ buffer size for h_sz

      .asg     CSR, inner_cnt       ;inner loop count
      .asg     BRC0, outer_cnt      ;outer loop count

      .asg     T0, oflag            ;returned value

ST2mask  .set  0000000100001010b    ;circular/linear pointers


      .global _fir2

      .text
_fir2:

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

	AND	#001FFh, mmap(ST0_55)     ;clear all ACOVx,TC1, TC2, C

	OR	#04140h, mmap(ST1_55)     ;set CPL, SXMD, FRCT
      
	AND	#0F9DFh, mmap(ST1_55)     ;clear M40, SATD, 54CM

	AND	#07A00h, mmap(ST2_55)     ;clear ARMS, RDM, CDPLC, AR[0-7]LC
      
	AND	#0FFDDh, mmap(ST3_55)     ;clear SATA, SMUL

;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer
	MOV	XAR1, xh_base		;extended base address for h_ptr
	MOV	#0, h_ptr		;point to first coefficient

	MOV	mmap(AR1), h_base	;base address of coefficients

	MOV	mmap(T1), h_sz		;coefficient array size

; r pointer - passed in its destination register, need do nothing

; db pointers, part 1 - must come before circ/linear ARx setup
	MOV	XAR3, XAR4		;save db array address
	MOV	XAR4, xdb_base1		;extended base address for db_ptr1
					;xdb_base2 already setup via argument pass
	MOV	*AR4, db_ptr1		;index of oldest db entry
	MOV	*AR4+, db_ptr2		;index of oldest db entry

	MOV	mmap(AR4), db_base1	;base address for db_ptr1

	MOV	mmap(AR4), db_base2	;base address for db_ptr2

; Set circular/linear ARx behavior
	OR	#ST2mask, mmap(ST2_55)	;config circ/linear pointers

	MOV	mmap(T1), db_sz		;db_sz = nh

	ADD	#1, mmap(db_sz)		;db_sz = nh+1

; db pointers, part 2 - must come after circ/linear ARx setup
	AMAR	*db_ptr2-		;index of 2nd oldest db entry

;
; Setup loop counts
;----------------------------------------------------------------
	||SFTS	T0, #-1			;T0 = nx/2

	SUB	#1, T0			;T0 = (nx/2 - 1)
	MOV	T0, outer_cnt		;outer loop executes nx/2 times
	SUB	#3, T1, T0		;T0 = nh-3
	MOV	T0, inner_cnt		;inner loop executes nh-2 times

;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
	ADD	#1, T1			;T1 = nh+1, adjustment for db_ptr1, db_ptr2

	MOV	*x_ptr+, *db_ptr1	;get 1st new input value
	MOV	*x_ptr+, *db_ptr2	;get 2nd new input value (newest)

;
; Start of outer loop
;----------------------------------------------------------------
	||RPTBLOCAL	loop1-1		;start the outer loop



;1st iteration
	MPY	*db_ptr1+, *h_ptr+, AC0		;part 1 of dual-MPY
	::MPY	*db_ptr2+, *h_ptr+, AC1		;part 2 of dual-MPY

;inner loop
	||RPT	inner_cnt
	MAC	*db_ptr1+, *h_ptr+, AC0		;part 1 of dual-MAC
	::MAC	*db_ptr2+, *h_ptr+, AC1		;part 2 of dual-MAC

;last iteration has different pointer adjustment and rounding
	MACR	*(db_ptr1-T1), *h_ptr+, AC0	;part 1 of dual-MAC
	::MACR	*(db_ptr2-T1), *h_ptr+, AC1	;part 2 of dual-MAC
	
	MOV	*x_ptr+, *db_ptr1	;get 1st new input value
	MOV	*x_ptr+, *db_ptr2	;get 2nd new input value (newest)

;store results to memory	
	MOV pair(HI(AC0)), dbl(*r_ptr+)    ;store 1st Q15 result to memory
	                                   ;store 2nd Q15 result to memory

loop1:					;end of outer loop

;
; Update the db entry point
;----------------------------------------------------------------
	MOV	db_ptr1, *-AR4		;update 1st element of db array

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	||MOV	#0, oflag		;clear oflag

	XCCPART	check1, overflow(AC0)	;clears ACOV0
	||MOV	#1, oflag		;overflow occurred
check1:

	XCCPART	check2, overflow(AC1)	;clears ACOV1
	||MOV	#1, oflag		;overflow occurred
check2:

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
	BCLR	FRCT			;clear FRCT

	AND	#0FE00h, mmap(ST2_55)	;clear CDPLC and AR[7-0]LC

	BSET	ARMS			;set ARMS 

;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
; - nothing to restore for this function

;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

;
; Return to calling function
;----------------------------------------------------------------
	||RET			;return to calling function

;----------------------------------------------------------------
;End of file

