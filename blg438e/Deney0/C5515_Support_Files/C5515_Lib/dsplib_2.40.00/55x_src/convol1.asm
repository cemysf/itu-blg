;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    convol1
; Processor:   C55xx
; Description: Implements real convolution algorithm using
;              dual-MAC approach.  C-callable.
;
; Useage: ushort oflag = firs(DATA *x,
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
RET_ADDR_SZ    .set 1               ;return address
REG_SAVE_SZ    .set 0               ;save-on-entry registers saved
FRAME_SZ       .set 0               ;local variables
ARG_BLK_SZ     .set 0               ;argument block

PARAM_OFFSET   .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
      .asg     AR0, x_ptr           ;linear pointer
      .asg     AR2, r_ptr           ;linear pointer
      .asg     CDP, h_ptr           ;circular pointer

      .asg     BSAC, h_base         ;base addr for h_ptr
      .asg     BKC, h_sz            ;circ buffer size for h_sz
      .asg     XCDP, xh_base        ;extended base address for h_ptr

      .asg     CSR, inner_cnt       ;inner loop count
      .asg     BRC0, outer_cnt      ;outer loop count

      .asg     T0, oflag            ;returned value

ST2mask  .set  0000000100000000b    ;circular/linear pointers


      .global _convol1

      .text
_convol1:

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

; h pointer - setup
      MOV	XAR1, xh_base               ;extended base address for h_ptr

      SUB	#1, T1, AC0                ;AC0 = nh-1

      MOV	mmap(AC0L), h_ptr                ;h_ptr = nh-1 (end of h[])

      MOV	mmap(AR1), h_base               ;base address of coefficients

      MOV	mmap(T1), h_sz                  ;coefficient array size

; r pointer - passed in its destination register, need do nothing

; Set circular/linear ARx behavior
      MOV	#ST2mask, mmap(ST2_55)            ;configure circular/linear pointers

;
; Setup loop counts
;----------------------------------------------------------------
      SFTS	T0, #-1                 ;T0 = nr/2
      SUB	#1, T0                  ;T0 = (nr/2 - 1)
      MOV	T0, outer_cnt                ;outer loop executes nr/2 times
      SUB	#3, T1, T0                 ;T0 = nh-3

      MOV	T0, inner_cnt                ;inner loop executes nh-2 times
      ||MOV	#1, T0                     ;x_ptr offset for parallel computation

;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
      SUB	#3, T1                  ;DR1 = nh-3, adjustment for x_ptr

;
; Start of outer loop
;----------------------------------------------------------------
      ||RPTBLOCAL	loop1-1               ;start the outer loop

;1st iteration
      MPY	*x_ptr+, *h_ptr-, AC0                   ;part 1 of dual-MPY
      ::MPY	*x_ptr(T0), *h_ptr-, AC1                 ;part 2 of dual-MPY

;inner loop
      ||RPT	inner_cnt
      MAC	*x_ptr+,  *h_ptr-, AC0           ;part 1 of dual-MAC
      ::MAC	*x_ptr(T0), *h_ptr-, AC1         ;part 2 of dual-MAC

;last iteration has different pointer adjustment and rounding
      MACR	*(x_ptr-T1), *h_ptr-, AC0  ;part 1 of dual-MAC
      ::MACR	*x_ptr(T0), *h_ptr-, AC1    ;part 2 of dual-MAC

;store result to memory
      MOV	HI(AC0), *r_ptr+             ;store 1st Q15 result to memory
      MOV	HI(AC1), *r_ptr+             ;store 2nd Q15 result to memory

loop1:

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
      MOV	#0, oflag                                        ;clear oflag

      XCCPART	check1, overflow(AC0)               ;clears ACOV0
      ||MOV	#1, oflag                                      ;overflow occurred
check1:

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
      BCLR	FRCT      ;clear FRCT

      AND	#0FE00h, mmap(ST2_55)     ;clear CDPLC and AR[7-0]LC

      BSET	ARMS      ;set ARMS

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
      ||RET                      ;return to calling function

;----------------------------------------------------------------
;End of file
