;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    maxval
; Processor:   C55xx
; Description: Description: Returns the value of the maximum element of a vector x
; Usage:    short r = maxval (DATA *x, ushort nx)
;	Arguments:
;	*x Pointer to input vector of size nx 
;     nx number of elements in the x[NX] array  
;	r maximum value
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
;  2.10.04 Li Yuan optimized code for benchmark purpose. 08/03/01
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
    .asg     BRC0, outer_cnt      ;outer loop count
    
    .global _minval

    .text

_minval:

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)
 
  
	
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

    SFTL  T0, #-1  			        ;divide by 2 
    SUB  #2, T0

    MOV T0, CSR				        ;CSR = NX/2 - 2
    || MOV dbl(*AR0+), AC1 		    ;AC1_H = Aaddr[0],  AC1_L = Aaddr[1]

	MOV dbl(*AR0+), AC0		        ;AC0_H = Aaddr[2],  AC0_L = Aaddr[3]
    || RPT CSR  
	

	MOV dbl(*AR0+), AC0
	|| MINDIFF AC0, AC1, AC1, AC2	;AC1_H/L contain min's

    
	 MOV AC1, T0			        ;T0 = odd min value
	||MOV @AC1_H, AC3 		        ;AC1 = even min value
      
;test max(odd max value, even max value), Carry bit affected
	MIN AC3,T0        		        ;AC1 = min(odd min value, even min value)
				                    ; return value in T0
;
; Restore status regs to expected C-convention values as needed
;----------------------------------------------------------------

    BSET #ARMS, ST2_55
    BSET #CPL, ST1_55	       ;SP relative addressing

;
; Restore any save-on-entry registers that are used
;----------------------------------------------------------------

    POP mmap(@DP_L)



;
; Deallocate the local frame and argument block
;----------------------------------------------------------------
;      AADD	#+(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP
; - not necessary for this function (the above is zero)

    RET        
