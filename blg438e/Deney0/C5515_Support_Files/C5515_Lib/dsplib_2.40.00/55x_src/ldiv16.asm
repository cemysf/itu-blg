;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    ldiv16
; Processor:   C55xx
; Description: Implements long division function.  Reciperical of Q15, y 
; 	       is calculated then multiplied times Q31 x. C-callable.
;
; Useage: void ldiv16(LDATA *x, 
;			DATA *y, 
;			DATA *z, 
;			DATA *zexp, 
;			ushort nx)
;
; Algorithm:
;     This routine returns the fractional and exponential portion
;  of the division in the form of :
;          
;               z[i] * zexp[i] = reciprocal
;
; History:
;         07/07/2003 - d. elam fixed bug in range test 
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
      .asg     AR1, y_ptr	    ;linear pointer
      .asg     AR2, z_ptr           ;linear pointer
      .asg     AR3, zexp_ptr        ;linear pointer
      .asg     T0, norm_ptr	    ;temp linear pointer
      .asg     AR4, ye_ptr	    ;table linear pointer
      	     
      
      .asg     BRC0, outer_cnt      ;outer loop count

      
ST2mask  .set  0000000000000000b    ;circular/linear pointers


      .global _ldiv16
      
      .text
_ldiv16:

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

	AND	#001FFh, mmap(ST0_55)	;clear all ACOVx, TC1, TC2, C

	OR	#04100h, mmap(ST1_55)	;set CPL, SXMD
	
	AND	#0F9DFh, mmap(ST1_55)	;clear M40, SATD, 54CM

	AND	#07A00h, mmap(ST2_55)	;clear ARMS, RDM, CDPLC, AR[0-7]LC

	AND	#0FFDDh, mmap(ST3_55)	;clear SATA, SMUL

;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; z pointer - passed in its destination register, need do nothing
      
; zexp  pointer - passed in its destination register, need do nothing

; Set circular/linear ARx behavior

	OR	#ST2mask, mmap(ST2_55)	;config circ/linear pointers

;
; Setup loop counts
;----------------------------------------------------------------

	MOV	#1, BRC1		;repeat inner loop 2x

	SUB	#1, T0			;T0 = n-1
	MOV	T0, outer_cnt		;outer loop executes n times

;
; Start of outer loop
;----------------------------------------------------------------
	RPTB	loop1-1			;start the outer loop
	MOV	*y_ptr+ << #16, AC1	;load first input value
	MANT	AC1, AC0		;calculate normalization of 1st value
	::NEXP	AC1, T1
	NEG	T1			;exponent value for the offset pointer
	ADD	#1, T1, ye_ptr		;offset pointer to exponent
	MOV	HI(AC0), norm_ptr	;store xnorm
	||SFTS	AC0, #-1		;shift right by one for 1st approximation
	XOR	#1FFFh << #16, AC0	;estimate the first Ym value
	MOV	HI(AC0), *z_ptr		;store first Ym

; First two iterations      Calculate Ym = 2*Ym - Ym^2*X
	||RPTBLOCAL	loop2-1
	MOV	*z_ptr << #15, AC0
	||MOV	*z_ptr, T1
	MPYM	*z_ptr, norm_ptr, AC1
	MOV	HI(AC1 << #1), *z_ptr
	MPYM	*z_ptr, T1, AC1
	SUB	AC1 << #1, AC0
	MOV	HI(AC0 << #2), *z_ptr

loop2:

; final iteration - same as previous loop without final command
; Calculate Ym = 2*Ym - Ym^2*X

	MOV	*z_ptr << #15, AC0
	||MOV	*z_ptr, T1
	MPYM	*z_ptr, norm_ptr, AC1
	MOV	HI(AC1 << #1), *z_ptr
	MPYM	*z_ptr, T1, AC1
	SUB	AC1 << #1, AC0
	
;-------------------------------------------------------------------------
; Check if value is in range 8000h <= Ym <= 7fffh, Adjust sign of result
;-------------------------------------------------------------------------
	BSET SATD
	SFTS    AC0, #3 
	MOV	HI(AC0), *z_ptr
	BCLR SATD
	
;-------------------------------------------------------------------------
; Multiply numerator by reciprocal of denominator
;-------------------------------------------------------------------------
	MPYM	*z_ptr, *x_ptr+, AC0		;numerator high * denominator high
	MPYM	*z_ptr, uns(*x_ptr+), AC1		;numeratot low * denominator high

;	OR	#04000h, mmap(ST1_55)		;turn off SXMD, set CPL

	ADD	AC1 << #-16, AC0
	SFTS	AC0, #1

	OR	#04100h, mmap(ST1_55)		;set CPL, SXMD


	ADD	#8000h, AC0		;rounding
	MANT	AC0, AC1
	::NEXP	AC0, T1		;calculate normalization of 1st value
	ADD	ye_ptr, T1		;offset pointer to exponent values
	MOV	#1, AC2
	||BCC final, T1 >= #0
	MOV	*(AC1H) << T1, AC1
	MOV	*(AC1L) << #16, AC1
	MOV	#0, T1

final:	
	SFTS	AC2, T1, AC0		;calculate exponent value
	||MOV	HI(AC1), *z_ptr+
	MOV	AC0, *zexp_ptr+		;store exponent

loop1:					;end of outer loop

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------

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

       POP	mmap(ST3_55)
;
; Return to calling function
;----------------------------------------------------------------
      RET			;return to calling function

	
;----------------------------------------------------------------
;End of file

