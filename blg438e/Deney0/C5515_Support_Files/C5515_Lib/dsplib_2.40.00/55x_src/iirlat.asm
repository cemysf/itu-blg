;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;****************************************************************
; Function:    iirlat
; Processor:   C55xx
; Description: Computes a real lattice IIR filter implementation using 
;		coefficient stored in vector h. The real data input is 
;		stored in vector x. The filter output result is stored 
;		in vector r .  This function retains the address of the 
;		delay filter memory d containing the previous delayed 
;		values to allow consecutive processing of blocks. This 
;		function can be used for both block-by-block and  
;		sample-by-sample filtering (nx=1).    
;		C-callable.
;
; Useage: short oflag = iirlat (DATA *x, 
;				DATA *h, 
;				DATA *r, 
;				DATA *pbuffer, 
;				int nx, 
;				int nh)
; Copyright Texas instruments Inc, 2000
;****************************************************************
*;Algorithm:
*; 	e(nh)[n] = x[n]
*;	
*; 	e(i-1)[n]  = e(i)[n] + k(i)*e'(i-1)[n-1]   i=nh,nh-1,.. 1
*;       e'(i)[n] = k(i)*e(i-1)[n] + e'(i-1)[n-1]   i=nh,nh-1,.. 1
*;	r[n] = e(0)[n]=e'(0)[0]
*;
*;
*;pbuffer: procession buffer of nh length
*;      e'0[n-1]
*;      e'1[n-1]
*;      e'2[n-1]
*;      e'3[n-1]
*;	.
*;	.
*;      e'nh-2[n-1]
*;      e'nh-1[n-1]
*;
*;x: input of length nx
*;	x[0]
*;	x[1]
*;	.
*;	.
*;	.
*;	x[nx-2]
*;	x[nx-1]
*;
*;h: input of length nh-1 (zero pad 1st value)
*;	0
;	h[1]
;	.
;	.
;	.
;	h[nh-1]
;	h[nh]
;
;r: output of length nx
;	r[0]
;	r[1]
;	.
;	.
;	.
;	r[nx-2]
;	r[nx-1]  
;
;
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
      .asg     AR4, p_ptr           ;circular pointer
      .asg     AR3, temp	    ;temp buffer
	
       
      .asg     BSA45, p_base        ;base addr for p_ptr
      .asg     XAR4, xdb_base       ;extended base addr for p_ptr
      .asg     BK47, p_sz           ;circ buffer size for p_ptr
      .asg     BK47_L, p_sz_L       ;for memory mapped access
      .asg     BSA01, h_base        ;base addr for h_ptr
      .asg     BK03, h_sz           ;circ buffer size for h_sz

      .asg     BRC1, inner_cnt       ;inner loop count
      .asg     BRC0, outer_cnt      ;outer loop count

      .asg     T0, oflag           ;returned value

ST2mask  .set  0000000000010010b    ;circular/linear pointers, AR4, AR1 circular


      .global _iirlat

      .text
_iirlat:

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

; h pointer 
		
	MOV	mmap(AR1), h_base	;base address of coefficients
					; passed in AR1
    
	MOV	mmap(T1), h_sz		;h_sz = nh

; r pointer - passed in its destination register, need do nothing

; p pointer

	MOV XAR3, XAR4
  
	MOV	mmap(AR3), p_base	;base address for p_ptr
      
	MOV	mmap(T1), p_sz		;p_sz = nh


; Set circular/linear ARx behavior
	OR	#ST2mask, mmap(ST2_55)	;config circ/linear pointers

;
; Setup loop counts
;----------------------------------------------------------------
	SUB	#1, T0			;T0 = nx-1
	MOV	T0, outer_cnt		;outer loop executes nx times
	SUB	#2, T1, T0		;T0 = nh-2
	MOV	T0, inner_cnt		;inner loop executes nh-1 times
	SUB	#1, T1			; T1 = nh-1   
      
	MOV	mmap(T1), p_ptr		;point to last coefficient
            
	MOV	mmap(T1), h_ptr		;point to last coefficient
      
	MOV	#-1, T0		; setup offset register 
      
;
; Start of outer loop
;----------------------------------------------------------------
	RPTBLOCAL	loop1-1		;start the outer loop
	
;1st iteration
      
	MOV	*x_ptr+ << #16, AC0	; setup for e(0): input value
       
       
;inner loop
	||RPTBLOCAL	loop2-1
	MOV	*p_ptr(T0) <<#16, AC1	; setup for e'(0): input value
      
	MASM	*h_ptr, *p_ptr(T0), AC0	; calculate e(0)
	MACM	*h_ptr-, AC0, AC1		; calculate e'(0)
	MOV	HI(AC1), *p_ptr-		; store e'(i)
      		
loop2:      	     

;last iteration has rounding
      
	MACMR	*h_ptr-, *p_ptr(T0), AC0
     
      
	MOV	HI(AC0), *p_ptr-		; store previously cacluclated e'(i)
							
;store result to memory
	||MOV	HI(AC0), *r_ptr+		;store Q15 value to memory

loop1:						;end of outer loop

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
    .if  $isdefed("SI_BUGS")
	MOV	#0, oflag		;clear oflag
	XCC	check1, overflow(AC0)	;clears ACOV0
    .else
	MOV	#0, oflag		;clear oflag
	||XCCPART	check1, overflow(AC0)	;clears ACOV0
	.endif
	MOV	#1, oflag			;overflow occurred
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

      POP	mmap(ST3_55)

;
; Return to calling function
;----------------------------------------------------------------
	RET			;return to calling function

;----------------------------------------------------------------
;End of file
