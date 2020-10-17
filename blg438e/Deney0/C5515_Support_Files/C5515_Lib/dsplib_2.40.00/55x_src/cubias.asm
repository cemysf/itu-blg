;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;****************************************************************
; Function:    corr_unbias
; Description: unbiased full length correlation of two vectors
; Processor:   C55xx
;
; Useage: ushort corr_raw(DATA *x, DATA *r, ushort nx, ushort nr)
; Copyright Texas instruments Inc, 2000
;
; History:
; - Modified save and restore AR5/AR6/AR7 to XAR5/XAR6/XAR7 registers.
;   Li Yuan - 08/14/01
;****************************************************************

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names
	.global _corr_unbias
_corr_unbias

; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
;REG_SAVE_SZ       .set 3            ;save-on-entry registers saved
REG_SAVE_SZ       .set 6            ;save-on-entry registers saved
FRAME_SZ          .set 8            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

; Register usage
; --------------
PARAM_OFFSET    .set   REG_SAVE_SZ + FRAME_SZ

	.asg    0, temp
	.asg    1, x_orig
	.asg    3, y_orig
	.asg    5, r_orig
	
	.asg    "0 + FRAME_SZ", SAVE_AR6
	.asg    "2 + FRAME_SZ", SAVE_AR7
	.asg    "4 + FRAME_SZ", SAVE_AR5
	.asg    "0 + REG_SAVE_SZ + FRAME_SZ", RETURN_ADDR

	.asg	AR0, x_ptr
	.asg	XAR0, Xx_ptr	
	.asg	AR1, y_ptr
	.asg	XAR1, Xy_ptr
	.asg	AR2, r_ptr
	.asg	XAR2, Xr_ptr
	.asg    AR3, mac_cnt
	.asg    AR4, x_save
	.asg    XAR4, Xx_save
	.asg	AR5, y_save
	.asg	XAR5, Xy_save	
	.asg	AR6, r1_r3_count
	.asg    AR7, r2_ptr
	.asg    XAR7, Xr2_ptr
	
	.asg	T0, nx
	.asg	T1, ny
	
    .asg	AC2, odd
	.asg	AC3, mytemp
	.asg	AC1, B
	.asg	AC0, A
	.asg    AC0, oflag           ;returned value

	
;
; Allocate the local frame and argument block
;----------------------------------------------------------------
        PSH mmap(ST0_55)	
        PSH mmap(ST1_55)	
        PSH mmap(ST2_55)	
        PSH mmap(ST3_55)	
	AADD #-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP

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
; x_save	-	Used extensively in Region 3 and Region 2
; x_orig	-	Unchanged original X pointer
	MOV Xx_ptr, dbl(*sp(#(x_orig)))
	ADD nx, x_ptr
	SUB #1, x_ptr
	MOV Xx_ptr, Xx_save
  
;---------- Y pointer setup    
; y_ptr		-	Y pointer as passed
; y_save	-	Y+nx-2 and Y+nx-1 in Region 3
; y_orig		-	Unchainged original Y pointer
    MOV Xy_ptr, dbl(*sp(#(y_orig)))
	MOV y_ptr, A
	ADD nx, A
	SUB #2, A
	MOV Xy_ptr, Xy_save
	MOV A, y_save

;---------- R pointer setup    
; r_ptr		-	R pointer as passed. Eventually used and initialized as r+nx-2
; r2_ptr	-	r+ny
; r_orig	-	Unchainged original Y pointer
	MOV Xr_ptr,dbl( *sp(#(r_orig)))
	MOV r_ptr, A
	MOV r_ptr, B
	ADD nx, B
	SUB #2, B
	MOV B, r_ptr
	|| ADD ny, A
	MOV Xr_ptr, Xr2_ptr
	MOV A, r2_ptr

;
; Initialize MAC cnt for regions 1 & 3, these will be          
; calculated in one loop, since the number of elements is the  
; same in each region.                                         
;----------------------------------------------------------------
	|| MOV nx, B
	MOV nx, A
	SUB #4, B
	SUB #1, A
	|| MOV B, mac_cnt
	MOV B, r1_r3_count


;+++++++++++ BIAS Calculator +++++++++++++++
; Upon entry:
; r_ptr	=	r+nx-2
; r2_ptr	=	r+ny
; mac_cnt	=	nx-4
; temp		=	nx-1
	;Setup BRC for localrepeat
;	BRC0 = mac_cnt
	;Setup n_mac
;	|| *sp(#(temp)) = A
	MOV mac_cnt, BRC0 || MOV A, *sp(#(temp))
		
	; Clear SXMD
;	bit(ST1,#ST1_SXMD) = #0	; Clear SXMD
	BCLR #ST1_SXMD, ST1_55
		
	RPTBLOCAL biascalclocalend
	
	;Compute bias value
	MOV #32767, A || RPT #15
    
    SUBC *sp(#(temp)), A, A
    
	; Adjust the temp value
	ADD #-1, *sp(#(temp))
	
	;Store bias value twice into output array
					MOV A, *r_ptr-
biascalclocalend:	MOV A, *r2_ptr+
	
	; Setup SXMD
	BSET #ST1_SXMD, ST1_55
			
;+++++++++++ End of BIAS calculator +++++++++++++++

; ---- ODD detection ----
; Due to the Dual MAC, we need to know if the region 1 and region 3
; are odd or even in length. If the number is odd, then we will need
; to do an extra MAC outside of the loop.
	BTST @#0, r1_r3_count, TC1
	MOV #0, odd
    .if  $isdefed("SI_BUGS")
	XCC temp000529, !TC1
	.else
	XCCPART temp000529, !TC1
	.endif
	MOV #-1, odd
temp000529: 

; For the dual MAC, we need to divide by two followed
; by a subsequent subtraction by 1 only if we have and odd number
; of MAC's to do. 
; 	r1_r3_count = r1_r3_count >> #1;
;	|| if (odd<#0) execute(d_unit)								
;		r1_r3_count = r1_r3_count - #1
;   BRC0 = r1_r3_count

	SFTL r1_r3_count, #-1
    .if  $isdefed("SI_BUGS")
	XCC temp000529b, odd < #0
	.else
	XCCPART temp000529b, odd < #0
	.endif
	SUB #1, r1_r3_count
temp000529b:
    MOV r1_r3_count, BRC0

	|| MOV nx, B
	SUB #4, B
	MOV B, mac_cnt
	
    
; Initial lag is in region 1, load initial MAC count and      
; number of elements to calculate in region 1                 
;----------------------------------------------------------------

REGION1_AND_3:

; ---- Pointer Setup ----
	MOV Xy_save, Xy_ptr
	MOV Xy_ptr, Xx_ptr
	SUB #1, y_ptr, x_ptr
	MOV Xx_save, XCDP
	    
	;Reset r_ptr to initial values
	MOV dbl(*sp(#(r_orig))), B
	ADD nx, B
	SUB #2, B
	MOV B, Xr_ptr

;--------- Calculate sum in region 1  
	MOV mac_cnt, CSR

	RPTBLOCAL endlocal1
    SUB #2, y_save
    
; ---- Preload A ----
	MPY *x_ptr-, *CDP-, A :: MPY *y_ptr-, *CDP-, B
	
; ---- Main Dual MAC loop  ---- 	
	RPTSUB CSR, #2
	MAC *x_ptr-, *CDP-, A :: MAC *y_ptr-, *CDP-, B
		
; ---- Cleanup MAC ----
    MACM *y_ptr-, *CDP-, B
    MOV Xx_save, XCDP
    
; ---- BIAS A and B and Store ----	
	MPYMR *r_ptr, B, B
	MOV Xy_save, Xy_ptr
	
	MOV Xy_ptr, Xx_ptr
	SUB #1, x_ptr
	MOV HI(B), *r_ptr-
	MPYMR *r_ptr, A, A
endlocal1:	MOV HI(A), *r_ptr-
; ---- Setup for Region 1 ----       

;---------- Calculate some MAC's outside of the loop
	BCC REGION1_FINAL, odd == #0
	
; ---- 3 -----	
	MPYM *y_ptr-, *CDP-, A
	MACM *y_ptr-, *CDP-, A
	MACM *y_ptr, *CDP, A
	
	; BIAS
	MPYMR *r_ptr, A, A	
	
	MOV HI(A), *r_ptr-
	
	; Setup pointers for next loop
	SUB #1, y_save
	MOV Xx_save, XCDP
	MOV Xy_save, Xy_ptr


; ---- 2 -----	
REGION1_FINAL:
	MPYM *y_ptr-, *CDP-, A
	MACMR *y_ptr, *CDP+, A
	MOV HI(A << #-1), *r_ptr-

; ---- 1 -----	
	MPYM *y_ptr, *CDP, A
	MOV HI(A), *r_ptr-

;--------- Calculate sum in region 3                              
	MOV r1_r3_count, BRC0
	MOV mac_cnt, CSR

; ---- Pointer Setup ----
	MOV dbl(*sp(#(y_orig))), B
	ADD ny, B
	SUB #1, B
	MOV B, Xy_save
	MOV Xy_save, XCDP

	; Compute x_save=X+nx-2
	MOV dbl(*sp(#(x_orig))), Xx_save
	ADD nx, x_save
	SUB #2, x_save

	MOV Xx_save, Xy_ptr
	MOV Xy_ptr, Xx_ptr
	SUB #1, y_ptr, x_ptr
	
	;Reset r2_ptr to initial values
	MOV dbl(*sp(#(r_orig))), A
	ADD ny, A
	MOV A, Xr2_ptr

	RPTBLOCAL localend3
	SUB #2, x_save
	
; ---- Preload A ----
	MPY *x_ptr-, *CDP-, A :: MPY *y_ptr-, *CDP-, B
	
; ---- Main Dual MAC loop  ---- 	
	RPTSUB CSR, #2
	MAC *x_ptr-, *CDP-, A :: MAC *y_ptr-, *CDP-, B

; ---- Cleanup MAC ----
    MACM *y_ptr-, *CDP-, B
    MOV Xy_save, XCDP
        
; ---- BIAS A and B and Store ----	
	MPYMR *r2_ptr, B, B
    MOV Xx_save, Xy_ptr
	    
	MOV Xy_ptr, Xx_ptr
	SUB #1, x_ptr
	MOV HI(B), *r2_ptr+
	MPYMR *r2_ptr, A, A
localend3:	MOV HI(A), *r2_ptr+

; ---- Setup for Region 3 ----     

; ---- 3 -----	
	BCC REGION3_FINAL, odd == #0	
	
	; no need for division since the previous one did it for me already
	
	; MACs
	MPYM *y_ptr-, *CDP-, A
	MACM *y_ptr-, *CDP-, A
	MACM *y_ptr, *CDP, A
	
		
	; BIAS
	MPYMR *r2_ptr, A, A	
	
	MOV HI(A), *r2_ptr+
         
	; Setup pointers for next loop
	SUB #1, x_save
	MOV Xx_save, XCDP
	MOV Xy_save, Xy_ptr

; ---- 2 -----	
REGION3_FINAL:
	MPYM *y_ptr-, *CDP-, A
	MACMR *y_ptr+, *CDP, A
	MOV HI(A << #-1), *r2_ptr+
	
; ---- 1 -----	
	MPYM *y_ptr, *CDP, A
	MOV HI(A), *r2_ptr

;--------- Calculate sum in region 2
; ---- BIAS calculation -----	
	; Clear SXMD
	BCLR #ST1_SXMD, ST1_55
	
	; Actual calculation
	MOV #32767, A
	MOV nx, *sp(#(temp))
	RPT #15
	SUBC *sp(#(temp)), A, A
	ADD #1, A
	MOV A, *sp(#(temp))
	
	; Set SXMD
	BSET #ST1_SXMD, ST1_55
	
;----------
;	.end
;----------

REGION2:
	; Repeat setup
	MOV ny, A
	SUB nx, A
	MOV A, T3
	MOV T3, BRC0
	MOV nx, mac_cnt
 	SUB #2, mac_cnt
 	
	; R pointer setup
	MOV nx, B
	SUB #1, B
	ADD dbl(*sp(#(r_orig))), B
	MOV B, Xr_ptr

	; Setup pointers
	MOV dbl(*sp(#(y_orig))), Xy_save
	MOV dbl(*sp(#(x_orig))), Xx_save
	MOV Xx_save, XCDP
	MOV Xy_save, Xy_ptr
	MOV mac_cnt, CSR
	
REGION2_LOOP:
	RPTBLOCAL r2localloop

; ---- Setup pointers ----
	ADD #1, y_save

; ---- Preload A ----
	MPYM *y_ptr+, *CDP+, A

; ---- Main MAC loop  ---- 
;	MOV mac_cnt, CSR
	RPT	CSR
	MACM *y_ptr+, *CDP+, A
	
; ---- BIAS ----
	MPYMR *sp(#(temp)), A, A

; ---- Setup for subsequent passes through Region 2 ----     
	MOV Xx_save, XCDP
	MOV Xy_save, Xy_ptr
	
; ---- Store ----      
r2localloop:	MOV HI(A), *r_ptr+


; Check if overflow occurred, and setup return value
;----------------------------------------------------------------
	MOV #0, oflag
	
    .if  $isdefed("SI_BUGS")
	XCC dummy1, overflow(A)
	.else
	XCCPART dummy1, overflow(A)
	.endif
dummy1:  MOV #1, A
	
    .if  $isdefed("SI_BUGS")
	XCC dummy2, overflow(B)
	.else
	XCCPART dummy2, overflow(B)
	.endif
dummy2:	MOV #1, A 

;
; Restore status regs to expected C-convention values as needed
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
	MOV	dbl(*SP(#(SAVE_AR7))), XAR7	; POPM    AR7
	|| BCLR #ST1_SATD, ST1_55
	
	MOV	dbl(*SP(#(SAVE_AR6))), XAR6	; POPM    AR6
	|| BCLR SATA
	
	MOV	dbl(*SP(#(SAVE_AR5))), XAR5	; POPM    AR5
	|| BCLR #ST1_FRCT, ST1_55

                                           	
;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
	AADD #(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
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
