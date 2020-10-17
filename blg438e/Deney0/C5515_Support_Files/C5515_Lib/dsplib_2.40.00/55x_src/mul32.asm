;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    mul32
; Processor:   C55xx
; Description: Implements a vector add using a single-MAC 
;              approach.  This routine is C-callable.
;
; Usage: ushort oflag = add (DATA *x,
;                             DATA *y,
;                             DATA *r,
;                             ushort nx,
;                             ushort scale)
;
; Copyright Texas instruments Inc, 2000
;****************************************************************

        .mmregs

					; register usage
					; ar0: addr. idx
* 	.asg	cdp, ar_x  ; used for mul32dual
	.asg	ar0, ar_x  ; used for mul32
	.asg	ar1, ar_y
	.asg	ar2, ar_z
	.asg	ar5, ar_zero

      .asg     T0, oflag            ;returned value

;*****************************************************************************
	.ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                       ;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

      .def	_mul32
	.text

_mul32

      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  
      PSH	mmap(ST3_55)
	MOV 	#0, ar_zero 		; for zeroing   	
	MOV		#0,	T3                              	



;
; Configure the status registers as needed.
;----------------------------------------------------------------

      AND #01FFh,mmap(ST0_55)       ;clear all ACOVx,TC1, TC2, C
      OR #4140h,mmap(ST1_55)        ;set CPL, SXMD, FRCT
      AND #0F9DFh,mmap(ST1_55)       ;clear M40, SATD, 54CM 
      AND #07A00h,mmap(ST2_55)       ;clear ARMS, RDM, CDPLC, AR[0-7]LC
      AND #0FFDDh,mmap(ST3_55)       ;clear SATA, SMUL
  ; Setup passed parameters in their destination registers
; Setup circular/linear CDP/ARx behavior
;----------------------------------------------------------------

; x pointer - passed in its destination register, need do nothing

; y pointer - - passed in its destination register, need do nothing

; r/z pointer - passed in its destination register, need do nothing

    MOV mmap(T0),a      ;RPTB count
    SUB 	#1, AC0
    MOV		AC0, mmap(BRC0)              

 	MOV #2,T0           ; for indexing
 	MOV #3,T1           ; for indexing

;
; 	mpy	*ar_x+,a		; a = 0 and XH adjustment
	MPYM 	*ar_x+, T3, AC0  

_start:
	; long data are stored in XH[0],XL[0], XH[1],XL[1], XH[2],XL[2], ... 
    rptblocal	eloop-1 		;					
  	
*	macsu	*ar_x-,*ar_y+,a 	; a  = XL*YH	(1)
    MPYM	uns(*ar_x-), *ar_y+, AC0 

*	macsu	*ar_y-,*ar_x,a		; a += XH*YL	(1)
    MACM	*ar_x, uns(*ar_y-), AC0 
 	
*	ld	a,-16,a 		; a >>= 16				
*	mac	*ar_x+0%,*ar_y+0%,a	; a += XH*YH		(1)
    MACM 	*(ar_x+T1), *(ar_y+T0), AC0 >> #16
    
*	st	a,*ar_z+ || ld *ar_zero,t;				(1)
*	stl	a,*ar_z+		;						
    MOV	AC0, dbl(*ar_z+)
;									 	Total loop cycles = 4 

eloop

; Return
;--------
_end:

;
; Check if overflow occurred, and setup return value
;----------------------------------------------------------------

	MOV	#0, oflag		;clear oflag

	XCCPART	check1, overflow(AC0)	;clears ACOV0
	||MOV	#1, oflag		;overflow occurred

check1:

      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
	RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
