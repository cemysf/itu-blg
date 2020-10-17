;***********************************************************
; Version 2.40.00                                           
;***********************************************************
;****************************************************************
; Function:    maxidx34
; Processor:   C55xx
; Description: Description: Returns the index of the maximum element of a vector x. In case
;	of multiple maximum elements, r contains the index of the last maximum
;	element found
; Usage:    short r = maxidx34 (DATA *x, ushort nx)
;	Arguments:
;	*x Pointer to input vector of size nx 
;   nx Number of elements in the x[NX] array  
;	r Index for vector element with maximum value
;
;
;	State of the registers after the call:
;
;	XAR0 contains *x
;	T0   contains nx
;
;
;
; Copyright Texas instruments Inc, 2000
; History:
; 	2.10 Cesar I. original code. 08/03/01
;****************************************************************
      .ARMS_off                     ;enable assembler for ARMS=0
      .mmregs                       ;enable mem mapped register names 
      .noremark   5555, 5584, 5573, 5572       
      
      
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
	.asg     AR1, maxv_ptr		  ;linear pointer
    
    .asg     BRC0, outer_cnt      ;outer loop count

        .text                                                           
               
        .global _maxidx34    
	
_maxidx34:   

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)
 

;
; Save any save-on-entry registers that are used
;----------------------------------------------------------------

      PSH T2, T3   
	
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
	

; Setup loop counts
;----------------------------------------------------------------
	SFTL T0, #-1			;restore original value 
     ||SUB AC3, AC3

     SUB #2, T0  
     ||MOV @AC3_L,TRN0          ; TRN0 = #0

	MOV T0, CSR                ;CSR = NG_SIZE/2 - 2
     ||MOV @AC3_L,TRN1	      	; TRN1 = #0  
   
  	 SUB T1,T1 
      MOV T0, AR3

; start benchmark
	   
	MOV dbl(*AR0+), AC1	;AC1_H = Aaddr[0],  AC1_L = Aaddr[1]
    
    ; 1 stall
	MOV dbl(*AR0+), AC0		;AC0_H = Aaddr[2],  AC0_L = Aaddr[3]
	|| RPT CSR         ;repeat( #( (NX/2 - 1) - 1) )


	MOV dbl(*AR0+), AC0
	|| MAXDIFF AC0, AC1, AC1, AC2	   ;AC1_H/L contain max's
     ; 1 stall
     MOV AC1, T2           ; T0    = odd max value
     || MOV @AC1_H, AC1    ; AC1_L = even max value
        ;assume even max value > odd max value
	MOV T1, T0			;DR0 setup for even max index computation
	|| MOV @TRN0_L << #16, AC0		;AC0_H = TRN0 (setup for even max index)

  ;test max(odd max value, even max value), Carry bit affected
	MAX T2, AC1			;AC1 = max(odd max value, even max value) 

     
	MOV AR3,T3     ; AR3  = #(NX/2 - 2)		;index seed value
	|| XCCPART  label1, !CARRY			;if Carry=0 then odd max value > even max value
    
    ; move at the last place to take advantage of localrepeat 

    MOV @TRN1_L << #16, AC0		;AC0_H = TRN1 (setup for odd max index)
	|| ADD #1, T0		;DR0 modified for odd max index computation
 
    MOV  #0ffh, @AC0_G  			;AC0_G = 0xff, to isolate leading zero
    ; 1 stall
	EXP AC0, T2			;T2 = position of leading zero in AC0 
  
	SUB T2, T3  			;subtract lead zero position from index seed
	SFTL T3, #1 		;mult by 2 since 2 values tested per iteration
	ADD T3, T0 			;T0 = index of max value (return value)

;   
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------

	BSET #ARMS, ST2_55
      BSET #CPL, ST1_55	       ;SP relative addressing


;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------
;    

	POP mmap(@DP_L)
	POP T2, T3

;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#+(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)



    RET        
        
        
        
        
        
        
        
        
        
        