;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;****************************************************************
; Function:    corr_bias
; Processor:   C55xx
; Description: biased full length correlation of two vectors
;
; Useage: ushort corr_raw(DATA *x, DATA *r, ushort nx, ushort nr)
; Copyright Texas instruments Inc, 2000
; History:
; - Changed save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
;   Li Yuan - 08/14/01
;
; - Added overflow checking and overflow is returned in T0 instead of 
;   AC0 register
;   Zhengting He - 10/25/2006
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names
	.global _corr_bias
_corr_bias

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
;REG_SAVE_SZ       .set 3            ;save-on-entry registers saved
REG_SAVE_SZ       .set 6            ;save-on-entry registers saved
FRAME_SZ          .set 5            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------
	

PARAM_OFFSET    .set  FRAME_SZ + REG_SAVE_SZ	
	.asg    0, temp
	.asg    1, n_inverse
	.asg    3, y_orig
	.asg    "0 + FRAME_SZ", SAVE_AR6
	.asg    "2 + FRAME_SZ", SAVE_AR7
	.asg    "4 + FRAME_SZ", SAVE_AR5
	.asg    "0 + REG_SAVE_SZ + FRAME_SZ", RETURN_ADDR
	
	.asg    AR3, mac_cnt
	.asg    AR4, x_save
	.asg    AR6, x2_save
	.asg	AR5, y_save    
	.asg    AR7, region1_and_3_loop_cnt
	.asg    XAR4, Xx_save
	.asg    XAR6, Xx2_save
	.asg	XAR5, Xy_save
	
	.asg	AR0, x_ptr
	.asg	AR1, y_ptr
	.asg	AR2, r_ptr
	.asg	XAR0, Xx_ptr
	.asg	XAR1, Xy_ptr
	.asg	XAR2, Xr_ptr
	
	.asg	DR0, nx
	.asg	DR1, ny
	
    .asg	AC2, odd
    
	.asg	AC1, B
	.asg	AC0, A
; bug: original return value in AC0
; fix: put in T0
	.asg    T0, oflag           ;returned value
	
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

        MOV	XAR7, dbl(*SP(#(SAVE_AR7)))	; PSHM    XAR7 
	|| BSET #ST1_FRCT, ST1_55
	
	MOV	XAR6, dbl(*SP(#(SAVE_AR6)))	; PSHM    XAR6 

;---------- X pointer setup    
; x_ptr		-	X pointer as passed
; x_save	-	X+nx
; x2_save	-	Unchanged original X pointer
	MOV Xx_ptr, Xx2_save
	MOV Xx_ptr, A
	ADD nx, A
	MOV A, Xx_save
;
; Calculate inverse of number of MACs  = nx                 
; We load Q15 equivalent of 1 into accumulator and use SUBC 
; Thus calculating Q15 equivalent of 1/N                    
;----------------------------------------------------------------
	MOV #32767, A
	
	MOV nx, *sp(#(temp))
	
	RPT #15
	SUBC *sp(#(temp)), A, A
	
	ADD #1, A
    MOV A, *sp(#(n_inverse))
 
	BSET #ST1_SXMD, ST1_55
 	
;---------- Y pointer setup    
; y_ptr		-	Y pointer as passed
; y_orig		-	Unchainged original Y pointer
	MOV Xy_ptr, Xy_save
	MOV Xy_ptr, dbl(*sp(#(y_orig)))  ; 

    MOV	XAR5, dbl(*SP(#(SAVE_AR5)))	
;
; Initialize MAC cnt for regions 1 & 3, these will be          
; calculated in one loop, since the number of elements is the  
; same in each region.                                         
;----------------------------------------------------------------
	MOV nx, B
	SUB #4, B
	MOV B, region1_and_3_loop_cnt
	SUB #1, x_save

; ---- ODD detection ----
; Due to the Dual MAC, we need to know if the region 1 and region 3
; are odd or even in length. If the number is odd, then we will need
; to do an extra MAC outside of the loop.
	BTST @#0, region1_and_3_loop_cnt, TC1
	MOV #0, odd
    .if  $isdefed("SI_BUGS")
	XCC temp000529, !TC1
	.else
	XCCPART temp000529, !TC1
	.endif
	MOV #-1, odd
temp000529: 

;        
; Initial lag is in region 1, load initial MAC count and      
; number of elements to calculate in region 1                 
;----------------------------------------------------------------

REGION1:
; ---- Pointer setup -----
	MOV y_save, y_ptr
	MOV x_save, x_ptr
	
; ---- Initialize BRC and mac_cnt -----
	SFTL region1_and_3_loop_cnt, #-1
    .if  $isdefed("SI_BUGS")
	XCC temp000529b, odd < #0
	.else
	XCCPART temp000529b, odd < #0
	.endif
	SUB #1, region1_and_3_loop_cnt
temp000529b:
    MOV region1_and_3_loop_cnt, BRC0
        
	MOV #0, mac_cnt
		
	MPY *x_ptr, *y_ptr+, A
	MPYMR *sp(#(n_inverse)), A, A
	MOV HI(A), *r_ptr+

; ---- 2 -----	
	MPYM *x_ptr-, *y_ptr-, A 
	MAC *x_ptr, *y_ptr, A
	MPYMR *sp(#(n_inverse)), A, A
	MOV HI(A), *r_ptr+    

; ---- Pointer stuff ----	           
	ADD #2, y_save
	MOV x_save, CDP
	MOV y_save, x_ptr
	ADD #1, x_ptr, y_ptr
						
	BCC REGION1_LOOP, odd == #0

; ---- 3 -----	
REGION1_extra_mac:
	MPYM  *x_ptr-, *CDP-, A
	MACM *x_ptr-, *CDP-, A
	MACM *x_ptr-, *CDP-, A
	
	MPYMR *sp(#(n_inverse)), A, A
	
	MOV HI(A), *r_ptr+
	
	ADD #1, y_save
	MOV Xx_save, XCDP

	MOV Xy_save, Xx_ptr
	ADD #1, x_ptr, y_ptr
	ADD #2, mac_cnt

REGION1_LOOP:
	MOV mac_cnt, CSR

	RPTBLOCAL endlocal1
    ADD #2, y_save
    
	MPY *x_ptr-, *CDP-, A :: MPY *y_ptr-, *CDP-, B
	
; ---- Main Dual MAC loop  ----   
	RPTADD CSR, #2
	MAC *x_ptr-, *CDP-, A :: MAC *y_ptr-, *CDP-, B
	
; ---- Cleanup MAC ----
	MACM *y_ptr-, *CDP-, B
	
; ---- Reload Pointers ----	
	MOV x_save, CDP
	MOV y_save, x_ptr
	ADD #1, x_ptr, y_ptr

; ---- BIAS A and B  ----
	MPYMR *sp(#(n_inverse)), A, A
	MPYMR *sp(#(n_inverse)), B, B

; ---- Store ----    
			MOV HI(A), *r_ptr+
endlocal1:	MOV HI(B), *r_ptr+ 

; ---- Reload Pointers ----	
	MOV dbl(*sp(#(y_orig))), Xy_save
	MOV x2_save, x_save

;
; Begin Loop for Region 2:                                      
;----------------------------------------------------------------

REGION2:
	MOV ny, A
	SUB nx, A
  
	MOV A, DR3
	MOV DR3, BRC0
    
	MOV nx, mac_cnt
	
	MOV x_save, x_ptr
	SUB #3, mac_cnt
	MOV y_save, y_ptr

REGION2_LOOP:
	MOV mac_cnt, CSR
	RPTBLOCAL localend2
	
; ---- Setup pointers ----
	ADD #1, y_save

; ---- Preload A ----
	MPYM *x_ptr+, *y_ptr+, A
	
; ---- Main MAC loop  ---- 
;	MOV mac_cnt, CSR
	RPT CSR
	MACM *x_ptr+, *y_ptr+, A, A	
	
; ---- Cleanup ----
	MACM *x_ptr+, *y_ptr+, A, A	
	MPYMR *sp(#(n_inverse)), A, A
	
; ---- Setup for subsequent passes through Region 2 ----     
	MOV x_save, x_ptr
	MOV y_save, y_ptr

; ---- Store ----      
localend2:	MOV HI(A), *r_ptr+

;
; Begin REGION3 loop:                                           
;----------------------------------------------------------------

REGION3:

	MOV region1_and_3_loop_cnt, BRC0
	MOV x_save, CDP
	MOV y_save, x_ptr
	ADD #1, x_ptr, y_ptr

	MOV nx, mac_cnt
	SUB #4, mac_cnt
	MOV mac_cnt, CSR


REGION3_LOOP:
	RPTBLOCAL localend3
	ADD #2, y_save

; ---- Preload A ----
	MPY *x_ptr+, *CDP+, A :: MPY *y_ptr+, *CDP+, B

; ---- Main Dual MAC loop  ----   
	RPTSUB CSR, #2
	MAC *x_ptr+, *CDP+, A :: MAC *y_ptr+, *CDP+, B

; ---- Cleanup ----     
	MACM *x_ptr, *CDP, A
	
; ---- Setup Pointers ----    
	MOV x_save, CDP
	MOV y_save, x_ptr
	ADD #1, x_ptr, y_ptr
	
; ---- BIAS A and B  ----
	MPYMR *sp(#(n_inverse)), A, A
	MPYMR *sp(#(n_inverse)), B, B
	
; ---- Store ----    
			MOV HI(A), *r_ptr+
localend3:	MOV HI(B), *r_ptr+ 
;	}

;
; Calculate last correlation elements outside of loop       
;----------------------------------------------------------------
	BCC REGION3_FINAL, odd == #0

; ---- 3 -----
	MPYM  *x_ptr+, *CDP+, A
	MACM *x_ptr+, *CDP+, A
	MACM *x_ptr+, *CDP+, A

	MPYMR *sp(#(n_inverse)), A, A
	
	MOV HI(A), *r_ptr+
	
	ADD #1, y_save
	MOV x_save, CDP
	MOV y_save, x_ptr
     
REGION3_FINAL:
; ---- 2 -----
	MPYM  *x_ptr+, *CDP+, A
	MACM *x_ptr, *CDP-, A
	MPYMR *sp(#(n_inverse)), A, A
	MOV HI(A), *r_ptr+    

; ---- 1 -----
	MPYM  *x_ptr, *CDP, A
	MPYMR *sp(#(n_inverse)), A, A
	MOV HI(A), *r_ptr+    

; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
; bug: original code put return value in A
; fix: put in oflag
	MOV #0, oflag
	
    .if  $isdefed("SI_BUGS")
	XCC dummy1, overflow(A)
	.else
	XCCPART dummy1, overflow(A)
	.endif
dummy1:  MOV #1, oflag
	
    .if  $isdefed("SI_BUGS")
	XCC dummy2, overflow(B)
	.else
	XCCPART dummy2, overflow(B)
	.endif
dummy2:	MOV #1, oflag
;                
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
	MOV	dbl(*SP(#(SAVE_AR7))), XAR7	; POPM    AR7
	
	MOV	dbl(*SP(#(SAVE_AR6))), XAR6	; POPM    AR6

	MOV	dbl(*SP(#(SAVE_AR5))), XAR5	; POPM    AR5

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


