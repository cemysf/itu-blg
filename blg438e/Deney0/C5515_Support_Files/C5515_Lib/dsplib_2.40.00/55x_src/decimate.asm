;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    firdec
; Processor:   C55xx
; Description: Decimation filter with user specified FIR coefficients
;
;					
; Usage:   ushort firdec(DATA *x,	XAR0 
;			DATA *h,	XAR1 
;			DATA *r,	XAR2
;			DATA *dbuffer,	XAR3 
;			ushort nh,	T0 
;			ushort nx,	T1 
;			ushort D);	XAR4
;
; Copyright Texas instruments Inc, 2000
;****************************************************************

	.ARMS_off		;enable assembler for ARMS=0
	.CPL_on			;enable assembler for CPL=1
	.mmregs			;enable mem mapped register names

; Stack frame
; -----------
RET_ADDR_SZ	.set	1	;return address
REG_SAVE_SZ	.set	0	;save-on-entry registers saved
FRAME_SZ	.set	0	;local variables
ARG_BLK_SZ	.set	0	;argument block

PARAM_OFFSET	.set	ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Register usage
; --------------
	.asg	AR0, x_ptr	;linear pointer
	.asg	AR1, h_ptr	;circular pointer
	.asg	AR2, r_ptr	;linear pointer
	.asg	AR4, db_ptr	;circular pointer

	.asg	BSA01, h_base	;base addr for h_ptr
	.asg	BK03, h_sz	;circ buffer size for h_sz
	.asg	BSA45, db_base	;base addr for db_ptr
	.asg	XAR4, xdb_base	;extended base addr for db_ptr
	.asg	BK47, db_sz	;circ buffer size for db_ptr
	.asg	BK47_L, db_sz_L	;for memory mapped access

	.asg	CSR, inner_cnt	;inner loop count
	.asg	BRC0, outer_cnt	;outer loop count

	.asg	T0, oflag	;returned value
	.asg	T2, DecFac	;decimation factor

ST2mask	.set	0000000000010010b	;circular/linear pointers


	.global	_firdec

	.text
_firdec:

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

	PSH T2

	AND	#01FFh,mmap(ST0_55)	;clear all ACOVx,TC1, TC2, C
	OR	#4140h,mmap(ST1_55)	;set CPL, SXMD, FRCT
	AND	#0F9DFh,mmap(ST1_55)	;clear M40, SATD, 54CM 
	AND	#07A00h,mmap(ST2_55)	;clear ARMS, RDM, CDPLC, AR[0-7]LC
	AND	#0FFDDh,mmap(ST3_55)	;clear SATA, SMUL

;
; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; h pointer
	MOV	mmap(AR1),h_base	;base address of coefficients
	MOV	#0,h_ptr		;point to first coefficient
	MOV	mmap(T0),h_sz		;coefficient array size h_sz = nh

; r pointer - already passed in its destination register

; db pointer
	MOV	AR4,DecFac		;save DecFac = D
	MOV	XAR3,xdb_base		;db array address
	MOV	*AR3+,db_ptr		;index of oldest db entry
	MOV	mmap(AR3),db_base	;base address for db_ptr

	MOV	mmap(T0),db_sz		;db_sz = nh
	;?ADD #1,mmap(db_sz)		;db_sz = nh+1

; Set circular/linear ARx behavior
	OR	#ST2mask,mmap(ST2_55)	;config circ/linear pointers

;
; Setup loop counts
;----------------------------------------------------------------
	BCLR	SXM
	MOV	T1,AC0			;AC0 = nx
	||RPT	#(16-1)
	SUBC	mmap(DecFac),AC0		
	SUB	#1,AC0			;
	MOV	AC0,mmap(outer_cnt)	;outer_cnt = (nx/D)-1
	BSET	SXM
	
	SUB	#3,T0			;setup reload for FIR taps inner_cnt = nh-3
	SUB	#2,DecFac		;setup reload for sample-to-db inner_cnt = D-2
	
	BCC	No_Decim, DecFac<0	
	
;
; Start of outer loop  D>=2
;----------------------------------------------------------------
	RPTBLOCAL	L1-1		;outer loop (nx/D) iterations
	
	;move next input value into delay buffer
	MOV	T0,inner_cnt		;inner_cnt = nh-3 (2 iter outside loop)
	||MOV	*x_ptr+,*db_ptr		

	;Sum h*x nh-iterations for next r value
	MPYM	*db_ptr+,*h_ptr+,AC0      
	||RPT	inner_cnt
	MACM	*db_ptr+,*h_ptr+,AC0,AC0
	MACMR	*db_ptr,*h_ptr+,AC0,AC0

	;store result to memory
	||MOV	DecFac,inner_cnt	;inner_cnt = D-2
	MOV	HI(AC0),*r_ptr+		;store Q15 value to memory
	
	;Move next D-1 input samples into delay buffer
	||RPT	inner_cnt
	MOV	*x_ptr+,*db_ptr-
L1:					;end of outer loop

	B	L2			;goto exit procedure
;
; Start of outer loop  D=1
;----------------------------------------------------------------
No_Decim:
	MOV	T0,inner_cnt		;inner_cnt = nh-3 (2 iter outside loop)
	RPTBLOCAL	L2-1		;start the outer loop
	
	;move next input value into delay buffer
	MOV	*x_ptr+,*db_ptr		

	;Sum h*x nh-iterations for next r value
	MPYM	*db_ptr+,*h_ptr+,AC0      
	||RPT	inner_cnt
	MACM	*db_ptr+,*h_ptr+,AC0,AC0
	MACMR	*db_ptr,*h_ptr+,AC0,AC0

	;store result to memory
	MOV	HI(AC0),*r_ptr+		;store Q15 value to memory
L2:					;end of outer loop
	
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
;	;BSET #ST1_FRCT,ST1_55		;set FRCT            

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
      POP T2
      POP   mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
      RET                         ;return to calling function

;----------------------------------------------------------------
;End of file
