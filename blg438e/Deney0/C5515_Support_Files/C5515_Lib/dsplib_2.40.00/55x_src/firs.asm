;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    firs
; Processor:   C55xx
; Description: Implements symmetric finite impulse response
;              filter using FIRS approach.  C-callable.
;
; Useage: ushort oflag = firs(DATA *x,
;                             DATA *h,
;                             DATA *r,
;                             DATA *dbuffer,
;                             ushort nx,
;                             ushort nh2)
;
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
      .asg    AR0, x_ptr            ;linear pointer
      .asg    AR1, db_ptr1          ;circular pointer
      .asg    AR2, r_ptr            ;linear pointer
      .asg    AR3, db_ptr2          ;circular pointer
      .asg    CDP, h_ptr            ;circular pointer

      .asg    BSA01, db_base1       ;base addr for db_ptr1
      .asg    XAR1, xdb_base1       ;extended base addr for db_ptr1
      .asg    BSA23, db_base2       ;base addr for db_ptr2
      .asg    BK03, db_sz           ;circ buffer size for db_ptr1 and db_ptr2
      .asg    BSAC, h_base          ;base addr for h_ptr
      .asg    XCDP, xh_base         ;extended base addr for h_ptr
      .asg    BKC, h_sz             ;circ buffer size for h_sz

      .asg    CSR, inner_cnt        ;inner loop count
      .asg    BRC0, outer_cnt       ;outer loop count

      .asg    T0, oflag             ;returned value

ST2mask  .set  0000000100001010b    ;circular/linear pointers


      .global _firs

      .text
_firs:

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

	AND	#001FFh, mmap(ST0_55)

	OR	#04140h, mmap(ST1_55)
      
	AND	#0F9DFh, mmap(ST1_55)

	AND	#07A00h, mmap(ST2_55)
      
	AND	#0FFDDh, mmap(ST3_55)

;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer
	MOV	XAR1, xh_base
	MOV	#0, h_ptr

	MOV	mmap(AR1), h_base

	MOV	mmap(T1), h_sz

; r pointer - passed in its destination register, need do nothing

; db pointers, part 1 - must come before circ/linear ARx setup
	MOV	XAR3, XAR4
	MOV	XAR4, xdb_base1

	MOV	*AR4, db_ptr1

	MOV	*AR4+, db_ptr2
	||MOV	#1, AC0

	MOV	mmap(AR4), db_base1
	
	MOV	mmap(AR4), db_base2

; Set circular/linear ARx behavior
	OR	#ST2mask, mmap(ST2_55)

	ADD	mmap(T1) << #1, AC0

	MOV	mmap(AC0L), db_sz

; db pointers, part 2 - must come after circ/linear ARx setup
	AMAR	*db_ptr2-

;
; Setup loop counts
;----------------------------------------------------------------
	||SUB	#1, T0

	MOV	T0, outer_cnt
	||AMAR	*db_ptr2-

	SUB	#3, T1, T0
	MOV	T0, inner_cnt

;
; Compute last iteration input pointer offsets
;----------------------------------------------------------------
	MOV	T1, T0
	SUB	#2, T1
      
    MOV	*x_ptr+, *db_ptr1  
;
; Start of outer loop
;----------------------------------------------------------------
	||RPTBLOCAL	loop1-1

;clear AC0 and pre-load AC1 with the sum of the 1st and last inputs
	
	ADD	*db_ptr1+, *db_ptr2-, AC1

;inner loop
	||RPT	inner_cnt
	FIRSADD	*db_ptr1+, *db_ptr2-, *h_ptr+, AC1, AC0	

;2nd to last iteration has different pointer adjustment
	FIRSADD	*(db_ptr1-T0), *(db_ptr2+T1), *h_ptr+, AC1, AC0

;last iteration is a MAC with rounding
	MACMR	*h_ptr+, AC1, AC0

    MOV	*x_ptr+, *db_ptr1
    
;store result to memory
	MOV	HI(AC0), *r_ptr+	
    
    ||MOV	#0, AC0
    
loop1:

;
; Update the db entry point
;----------------------------------------------------------------
	MOV	db_ptr1, *-AR4

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	||MOV	#0, oflag		;clear oflag

	XCCPART	check1, overflow(AC0)	;clears ACOV0
	||MOV	#1, oflag		;overflow occurred

check1:

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
	BCLR	FRCT

	AND	#0FE00h, mmap(ST2_55)

	BSET	ARMS

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
	RET

;----------------------------------------------------------------
;End of file
