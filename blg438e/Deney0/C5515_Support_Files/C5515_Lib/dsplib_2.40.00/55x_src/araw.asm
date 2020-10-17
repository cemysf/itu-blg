;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    acorr_raw
; Version:     2.0
; Processor:   C55xx
; Description: calculates raw auto-correlation
; Usage:    short acorr_raw(DATA *x, DATA *r, ushort nx, ushort nr)
; Copyright Texas instruments Inc, 2000
; History:
; - Changed save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
; - Fixed XARx init bug (added Xx_ptr,Xx_save,Xx2_save,Xxb_ptr).
;   Li Yuan - 08/14/01
;
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;   Zhengting He - 10/25/2006
;****************************************************************

	.ARMS_off                     ;enable assembler for ARMS=0
	.CPL_on                       ;enable assembler for CPL=1
	.mmregs                       ;enable mem mapped register names
	.global _acorr_raw
_acorr_raw

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
;REG_SAVE_SZ       .set 3            ;save-on-entry registers saved
REG_SAVE_SZ       .set 6            ;save-on-entry registers saved
FRAME_SZ          .set 1            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ
	.asg    0, temp
	.asg    0 + FRAME_SZ, SAVE_AR5
	.asg    2 + FRAME_SZ, SAVE_AR6
	.asg    4 + FRAME_SZ, SAVE_AR7
	.asg    0 + FRAME_SZ + REG_SAVE_SZ, RETURN_ADDR
	
	.asg	AR0, x_ptr
	.asg	XAR0, Xx_ptr
	.asg	AR1, r_ptr
	.asg	DR0, nx
	.asg	DR1, nr

	.asg    AR2, counter
	.asg    AR3, x2_save
	.asg    XAR3, Xx2_save
	.asg	AR4, odd
	.asg	AR5, x_save
	.asg	XAR5, Xx_save
	.asg    AR6, loop_count
	.asg	AR7, xb_ptr
	.asg	XAR7, Xxb_ptr

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
	||BSET	SXMD			; Set SXMD

	MOV	XAR6, dbl(*SP(#(SAVE_AR6)))	; PSHM    XAR6
	||BSET	FRCT			; Set FRCT

	MOV	XAR5, dbl(*SP(#(SAVE_AR5)))	; PSHM    XAR5 

;
; Initialize some of the variables
;----------------------------------------------------------------
	MOV	#0, exec			
	||MOV	nr, loop_count

	MOV	nr, AC3
	MOV	Xx_ptr, Xx_save

	MOV	Xx_ptr, Xx2_save
	SUB	#1, AC3

	MOV	nx, AC0
	BCC	LOOP_SINGLE, AC3 == #0		; We can't use dual MAC for
									; nr==#1
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
	MOV	Xx_save, XCDP		; Setup CDP 	
	
	MOV	x2_save, x_ptr
	MOV Xx_ptr, Xxb_ptr
	ADD	#1, x_ptr, xb_ptr	; Setup the secondary pointer

	SFTS	loop_count, #-1
	MOV	loop_count, BRC0
      
	MOV	nx, counter
 	SUB	#4, counter		; Changed to 4 from 3 because we want to
 					; try for the dual MAC.
	MOV	counter, CSR		; Because of the CSR updates, we need to preload CSR

;
; Perform correlation:                                       
;----------------------------------------------------------------
LOOP_DUAL:   
	RPTBLOCAL	loop1-1

; ---- Preload ----
	MPY	*x_ptr+, *CDP+, AC0
	::MPY	*xb_ptr+, *CDP+, AC3
	||ADD	#2, x2_save

; ---- Main Dual MAC loop  ----
	RPTSUB	CSR, #2
	MAC	*x_ptr+, *CDP+, AC0
	::MAC	*xb_ptr+, *CDP+, AC3
    
; ---- Do one MAC for A, and final MAC for B  ----
	MACMR	*xb_ptr, *CDP, AC3	;Create the B result
	MACM	*x_ptr+, *CDP+, AC0
	
; ---- Final MAC for A  ----
	MACMR	*x_ptr, *CDP, AC0	;Create the A result
	||AMOV	x2_save, x_ptr		; x_ptr = x2_save
    
; ---- Store A, reset CDP ----
	MOV	HI(AC0), *r_ptr+
	||MOV	x_save, CDP

; ---- Store B, reload x_pointer (used for A) with new x2_save ----
	MOV	HI(AC3), *r_ptr+
	||AMOV	x2_save, xb_ptr

; ---- Reload xb_ptr (used for B) with one more than x_ptr ----
	AMAR	*xb_ptr+		;xb_ptr = x_ptr + #1 ; Setup the secondary pointer
	
loop1:

	BCC	FINISH, exec == #0

; ---- 2 -----
	MPYM	*x_ptr+, *CDP+, AC0
	MACMR	*x_ptr, *CDP-, AC0

	MOV	HI(AC0), *r_ptr+

	BCC	FINISH, exec < #0

; ---- 1 -----
	MPYMR	*x_ptr, *CDP, AC0

	MOV	HI(AC0), *r_ptr+

FINISH:
; bug: return value originally in AC0
; put to T0
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	MOv	#0, T0			;clear oflag
	
	XCCPART	check1, overflow(AC0)	;clears ACOV0
	||MOV	#1, T0                 ;overflow occurred
	
check1:

	XCCPARt	check2, overflow(AC3)	;clears ACOV1
	||MOV	#1, T0			;overflow occurred

;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
	BCLR	SXMD			; Clear SXMD
	||MOV	dbl(*SP(#(SAVE_AR7))), XAR7	; POPM    AR7

	BCLR	FRCT			; Clear FRCT
	||MOV	dbl(*SP(#(SAVE_AR6))), XAR6	; POPM    AR6

	MOV	dbl(*SP(#(SAVE_AR5))), XAR5	; POPM    AR5

;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
	AADD	#(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ +1), SP

     POP	mmap(ST1_55)

;
; Return to calling function
;----------------------------------------------------------------
	RET	; RETD
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
	MOV	x_save, CDP		; Setup CDP 	
	MOV	x2_save, x_ptr

; ---- Counter setup ----
	MOV	nx, counter
 	SUB	#3, counter
	MOV	counter, CSR		; Because of the CSR updates, we need to preload CSR

; ---- Preload A ----
	MPYM	*x_ptr+, *CDP+, AC0

; ---- MAC ----		
	RPT	CSR
	MACM	*x_ptr+, *CDP+, AC0	

	MACMR	*x_ptr, *CDP, AC0	;Create the A result

; ---- Save ----
	MOV	HI(AC0), *r_ptr+
	
	B	FINISH	; Branch back to cleanup routines
