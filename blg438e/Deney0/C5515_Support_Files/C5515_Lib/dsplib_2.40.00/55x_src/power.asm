;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    POWER
; Processor:   C55xx
; Description: Implements a vector power using a single-MAC 
;              approach.  This routine is C-callable.
;
; Algorithm:   for(i=0, i<nx, i++)
;                r(i) += x(i) * x(i); 
;
; Usage: ushort oflag = add (DATA *x,
;                             LDATA *r,
;                             ushort nx,
;
; Copyright Texas instruments Inc, 2000
;
; History:
; - Corrected return register from AR2 to AR1.
;               ---- Li Yuan    01/17/01
;
; - Return overflow value is in T0 instead of AC0. 
;   Output vector is pointed by AR3 and returned.
;      Zhengting He - 10/25/2006
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

; -----------
; Stack frame
; -----------

RET_ADDR_SZ       .set 1            ;return address
; REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
REG_SAVE_SZ       .set 2            ;save-on-entry registers saved CHANGED BY ZHENGTING
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

; ------------------------------
; Register usage and definitions
; ------------------------------
	.asg     AR0, x_ptr           	;linear pointer for first input vector
	.asg     AR1, r_ptr           	;linear pointer for result vector
;	.asg     AR2, r_ptr           	;linear pointer for result vector NEW

ST2mask	.set  0000000000010010b 	;circular/linear pointers


        .def _power
	.text

_power:

     PSH	mmap(ST3_55)

; ---------------------------------------------------------------
; Allocate the local frame and argument block
; ---------------------------------------------------------------
;      SP = SP - #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ)
	AADD #-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ +1), SP 
; - not necessary for this function (the above is zero)

; ---------------------------------------------------------------
; Save any save-on-entry registers that are used
; ---------------------------------------------------------------
; - nothing to save for this function
	MOV	XAR3, dbl(*SP(#0))	; PSHM    XAR3

; ZHENGTING ADDED THESE 2 LINES SINCE AR3 NEEDS TO BE USED TO 
; RETURN RESULT. SAVE XAR3 NOW AND RESTORE XAR3 LATER 

; ---------------------------------------------------------------
; Configure the status registers as needed.
; ---------------------------------------------------------------

	AND	#001FFh, mmap(ST0_55)		;clear all ACOVx, TC1, TC2, C
	
	OR	#04140h, mmap(ST1_55)		;set CPL, SXMD, FRCT

	AND	#0F9DFh, mmap(ST1_55)		;clear M40, SATD, 54CM

	AND	#07A00h, mmap(ST2_55)		;clear ARMS, RDM, CDPLC, AR[0-7]LC

	AND	#0FFDDh, mmap(ST3_55)		;clear SATA, SMUL

; ---------------------------------------------------------------
; Setup passed parameters in their destination registers
; Setup linear CDP/ARx behavior
; ---------------------------------------------------------------
; x pointer - passed in its destination register
; y pointer - passed in its destination register
; r pointer - passed in its destination register
; Set circular/linear ARx behavior                               
; ---------------------------------------------------------------

	OR	#ST2mask, mmap(ST2_55)		;config circ/linear pointers

; ---------------------------------------------------------------
; Setup loop counts
; ---------------------------------------------------------------

	SUB	#2, T0				;T0 = nx - 1
	MOV	T0, CSR				;outer loop executes nx times
	SQRM	*x_ptr+, AC0			;zero out the ACC and the first mpy

; ---------------------------------------------------------------
; Start of outer loop 
; for (i=0; iP<nx; i++)
;    R(i) = X(i) * X(i);
; ---------------------------------------------------------------

	||RPT	CSR

; ----------------------------------------------------
; AC0 = m40(rnd(AC1 + uns(*x_ptr+)) * uns(*y_ptr+))))
; ----------------------------------------------------

	SQAM	*x_ptr+, AC0			;vector MAC of two inputs
	MOV AR1, AR3
	MOV AC0, dbl(*AR3)  ; ZHENGTING ADDED SINCE AR1 CANNOT BE USED HERE

; ADDED CODE TO CHECK THE OVERFLOW
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	MOV #0, T0
	
    .if  $isdefed("SI_BUGS")
	XCC dummy1, overflow(AC0)
	.else
	XCCPART dummy1, overflow(AC0)
	.endif
dummy1:  MOV #1, T0 		; 


; ---------------------------------------------------------------
; Restore status regs to expected C-convention values as needed
; ---------------------------------------------------------------

	AND	#0FE00h, mmap(ST2_55)		;clear CDPLC and AR[0-7]LC

	BSET	ARMS				;set ARMS
	BCLR	FRCT				;clear FRCT

; ----------------------------------------------------------------
; Restore any save-on-entry registers that are used
; ----------------------------------------------------------------
; - nothing to restore for this function
; ZHENGTING ADDED
	MOV	dbl(*SP(#0)), XAR3	; POPM    AR3	
      
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
	AADD #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ +1), SP

    POP	mmap(ST3_55)

; ---------------------------------------------------------------
; Return to calling function
; ---------------------------------------------------------------
      RET					;return to calling function

;----------------------------------------------------------------
;End of file

