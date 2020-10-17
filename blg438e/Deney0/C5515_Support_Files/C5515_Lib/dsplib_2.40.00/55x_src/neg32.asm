;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    NEG32 
; Processor:   C55xx
; Description: Implements a 32-bit 2'complement of an input
;              vector.  This routine is C-callable.
;
; Algorithm:   for(i=0, i<nx, i++)
;	              r(i) =  - x(i); 
;
; Usage: ushort oflag = neg32 (LDATA *x,
;                              LDATA *r,
;                              ushort nx)
;
; Copyright Texas instruments Inc, 2000
;
; Note:
; 1. Corrected loop lable
;           ------Li Yuan 10/31/2000
; 2. Corrected SATD bit setting from clear to set.
;           ------Li Yuan 01/19/2001
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; -----------
; Stack frame
; -----------

RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

; ------------------------------
; Register usage and definitions
; ------------------------------
	.asg     AR0, x_ptr           	;linear pointer for first input vector
	.asg     AR1, r_ptr           	;linear pointer for result vector

	.asg     BRC0, outer_cnt      	;outer loop count
	.asg     T0, oflag           	;returned value

ST2mask	.set  0000000000010010b 	;circular/linear pointers


	.def _neg32
	.text

_neg32:


     PSH	mmap(ST3_55)

; ---------------------------------------------------------------
; Allocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP - #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

; ---------------------------------------------------------------
; Save any save-on-entry registers that are used
; ---------------------------------------------------------------
; - nothing to save for this function

; ---------------------------------------------------------------
; Configure the status registers as needed.
; ---------------------------------------------------------------

	AND	#001FFh, mmap(ST0_55)	;clear all ACOVx, TC1, TC2, C

	OR	#04340h, mmap(ST1_55)	;set CPL. SXMD, FRCT, SATD

	AND	#0FBDFh, mmap(ST1_55)	;clear M40, 54CM

	AND	#07A00h, mmap(ST2_55)	;clear ARMS, RDM, CDPLC, AR[0-7]LC

	AND 	#0FFDDh, mmap(ST3_55)	;clear SATA, SMUL

; ---------------------------------------------------------------
; Setup passed parameters in their destination registers
; Setup linear CDP/ARx behavior
; ---------------------------------------------------------------
; x pointer - passed in its destination register
; y pointer - passed in its destination register
; r pointer - passed in its destination register
; Set circular/linear ARx behavior                               
; ---------------------------------------------------------------

	OR	#ST2mask, mmap(ST2_55)	;config circ/linear pointers

; ---------------------------------------------------------------
; Setup loop counts
; --------------------------------------------------------------

	SUB	#1, T0			;T0 = nx - 1
	MOV	T0, outer_cnt		;outer loop executes nx times

; ---------------------------------------------------------------
; Start of outer loop 
; for (i=0; iP<nx; i++)
;    R(i) = - X(i);
; ---------------------------------------------------------------

	RPTBLOCAL   outerloop - 1 		;start the outer loop
	MOV40	    dbl(*AR0+), AC0	;AC0=32-bit value (input vector)
	NEG	AC0			;negate AC0
	MOV	AC0, dbl(*AR1+)		;storing 32-bit ACC to mem
outerloop:				;end of outer loop

; ---------------------------------------------------------------
; Check if overflow occurred, and setup return value
; ---------------------------------------------------------------

	MOV	#0, oflag		;cler oflag

	XCCPART	OvrFlow, overflow(AC0)	;clears AC0V0
	||MOV	#1, oflag		;overflow occured

; ---------------------------------------------------------------
; Restore status regs to expected C-convention values as needed
; ---------------------------------------------------------------

	AND	#0FE00h, mmap(ST2_55)	;clear CDPLC and AR[0-7]LC

	BSET	ARMS			;set ARMS
	BCLR	FRCT			;clear FRCT

; ----------------------------------------------------------------
; Restore any save-on-entry registers that are used
; ----------------------------------------------------------------
; - nothing to restore for this function

; ---------------------------------------------------------------
; Deallocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

     POP	mmap(ST3_55)

; ---------------------------------------------------------------
; Return to calling function
; ---------------------------------------------------------------
      RET				;return to calling function

;----------------------------------------------------------------
;End of file


