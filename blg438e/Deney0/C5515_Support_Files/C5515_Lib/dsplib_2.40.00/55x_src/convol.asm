;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    convol
; Processor:   C55xx
; Description: Implements real convolution algorithm using
;              single-MAC approach.  C-callable.
;
; Usage: ushort oflag = firs(DATA *x,
;                             DATA *h,
;                             DATA *r,
;                             ushort nr,
;                             ushort nh)
;
; Copyright Texas instruments Inc, 2000
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
      .asg     AR1, h_ptr           ;circular pointer
      .asg     AR2, r_ptr           ;linear pointer

      .asg     BSA01, h_base        ;base addr for h_ptr
      .asg     BK03, h_sz           ;circ buffer size for h_sz

      .asg     CSR, inner_cnt       ;inner loop count
      .asg     BRC0, outer_cnt      ;outer loop count

      .asg     T0, oflag            ;returned value

ST2mask  .set  0000000000000010b   ;circular/linear pointers


      .global _convol

      .text
_convol:

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

;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------


; x pointer - passed in its destination register, need do nothing

; h pointer - setup

	MOV	mmap(AR1), h_base	;base address of h[]

	SUB	#1, T1, h_ptr		;h_ptr = nh-1 (end of h[])

	MOV	mmap(T1), h_sz		;coefficient array size

; r pointer - passed in its destination register, need do nothing

; Set circular/linear ARx behavior

	MOV	#ST2mask, mmap(ST2_55)	;configure circular/linear pointers

;
; Setup loop counts
;----------------------------------------------------------------
	SUB	#1, T0			;T0 = nr - 1
	MOV	T0, outer_cnt		;outer loop executes nr times
	SUB	#3, T1, T0		;T0 = nh - 3
	MOV	T0, inner_cnt		;inner loop executes nh-2 times

;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
	SUB	#2, T1			;T1 = nh-2, adjustment for x_ptr

;
; Start of outer loop
;----------------------------------------------------------------
	||RPTBLOCAL	loop1-1		;start the outer loop

;1st iteration
	MPYM	*x_ptr+, *h_ptr-, AC0

;inner loop
	||RPT	inner_cnt
	MACM	*x_ptr+, *h_ptr-, AC0

;last iteration has different pointer adjustment and rounding
	MACMR	*(x_ptr-T1), *h_ptr-, AC0

;store result to memory
	MOV	HI(AC0), *r_ptr+	;store Q15 result to memory

loop1:					;end of outer loop

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	MOV	#0, oflag		;clear oflag

	XCCPART	check1, overflow(AC0)	;clears ACOV0
	||MOV	#1, oflag		;overflow occurred
check1:

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
	||RET				;return to calling function

;----------------------------------------------------------------
;End of file
