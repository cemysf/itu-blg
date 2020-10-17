;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;****************************************************************
; Function:    corr_raw
; Processor:   C55xx
; Description: raw full length correlation of two vectors
;
;
; Usage: ushort corr_raw(DATA *x, DATA *r, ushort nx, ushort nr)
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
	.global _corr_raw
	.text
    
_corr_raw

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 6            ;save-on-entry registers saved
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ	
	.asg    "0 + FRAME_SZ", SAVE_AR6
	.asg    "2 + FRAME_SZ", SAVE_AR7
	.asg    "4 + FRAME_SZ", SAVE_AR5
	.asg    0 + REG_SAVE_SZ + FRAME_SZ, RETURN_ADDR
	.asg    0,	y_orig

	.asg	AR0, x_ptr
	.asg	XAR0, Xx_ptr
	.asg	AR1, y_ptr
	.asg	XAR1, Xy_ptr
	.asg	AR2, r_ptr
	.asg    AR3, mac_cnt
	.asg    AR4, x_save
	.asg    XAR4, Xx_save
	.asg    AR6, x2_save
	.asg    XAR6, Xx2_save
	.asg	AR5, y_save
	.asg	XAR5, Xy_save
	.asg    AR7, region1_and_3_loop_cnt

	.asg	T0, nx
	.asg	T1, ny
	
    .asg	AC2, odd
    
	.asg	AC1, B
	.asg	AC0, A
;	.asg    AC0, oflag           ;returned value
    .asg    T0, oflag   		; for C55, return value in T0, c54 in AC0
	
;
; Allocate the local frame and argument block( +1 is for dbl alignment)
;----------------------------------------------------------------
    PSH mmap(ST0_55)
    PSH mmap(ST1_55)
    PSH mmap(ST2_55)
    PSH mmap(ST3_55)
	AADD #-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ +1), SP

;
; Save any save-on-entry registers that are used
; Configure the status registers as needed.
;----------------------------------------------------------------
	MOV	XAR5, dbl(*SP(#(SAVE_AR5)))	; PSHM    XAR5 
	|| BSET #ST1_SXMD, ST1_55

	MOV	XAR6, dbl(*SP(#(SAVE_AR6)))	; PSHM    XAR6 
	|| BSET #ST1_FRCT, ST1_55
	
        MOV	XAR7, dbl(*SP(#(SAVE_AR7)))	; PSHM    XAR7 

;---------- X pointer setup    
; x_ptr		-	X pointer as passed
; x_save	-	X+nx
; x2_save	-	X
	MOV Xx_ptr, Xx2_save ;
	MOV Xx_ptr, Xx_save ;
	MOV x_ptr, A
	ADD nx, A
	MOV A, x_save
	
;---------- Y pointer setup    
; y_ptr		-	Y pointer as passed
; y_orig	-	Unchainged original Y pointer
	MOV Xy_ptr, Xy_save
	MOV Xy_ptr ,dbl(*sp(#(y_orig)))
	
; Initialize MAC cnt for regions 1 & 3, these will be          
; calculated in one loop, since the number of elements is the  
; same in each region.                                         
;----------------------------------------------------------------
	MOV nx, B
	SUB #4, B
;    region1_and_3_loop_cnt = B
	MOV B, region1_and_3_loop_cnt
	SUB #1, x_save

; ---- ODD detection ----
; Due to the Dual MAC, we need to know if the region 1 and region 3
; are odd or even in length. If the number is odd, then we will need
; to do an extra MAC outside of the loop.
;	TC1 = bit(region1_and_3_loop_cnt, @#0)	; Test to see if the LSB 
											; of NR is set. If it is, 
											; then we have an odd number
	BTST @#0, region1_and_3_loop_cnt, TC1
	; If !#0 (even), then we actually have an odd number of MAC's to 
	; do!
	MOV #0, odd
;	if (!TC1) execute(D_unit)
    .if  $isdefed("SI_BUGS")
	XCC temp000529, !TC1
	.else
	XCCPART temp000529, !TC1
	.endif
 	MOV #-1, odd            ; Setup the odd flag for later use 
temp000529:	
	
; Begin Region 1:                                      
;----------------------------------------------------------------
REGION1:
	MOV Xy_save, Xy_ptr
	MOV Xx_save, Xx_ptr
		
; For the dual MAC, we need to divide by two followed
; by a subsequent subtraction by 1 only if we have and odd number
; of MAC's to do. 
; 	region1_and_3_loop_cnt = region1_and_3_loop_cnt >> #1;
	SFTL region1_and_3_loop_cnt, #-1
;	if (odd<#0) execute(d_unit)								
    .if  $isdefed("SI_BUGS")
	XCC temp000529b, odd < #0
	.else
	XCCPART temp000529b, odd < #0
	.endif
	SUB #1, region1_and_3_loop_cnt
temp000529b:
    MOV region1_and_3_loop_cnt, BRC0
	MOV #0, mac_cnt             ; 2 cycles 

; Calculate first couple of elements outside of the loop     
; ---- 1 -----
	MPYMR *x_ptr, *y_ptr+, A
	MOV HI(A), *r_ptr+
	
; ---- 2 and Pointer stuff ----

	MPYM *x_ptr-, *y_ptr-, A || ADD #2, y_save

	MACMR *x_ptr, *y_ptr, A, A
	    
	MOV Xx_save, XCDP
	MOV Xy_save, Xx_ptr
	MOV Xx_ptr, Xy_ptr
	ADD #1, x_ptr, y_ptr    ; Setup the secondary point in case
						; we enter the Dual MAC	
	
	MOV HI(A), *r_ptr+
	
;If there is an even number, skip the extra MAC
	BCC REGION1_LOOP, odd == #0
	
; ---- 3 -----
REGION1_extra_mac:
	MPYM  *x_ptr-, *CDP-, A || ADD #1, y_save 

	MACM *x_ptr-, *CDP-, A
	
	MACMR *x_ptr-, *CDP-, A || MOV x_save, CDP
	
	MOV Xy_save, Xx_ptr
	MOV Xx_ptr, Xy_ptr
	ADD #1, x_ptr, y_ptr
	ADD #1, mac_cnt
	MOV mac_cnt, CSR
	MOV HI(A), *r_ptr+

REGION1_LOOP:
	
	RPTBLOCAL endlocal1
    ADD #2, y_save

; ---- Preload A ----
	MPY *x_ptr-, *CDP-, B :: MPY *y_ptr-, *CDP-, A
	
; ---- Main Dual MAC loop  ----        
	RPTADD CSR, #2
	MAC *x_ptr-, *CDP-, B :: MAC *y_ptr-, *CDP-, A

; ---- Cleanup MAC ----
	MACMR *x_ptr, *CDP, B
	MACM *y_ptr-, *CDP-, A
	MACMR *y_ptr-, *CDP-, A

; ---- Reload Pointers ----	
	MOV Xx_save, XCDP
	MOV Xy_save, Xx_ptr
	MOV Xx_ptr, Xy_ptr
	ADD #1, x_ptr, y_ptr

; ---- Store ----    
			MOV HI(B), *r_ptr+
endlocal1:	MOV HI(A), *r_ptr+

    

; ---- Reload Pointers ----	
	MOV dbl(*sp(#(y_orig))), Xy_save
	MOV Xx2_save, Xx_save

;
; Begin Loop for Region 2:                                      
;----------------------------------------------------------------
REGION2:
	MOV ny, A
	SUB nx, A
	  
	MOV A, DR3
	MOV DR3, BRC0

	MOV nx, mac_cnt
	
	MOV Xx_save, Xx_ptr
	SUB #3, mac_cnt
	MOV Xy_save, Xy_ptr

REGION2_LOOP:
	MOV mac_cnt, CSR
	RPTBLOCAL localend2
; ---- Setup pointers ----
	ADD #1, y_save
	
; ---- Preload A ----
	MPYM *x_ptr+, *y_ptr+, A
    
; ---- Main MAC loop  ---- 
;	MOV mac_cnt, CSR       ; moved out of loop for reduce cycle
	RPT CSR
	MACM *x_ptr+, *y_ptr+, A, A

; ---- Cleanup ----
	MACMR *x_ptr+, *y_ptr+, A, A
	
; ---- Setup for subsequent passes through Region 2 ----     
	MOV Xx_save, Xx_ptr
	MOV Xy_save, Xy_ptr
	
; ---- Store ----      
localend2:	MOV HI(A), *r_ptr+

;
; Begin REGION3 loop:                                           
;----------------------------------------------------------------
REGION3:

	MOV region1_and_3_loop_cnt, BRC0
	MOV Xx_save, XCDP
	MOV Xy_save, Xx_ptr
	MOV Xx_ptr, Xy_ptr
	ADD #1, x_ptr, y_ptr

    ; We are re-loading mac_cnt to remove the dependency 
    ; from the region 2 setup code
	MOV nx, mac_cnt
	SUB #5, mac_cnt
	MOV mac_cnt, CSR
	
REGION3_LOOP:
	RPTBLOCAL localend3
	ADD #2, y_save
	
; ---- Preload A ----
	MPY *x_ptr+, *CDP+, B :: MPY *y_ptr+, *CDP+, A
   
; ---- Main Dual MAC loop  ----        
	RPTSUB CSR, #2
	MAC *x_ptr+, *CDP+, B :: MAC *y_ptr+, *CDP+, A
	
; ---- Cleanup MAC ----
	MACMR *y_ptr, *CDP, A
	MACM *x_ptr+, *CDP+, B
	MACMR *x_ptr, *CDP, B

; ---- Reload Pointers ----	
	MOV Xx_save, XCDP
	MOV Xy_save, Xx_ptr
	MOV Xx_ptr, Xy_ptr
	ADD #1, x_ptr, y_ptr
	
; ---- Store ----    
			MOV HI(B), *r_ptr+
localend3:	MOV HI(A), *r_ptr+

;
; Calculate last correlation elements outside of loop       
;----------------------------------------------------------------
	BCC REGION3_FINAL, odd == #0

; ---- 3 -----
	MPYM *x_ptr+, *CDP+, A || ADD #1, y_save
	
    MACM *x_ptr+, *CDP+, A
    MACMR *x_ptr, *CDP, A
    
	MOV Xx_save, XCDP
	MOV Xy_save, Xx_ptr
	MOV HI(A), *r_ptr+

; ---- 2 -----
REGION3_FINAL:
	MPYM *x_ptr+, *CDP+, A
	MACMR *x_ptr, *CDP-, A
	MOV HI(A), *r_ptr+

; ---- 1 -----
	MPYM *x_ptr, *CDP, A
	MOV HI(A), *r_ptr+
	
;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	MOV #0, oflag
	
    .if  $isdefed("SI_BUGS")
	XCC dummy1, overflow(A)
	.else
	XCCPART dummy1, overflow(A)
	.endif
; dummy1:  MOV #1, A			; bug! put in oflag
dummy1:  MOV #1, oflag 		; 
	
    .if  $isdefed("SI_BUGS")
	XCC dummy2, overflow(B)
	.else
	XCCPART dummy2, overflow(B)
	.endif
; dummy1:  MOV #1, A			; bug! put in oflag
dummy2:	MOV #1, oflag 

; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
	MOV	dbl(*SP(#(SAVE_AR7))), XAR7	; POPM    AR7
	|| BCLR #ST1_SATD, ST1_55
	
	MOV	dbl(*SP(#(SAVE_AR6))), XAR6	; POPM    AR6
	|| BCLR SATA
	
	MOV	dbl(*SP(#(SAVE_AR5))), XAR5	; POPM    AR5
	|| BCLR #ST1_FRCT, ST1_55	
      
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
	AADD #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ +1), SP
      POP mmap(ST3_55)
      POP mmap(ST2_55)
      POP mmap(ST1_55)
      POP mmap(ST0_55)
;
; Return to calling function
;----------------------------------------------------------------
	return ; RETD
;----------------------------------------------------------------
;End of file
