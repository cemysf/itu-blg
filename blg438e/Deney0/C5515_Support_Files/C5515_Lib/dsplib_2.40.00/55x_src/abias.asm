;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;****************************************************************
; Function:    acorr_bias
; Processor:   C55xx
; Description: calculates positive biased auto-correlation
;
; Usage:    short acorr_bias(DATA *x, DATA *r, ushort nx, ushort nr)
;
; Copyright Texas instruments Inc, 2000
; History:
; - Modified save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
;   Li Yuan - 08/14/01
; 
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;   Zhengting He - 10/25/2006
;****************************************************************

	.ARMS_off                     ;enable assembler for ARMS=0
	.CPL_on                       ;enable assembler for CPL=1
	.mmregs                       ;enable mem mapped register names
	.global _acorr_bias
_acorr_bias

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
;REG_SAVE_SZ       .set 3            ;save-on-entry registers saved
REG_SAVE_SZ       .set 6            ;save-on-entry registers saved
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ
	.asg    0, temp
	.asg	1, n_inverse
	.asg    0 + FRAME_SZ, SAVE_AR5
	.asg    2 + FRAME_SZ, SAVE_AR6
	.asg    4 + FRAME_SZ, SAVE_AR7
	.asg    0 + FRAME_SZ + REG_SAVE_SZ, RETURN_ADDR
	
	.asg	AR0, x_ptr
	.asg	AR1, r_ptr
	.asg	XAR0, Xx_ptr
	.asg	XAR1, Xr_ptr
	.asg	DR0, nx
	.asg	DR1, nr
	
	.asg    AR2, counter
	.asg    AR3, x2_save
	.asg    XAR3, Xx2_save
	.asg	AR4, odd
	.asg	AR5, x_save
	.asg	XAR5, Xx_save
	.asg    AR6, loop_count
	.asg    AR7, xb_ptr
	.asg    XAR7, Xxb_ptr
	
    ;.asg	AC2, odd
    .asg	AC1, exec
	;.asg	AC3, B
	;.asg	AC0, A

        PSH	mmap(ST1_55)
	
;
; Allocate the local frame and argument block( +1 is for dbl alignment)
;----------------------------------------------------------------
	AADD	#-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ +1), SP 

;
; Save any save-on-entry registers that are used
; Configure the status registers as needed.
;----------------------------------------------------------------
    MOV	XAR7, dbl(*SP(#(SAVE_AR7)))	; PSHM    XAR7 
	||BSET	FRCT			; Set FRCT

	MOV	XAR6, dbl(*SP(#(SAVE_AR6)))	; PSHM    XAR6 
	||BSET	SXMD			; Set SXMD

	MOV	XAR5, dbl(*SP(#(SAVE_AR5)))	; PSHM    XAR5 
        
;
; Initialize some of the variables
;----------------------------------------------------------------
	||MOV	#0, exec

	MOV	nr, loop_count
	||MOV	#0, odd

	MOV	Xx_ptr, Xx_save

	MOV	Xx_ptr, Xx2_save
	MOV	nx, AC0
		
	SUB	#1, loop_count

;
; If the number of correlation elements to calculate is      
; exactly equal to na, then we want to calculate the last    
; 2 elements outside of the loop. Since loop assumes minimum 
; of 3 MAC operations                                        
;----------------------------------------------------------------
	||SUB	nr, AC0
	MOV	AC0, *sp(#(temp))
    
	CMP	*sp(#(temp)) == #1, TC1
	
	BCC	L0, !TC1
	
	SUB	#1, exec
	SUB	#1, loop_count
	||B	L1				  	

L0:
	CMP	*sp(#(temp)) == #0, TC1
	
	BCC	L1, !TC1
	SUB	#2, loop_count
	ADD	#1, exec

L1:

; ---- Prepare the scaling value ----
	MOV	#32767, AC0
	MOV	nx, *sp(#(temp))
	RPT	#15
	SUBC	*sp(#(temp)), AC0
	ADD	#1, AC0
	MOV	AC0, *sp(#(n_inverse))
	BSET	SXMD

; ---- If NR == #1, then we can't use the DUAL MAC loop ----
	MOV	nr, *sp(#(temp))
	CMP	*sp(#temp) == #1, TC1
	BCC	LOOP_SINGLE, TC1
	
; ---- ODD detection ----
; If we have an output buffer which is an odd number, then we need to 
; enable the extra mac which is outside of the main dual mac loop.
	BTST	@#0, nr, TC1	; Test to see if the LSB of NR is set. If 
				; it is, then we have an odd number
    .if  $isdefed("SI_BUGS")
	XCC	check1, TC1
	.else
	XCCPART	check1, TC1
	.endif
	MOV	#-1, odd	; Setup the odd flag for later use 

check1:

; Generic pointer and loop setup 
; 	Generic will be used by both normal dual mac and the odd 
;	numbered dual mac. 

	MOV	Xx_save, XCDP		; Setup CDP 	
	MOV	Xx2_save, Xx_ptr
	ADD	#1, x_ptr 
	MOV Xx_ptr,Xxb_ptr	; Setup the secondary pointer
    SUB	#1, x_ptr
 	SFTS	loop_count, #-1
    .if  $isdefed("SI_BUGS")
	XCC	check2, odd<#0		; This is only for the case where we have odd
	.else
	XCCPART	check2, odd<#0		; This is only for the case where we have odd
	.endif
	SUB	#1, loop_count		; sized input vectors. In this case we have

check2:					; moved one of the MACs out of the loop

	MOV	loop_count, BRC0
	
	MOV	nx, counter
 	SUB	#3, counter
	MOV	counter, CSR

;
; Perform correlation:                                       
;----------------------------------------------------------------
	
LOOP_DUAL:   
	RPTBLOCAL	loop1-1

; ---- Preload A ----
	MPY	*x_ptr+, *CDP+, AC0
	::MPY	*xb_ptr+, *CDP+, AC3

; ---- Main Dual MAC loop  ----
	RPTSUB	CSR, #2
	MAC	*x_ptr+, *CDP+, AC0
	::MAC	*xb_ptr+, *CDP+, AC3

; ---- Do one MAC for A, Load DR2 with B  ----
	MACM	*x_ptr, *CDP, AC0
	||MOV	HI(AC3), T2

; ---- Multiply B with inverse, Load DR3 with A  ----
	MPYMR	*sp(#(n_inverse)), T2, AC3
	||MOV	HI(AC0), T3

; ---- Multiply A with inverse, x2 incremented by to because of DUAL MAC ----
	MPYMR	*sp(#(n_inverse)), T3, AC0
	||ADD	#2, x2_save

; ---- Store A, reset CDP ----
	MOV	HI(AC0), *r_ptr+
	||MOV	x_save, CDP

; ---- Store B, reload x_pointer (used for A) with new x2_save ----
	MOV	HI(AC3), *r_ptr+
	||MOV	x2_save, x_ptr

; ---- Reload xb_ptr (used for B) with one more than x_ptr ----
	ADD	#1, x_ptr, xb_ptr		; Setup the secondary pointer
	
loop1:

	BCC	REGULAR, odd>=#0		; Goto REGULAR to regular if we 
						; didn't have the odd condition.
	
; ---- 3 -----
; If ODD, then we need to do the odd value outside of the MAC
; loop. Pointers CDP and x_ptr need to be restored at end
; of loop for following MAC instructions
	MPYM	*x_ptr+, *CDP+, AC0
	||ADD	#1, x2_save
	
	MACM	*x_ptr+, *CDP+, AC0	
	MACM	*x_ptr, *CDP, AC0

	MOV	HI(AC0), T3
	
	MPYMR	*sp(#(n_inverse)), T3, AC0
	||MOV	x_save, CDP
	
	MOV	HI(AC0), *r_ptr+
	||MOV	x2_save, x_ptr	


REGULAR:
	BCC	FINISH, exec == #0	; This is actually kinda redundant because we have the SINGLE detector now

; ---- 2 -----
	MPYM	*x_ptr+, *CDP+, AC0
	MACM	*x_ptr, *CDP-, AC0
	
	MOV	HI(AC0), T3
	MPYMR	*sp(#(n_inverse)), T3, AC0
	MOV	HI(AC0), *r_ptr+

	BCC	FINISH, exec < #0

; ---- 1 -----
	MPYM	*x_ptr, *CDP, AC0
	
	MOV	HI(AC0), T3
	MPYMR	*sp(#(n_inverse)), T3, AC0
	MOV	HI(AC0), *r_ptr+

FINISH:
; bug: original code put return value to AC0
; fix: put to T0
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	MOV	#0, T0			;clear oflag
	
	XCCPART	check3, overflow(AC0)	;clears ACOV0
	||MOV	#1, T0			;overflow occurred

check3:
	
	XCCPART	check4, overflow(AC3)	;clears ACOV1
	||MOV	#1, T0			;overflow occurred

check4:

;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------

	MOV	dbl(*SP(#(SAVE_AR7))), XAR7	; POPM    AR7

	BCLR	SXMD			; Clear SXMD
	||MOV	dbl(*SP(#(SAVE_AR6))), XAR6	; POPM    AR6

	BCLR	FRCT			; Clear FRCT
	||MOV	dbl(*SP(#(SAVE_AR5))), XAR5	; POPM    AR5


;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
	AADD	#(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ +1), SP

        POP	mmap(ST1_55)

;
; Return to calling function
;----------------------------------------------------------------
	RET			; RETD

;----------------------------------------------------------------
;End of file


LOOP_SINGLE:   
; This is only used if we have the case where it is a single 
; value to calculate. The dual MAC loop cannot be used here 
; because it would overwrite neighbouring values due to 
; the dual saves. A conditional save would be cycle costly
; to have in the DUAL MAC loop
;--------------------------------------------------

; ---- Pointer setup ----
	MOV	Xx_save, XCDP	; Setup CDP 	
	MOV	Xx2_save, Xx_ptr

; ---- Counter setup ----
	MOV	nx, counter
 	SUB	#3, counter
 	MOV	counter, CSR	; Because of the CSR updates, we need to preload CSR

; ---- Preload A ----
	MPYM	*x_ptr+, *CDP+, AC0
	
; ---- MAC ----
	RPT	CSR
	MACM	*x_ptr+, *CDP+, AC0	

; ---- Multiply by inverse ----
	MOV	HI(AC0), T3
	MPYMR	*sp(#(n_inverse)), T3, AC0
	
; ---- Save ----
	MOV	HI(AC0), *r_ptr+
	
	B	FINISH			; Branch back to cleanup routines
