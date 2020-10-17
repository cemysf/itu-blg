;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    ADD
; Processor:   C55xx
; Description: Implements a vector add using a single-MAC 
;              approach.
;
; Usage: ushort oflag = add (DATA *x,
;                             DATA *y,
;                             DATA *r,
;                             ushort nx,
;                             ushort scale)
;
; Copyright Texas instruments Inc, 2000
;****************************************************************

	.ARMS_off			;enable assembler for ARMS=0
	.CPL_on				;enable assembler for CPL=1
	.mmregs				;enable mem mapped register names

; -----------
; Stack frame
; -----------

RET_ADDR_SZ       .set 1            	;return address
REG_SAVE_SZ       .set 0            	;save-on-entry registers saved
FRAME_SZ          .set 0            	;local variables
ARG_BLK_SZ        .set 0            	;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

; ------------------------------
; Register usage and definitions
; ------------------------------
	.asg     AR0, x_ptr           	;linear pointer for first input vector
	.asg     AR1, y_ptr           	;linear pointer for second input vector
	.asg     AR2, r_ptr           	;linear pointer for result vector

	.asg     BRC0, outer_cnt      	;outer loop count
	.asg     T0, oflag           	;returned value

ST2mask	.set  0000000000010010b 	;circular/linear pointers


	.def _add
	.text

_add:

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

	AND	#001FFh, mmap(ST0_55)	;clear all ACOVx,TC1, TC2, C

	OR	#04140h, mmap(ST1_55)	;set CPL, SXMD, FRCT

	AND	#0F9DFh, mmap(ST1_55)	;clear M40, SATD, 54CM

	AND 	#07A00h, mmap(ST2_55)	;clear ARMS, RDM, CDPLC, AR[0-7]LC

	AND	#0FFDDh, mmap(ST3_55)	;clear SATA, SMUL

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
; ---------------------------------------------------------------

	SUB	#1, T0			;T0 = nx-1
	MOV	T0, outer_cnt		;outer loop executes nx times

; ---------------------------------------------------------------
; Start of outer loop 
; for (i=0; iP<nx; i++)
;    R(i) = X(i) + Y(i);
; ---------------------------------------------------------------

	RPTBLOCAL	loop		;start the outer loop
	ADD	*AR0+, *AR1+, AC0		;vector add of two inputs

; ---------------------------------------------------------------
; To implement scaling:
; if(scale = #1) then AC0=AC0/2;
; otherwise *r_ptr+ = AC0
; ---------------------------------------------------------------

	XCC	loop, T1!=#0		;testing for scaling
      ||SFTA	AC0, -1			;if scale=1, AC0=AC0/2
loop:	MOV	HI(AC0), *AR2+		;end of outer loop

; ---------------------------------------------------------------
; Check if overflow occurred, and setup return value
; ---------------------------------------------------------------

	MOV	#0, oflag		;clear oflag
	XCC	check, overflow(AC0)
      ||MOV	#1, oflag		;overflow occured

check:

; ---------------------------------------------------------------
; Restore status regs to expected C-convention values as needed
; ---------------------------------------------------------------

	AND	#0FE00h, mmap(ST2_55)	;clear CDPLC and AR[7-0]LC

	BSET	ARMS			;set ARMS
	BCLR	FRCT			;clear FRCT

; ----------------------------------------------------------------
; Restore any save-on-entry registers that are used
; ----------------------------------------------------------------
; - nothing to restore for this function


       POP	mmap(ST3_55)


; ---------------------------------------------------------------
; Deallocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP + #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
; - not necessary for this function (the above is zero)

; ---------------------------------------------------------------
; Return to calling function
; ---------------------------------------------------------------

      RET		 
		
;----------------------------------------------------------------
;End of file 	
