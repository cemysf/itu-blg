;***********************************************************
; Version 2.40.00                                           
;***********************************************************
;****************************************************************
; Function:    minidx
; Processor:   C55xx
; Description: Description: Returns the index of the minimum element of a vector x. In case
;	of multiple maximum elements, r contains the index of the last maximum
;	element found
; Usage:    short r = minidx (DATA *x, ushort ng, ushort ng_size)
;	Arguments:
;	*x Pointer to input vector of size nx 
;     ng Number of groups forming the x[NX] array
;     ng_size Size of the group  
;	r Index for vector element with maximum value
;
;
;	State of the registers after the call:
;
;	XAR0 contains *x
;	T0   contains ng
;     T1   contains ng_size
;
;
;
; Copyright Texas instruments Inc, 2000
; History:
;  2.10 Li Yuan optimized code for benchmark purpose. 07/11/02
;               also fixed bug to make code works when the first element is min.
;****************************************************************
    .ARMS_off                     ;enable assembler for ARMS=0
    .mmregs                       ;enable mem mapped register names 
    .noremark   5555, 5584, 5573, 5572       
      
; Local variable
;----------------

      
   	.bss	MIN_VALUE, 2
MIN_INDEX	.set	MIN_VALUE + 1
      
; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
FRAME_SZ          .set 0            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ         


;----------------------------------------------------------------
; Assign auxiliary registers for temporaries and address
; calculations.
;----------------------------------------------------------------
    .asg     AR0, x_ptr           ;linear pointer                    
    .asg     AR1, minv_ptr		  ;linear pointer

    .asg     AR5, trn0_ptr    	  ; linear pointer
    .asg     AR6, trn1_ptr        ; linear pointer
    
    .asg     BRC0, outer_cnt      ;outer loop count

    .text                                                           
    
    .global _minidx    
	
_minidx:   

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)
 

;
; Save any save-on-entry registers that are used
;----------------------------------------------------------------

    PSH T2
    PSH T3
    PSHBOTH XAR5
    PSHBOTH XAR6
    PSHBOTH XAR7   
	
;
; Configure the status registers as needed.
;----------------------------------------------------------------
	 
	   
    BCLR #C54CM, ST1_55
	BCLR #ARMS, ST2_55
    BCLR #CPL, ST1_55	       ;DP relative addressing
	

    PSH mmap(@DP_L)
    MOV  #0, DP			;set DP=0 for mmreg accesses
	.dp 0       

;-----------------------------------------------------------------------
; Copy arguments to local locations and set registers
;
;-----------------------------------------------------------------------
; x pointer - passed in its destination register, need do nothing
	
    
    ;Note: *AR1+ and *AR1- modifiers are needed in following instructions
    ;to allow parallelism with the blockrepeat instruction (cannot parallelize
    ;with *AR1(#1) = #0).
    AMOV #MIN_VALUE, XAR1	;pointer to .bss base
  

;
; Setup loop counts
;----------------------------------------------------------------
    SUB  #1, T0			;T0 = ng-1
    
    MOV T0, outer_cnt			;outer loop executes ng times
    || MOV *x_ptr, *minv_ptr+ 	;MIN_VALUE = Aaddr[0]    

	MOV T1, T3
    || SUB AC3, AC3			; ac3 = #0 used to initialize TRN0,1

	SFTL T1, #-1
	|| MOV #TRN1_L, trn1_ptr 
	 
	SUB #2, T1

    MOV T1, CSR				;CSR = NG_SIZE/2 - 2
	|| MOV #TRN0_L, trn0_ptr

    MOV T1, AR3		;init position of leading zero 
  	 
  
  	SUB T1, T1
	||MOV #0ffh, AR7

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV T1, AR4			;save base index of the first data
    	
  	MOV #0, *AR1-	;MIN_INDEX = 0
    ||RPTBLOCAL outer_loop


;BENCHMARK KERNEL ******************************************************
;Data values are processed via the outer loop N_GROUP values at a time.
;The outer loop is therefore executed N_INPUT/N_GROUP times.
        


    ;START OF OUTER LOOP *******************

	MOV AC3, dbl(*AR6)		; AC3 = #0 ; init TRN1 = #0
      || MOV dbl(*AR0+), AC1		;AC1_H = Aaddr[0],  AC1_L = Aaddr[1]

	MOV dbl(*AR0+), AC0		;AC0_H = Aaddr[2],  AC0_L = Aaddr[3]
	|| RPT CSR		           ;repeat( #( (N_GROUP/2 - 1) - 1) )


  ;START OF INNER LOOP *******************

	MOV dbl(*AR0+), AC0
	|| MINDIFF AC0, AC1, AC1, AC2  	;AC1_H/L contain max's

  ;END OF INNER LOOP ***************

    MOV *AR1, AC0       			;AC0 = old max value   
    ||SUB #2, AR0 
    
     MOV AC1, T0           ; T0    = odd max value
     || MOV @AC1_H, AC1    ; AC1_L = even max value

  ;test max(odd max value, even max value), Carry bit affected
	MIN T0, AC1		;AC1 = max(odd max value, even max value)
    
  ;test max(old max value, new max value)
	CMP AC0>=AC1, TC1		;TC1 set if max(odd,even) value > old max value
   
  ;assume even max value > odd max value
	MOV T1, T0			;DR0 setup for even max index computation
	|| MOV @TRN0_L << #16, AC0		;AC0_H = TRN0 (setup for even max index)
 
	ADD T3, T1 		;T3 = #N_GROUP		;add N_GROUP to index base
  
     
     
	MOV AR3, AC2     ; AR3  = #(N_GROUP/2 - 2)		;index seed value
	|| XCCPART  label1, !CARRY			;if Carry=0 then odd max value > even max value
    
    ; move at the last place to take advantage of localrepeat 
label1:
    MOV @TRN1_L << #16, AC0		;AC0_H = TRN1 (setup for odd max index)
	|| ADD #1, T0		;DR0 modified for odd max index computation
 

  ;PERFORM IN_LOOP NECESSARY PORTION OF INDEX COMPUTATION **********

;  if TC1=1 or TC2=1, then a new max value is > old max value
    MOV AC3, *AR5     ; AC3 = #0 ; init TRN0 = #0
	||XCCPART label2 , TC1

 
label2:
  	 MOV T0, AR4			;save base index of max value
     || MOV  AR7, @AC0_G  			;AC0_G = 0xff, to isolate leading zero
   
    
    
	XCC label3, TC1

outer_loop:
label3:	EXP AC0, T2			;T2 = position of leading zero in AC0 
    || MOV AC1, *AR1    		;update MIN_VALUE

					;end outer loop


	
	SUB T2, AC2			;subtract lead zero position from index seed
	SFTL AC2, #1			;mult by 2 since 2 values tested per iteration
	ADD AR4,AC2 			;AC2 = index of max value
	 MOV AC2, T0 				; return value
;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------

	BSET #ARMS, ST2_55
      BSET #CPL, ST1_55	       ;SP relative addressing

;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------

    POP mmap(@DP_L)
	POPBOTH XAR7
      POPBOTH XAR6
      POPBOTH XAR5
      POP T3
      POP T2

;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#+(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)



    RET        
        
        
        
        
        
        
        
        
        
        