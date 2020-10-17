;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    firinterp
; Processor:   C55xx
; Description: Interpolation filter with user specified FIR coefficients
;
;						Passing:
; Usage:   short firinterp(	DATA *x,	XAR0
;				DATA *h,	XAR1
;				DATA *r,	XAR2
;				DATA *dbuffer,	XAR3
;				ushort nh,	T0
;				ushort nx,	T1
;				ushort I);	XAR4
;
; Requirements:	I >= 1
;		nh/I >= 3
;		x[nx]
;		h[nh]
;		r[nx*I]
;		dbuffer[(nh/I)+1]
;			dbuffer[0] is ptr to last db entry
;			dbuffer[1..(nh/I)+1] is db data
; Copyright Texas instruments Inc, 2000
;****************************************************************

	.ARMS_off			;enable assembler for ARMS=0
	.CPL_on				;enable assembler for CPL=1
	.mmregs				;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ	.set	1		;return address
REG_SAVE_SZ	.set	0		;save-on-entry registers saved
FRAME_SZ	.set	0		;local variables
ARG_BLK_SZ	.set	0		;argument block

PARAM_OFFSET	.set	ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
	.asg	AR0, x_ptr		;linear pointer
	.asg	AR1, h_ptr		;circular pointer
	.asg	AR2, r_ptr		;linear pointer
	.asg	AR4, db_ptr		;circular pointer

	.asg	BSA01, h_base		;base addr for h_ptr
	.asg	BK03, h_sz		;circ buffer size for h_sz
	.asg	BSA45, db_base		;base addr for db_ptr
	.asg	XAR4, xdb_base		;extended base addr for db_ptr
	.asg	BK47, db_sz		;circ buffer size for db_ptr
	.asg	BK47_L, db_sz_L		;for memory mapped access
                                	
	.asg	CSR, inner_cnt		;inner loop count
	.asg	BRC0, outer_cnt		;outer loop count
	.asg	BRC1, mid_cnt		;outer loop count

	.asg	T0, oflag		;returned value
	.asg	T1, I			;interpolation factor

ST2mask	.set	0000000000010010b	;circular/linear pointers


	.global	_firinterp

	.text
_firinterp:

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
      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  
      PSH	mmap(ST3_55)

	AND	#01FFh,mmap(ST0_55)	;clear all ACOVx,TC1, TC2, C
	OR	#4140h,mmap(ST1_55)	;set CPL, SXMD, FRCT
	AND	#0F9DFh,mmap(ST1_55)	;clear M40, SATD, 54CM 
	AND	#07A00h,mmap(ST2_55)	;clear ARMS, RDM, CDPLC, AR[0-7]LC
	AND	#0FFDDh,mmap(ST3_55)	;clear SATA, SMUL

;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
; Setup loop counts
;----------------------------------------------------------------

; outer loop count
	SUB	#1,T1
	MOV	T1,outer_cnt		;outer_cnt = nx-1

; x pointer - passed in its destination register, need do nothing

; h pointer
	MOV	mmap(AR1),h_base	;base address of coefficients
	MOV	#0,h_ptr		;point to first coefficient
	MOV	mmap(T0),h_sz		;coefficient array size h_sz = nh

; r pointer - already passed in its destination register

; db pointer
	MOV	AR4,I			;save I (interpolation factor)
	MOV	XAR3,xdb_base		;db array address
	MOV	*AR3+,db_ptr		;index of oldest db entry
	MOV	mmap(AR3),db_base	;base address for db_ptr

; Set circular/linear ARx behavior
	OR	#ST2mask,mmap(ST2_55)	;config circ/linear pointers

; Setup loop counts
	BCLR	SXM
	MOV	T0,AC0			;AC0 = nh
	||RPT	#(16-1)
	SUBC	mmap(I),AC0		;LO(AC0) = (nh/I)
	MOV	HI(AC0),mmap(T0)	;T0 = remainder of (nh/I)
	MOV	AC0,mmap(db_sz)		;db_sz = (nh/I)
	SUB	#3,AC0			;
	MOV	AC0,mmap(inner_cnt)	;inner_cnt = (nh/I)-3 (reload for FIR taps)
	ADD	mmap(I),T0		;
	ADD	#1,T0			;T0 = remainder+I+1 (last tap hptr update)
	BSET	SXM

	SUB	#1,I,T2			;T2 = I-1
	MOV	T2,mid_cnt		;mid_cnt = I-1	
	
	BCC	No_Interp, T3<0	
	
;
; Start of outer loop  I>=2
;----------------------------------------------------------------
	RPTBLOCAL	L1-1		;outer loop (nx iterations)
	
	;move next input value into delay buffer
	MOV	*x_ptr+,*db_ptr		

	||RPTBLOCAL	L2-1		;  middle loop (I iterations)
	 
	;Sum h*x (nh/I)-iterations (only non-zero) for next r value
	MPYM	*db_ptr+,*(h_ptr+I),AC0	;    inner loop (nh/I iterations)      
	||RPT	inner_cnt
	MACM	*db_ptr+,*(h_ptr+I),AC0,AC0
	MACMR	*db_ptr+,*(h_ptr+T0),AC0,AC0
	
	;store result to memory
	MOV	HI(AC0),*r_ptr+		;    store Q15 value to memory
L2:	
	;reset h_ptr
	AMAR	*(h_ptr-I)		;  h_ptr = &h[0]	
	
	;Point db_ptr to new entry
	||AMAR	*db_ptr-		;
L1:					;end of outer loop

	B	L3			;goto exit procedure
;
; Start of outer loop  I=1
;----------------------------------------------------------------
No_Interp:
	MOV	T2,inner_cnt		;inner_cnt = nh-3 (2 iter outside loop)
	RPTBLOCAL L3-1			;start the outer loop
	
	;move next input value into delay buffer
	MOV	*x_ptr+,*db_ptr		

	;Sum h*x nh-iterations for next r value
	MPYM	*db_ptr+,*h_ptr+,AC0      
	||RPT	inner_cnt
	MACM	*db_ptr+,*h_ptr+,AC0,AC0
	MACMR	*db_ptr,*h_ptr+,AC0,AC0

	;store result to memory
	MOV	HI(AC0),*r_ptr+		;store Q15 value to memory
L3:					;end of outer loop
	
;
; Update the db entry point
;----------------------------------------------------------------
	MOV db_ptr,*-AR3		;update 1st element of db array

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	||MOV #0,oflag			;clear oflag

	XCCPART overf_label, overflow(AC0) ;clears ACOV0
	||MOV #1,oflag			;overflow occurred
overf_label:

;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------
;	BCLR #ST1_FRCT,ST1_55		;clear FRCT
;	AND #0FE00h,mmap(ST2_55)	;clear CDPLC and AR[7-0]LC
;	BSET #ST2_ARMS,ST2_55		;set ARMS            

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
      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
      RET                         ;return to calling function

;----------------------------------------------------------------
;End of file
