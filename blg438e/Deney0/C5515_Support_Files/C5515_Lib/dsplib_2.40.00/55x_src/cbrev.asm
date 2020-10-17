;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Note: a symbol "SI_BUGS" is used to make a work around for silicon
; 5510 version1.0. If you are going to use the code on 5510 version1.0
; silicon, you have to put switch -d"SI_BUGS" when you compile the code.
;*********************************************************************
; Function:    cbrev
; Processor:   C55xx
; Description: This function performs bit-reversal of complex data array x.
;              If x==y, in-place bit reversal is performed.
; Usage:    void cbrev (DATA *x, DATA *y, ushort n)
; Copyright Texas instruments Inc, 2000
;****************************************************************

		.mmregs  
		.cpl_on   

		.sect ".text:cbrev"
        .global _cbrev   

_cbrev:

;//-----------------------------------------------------------------------------
;// Context Save
;//-----------------------------------------------------------------------------

	PSH	mmap(ST2_55)		; preserve ST2 register  

;//-----------------------------------------------------------------------------
;// Initialize
;//-----------------------------------------------------------------------------

	BSET	AR1LC			      ; circular addressing for AR1
	.arms_off
	BCLR	ARMS			      ; reset ARMS bit
	
	MOV	T0, T1			    ; n in DR1
	SFTL	T1, #1			; 2*n
	MOV	mmap(T1), BK03		; circular buffer size is 2*n 
	MOV	mmap(AR1), BSA01	      ; circular buffer offset 
     


 
      MOV T0, Hi(AC2)               ; used for log2(N) computation


;
;	Determine if in-place or off-place computation
;

	MOV	XAR1, AC0
	MOV	XAR0, AC1		     
	
	MOV	#0, AR1			 ; output pointer (circular)

	
	SUB	AC1, AC0		    ; compare input and output pointers 
	BCC	off_place, AC0 != #0; if x<>y, do off-place bit reversal

;//-----------------------------------------------------------------------------
;// In-place bit reversal
;//-----------------------------------------------------------------------------
in_place: 

	BSET	AR0LC			; circular addressing for AR0
	BSET	AR2LC			; circular addressing for AR2
	BSET	AR4LC			; circular addressing for AR4
	BSET	AR3LC			; circular addressing for AR3
	
	MOV	mmap(AR0), BSA23	; circular buffer offset 
	MOV	mmap(AR0), BSA45	; circular buffer offset
	MOV	mmap(AR0), BSA01	; circular buffer offset 

 	MOV	#0, AR0			 ; output pointer (circular)
 	MOV	#0, AR3			 ; output pointer (circular)
 	MOV	#0, AR2			 ; output pointer (circular)
 	MOV	#0, AR4			 ; output pointer (circular)

;
;    Initialize extended part of XARn
;

    MOV    XAR0,XAR2
    MOV    XAR0,XAR3
    MOV    XAR0,XAR4

;
;    Compute log2(N)
;

	EXP AC2, T1				; Hi(AC2) = N
    MOV #14, AC2
    SUB T1,AC2				; AC2 = log2(N)


;
;	Test if log2(N) is odd
;

	AND #1, AC2, AC3
	BCC	log2n_odd, AC3 != #0	; branch to log2(N) odd processing
	
;
; 	process for log2(N) even
;	

 
;
;   Compute 2^[log2(N)/2]-1           
;                               
           SFTL AC2, #-1			; log2(N)/2
           MOV AC2, T1
           NEG T1
           MOV T0, AC2
           SFTL AC2,T1              ; 2^[log2(N)/2]				
           
           SUB     #2, AC2, AC3
           MOV     AC3,mmap(BRC0)   ; 2^[log2(N)/2]-2 
            
           MOV     AC2,T0
           SFTL    AC2, #1 
           MOV     AC2,T1             
                                      
           MOV     #0,AC2  

            RPTBLOCAL even_loop
              MOV   AC2,mmap(BRC1)
              AMAR  *(AR0+T0B)
              AMAR  *(AR2+T1)
              AMOV  AR0,AR4
           || ADD #1,AC2
              AMOV  AR2,AR3
           || RPTBLOCAL even_loop
                ; loop starts here
                MOV dbl(*AR4),AC0
                MOV dbl(*AR3),dbl(*(AR4+T1))
                
even_loop:
				MOV AC0,dbl(*(AR3+T0B))

	B	end  
log2n_odd:


;
;   Compute 2^[(log2(N)-1)/2]           
;    
		   SUB #1,AC2               ;  log2(N)-1          
           SFTL AC2, #-1			; (log2(N)-1)/2
           MOV AC2, T1
           ADD #1, T1
           NEG T1
           MOV T0, AC2
           SFTL AC2,T1				;2^[(log2(N)-1)/2]
           

			SUB    #2, AC2, AC3
            MOV    AC3,mmap(BRC0) 
            SFTL   AC2, #1   
            MOV    AC2,T0
            SFTL   AC2, #1 
            MOV    AC2,T1             
            
            MOV     #1,AC2
            RPTBLOCAL  odd_loop
              MOV   AC2,mmap(BRC1)
              AMAR  *(AR0+T0B)
              AMAR  *(AR0+T0B)
              AMAR  *(AR2+T1)
              AMOV  AR0,AR4
           || ADD #2,AC2
              AMOV  AR2,AR3
           || RPTBLOCAL odd_loop
                ; loop starts here
                MOV dbl(*AR4),AC0
                MOV dbl(*AR3),dbl(*(AR4+T0))
                
odd_loop:
				MOV AC0,dbl(*(AR3+T0B))

	B	end  
	 
	
;//-----------------------------------------------------------------------------
;// Off-place bit reversal
;//-----------------------------------------------------------------------------
off_place: 

;TEST

   
;	MOV	T0, T1			    ; n in DR1
;	SFTL	T1, #1			; 2*n
;	MOV	mmap(T1), BK03		; circular buffer size is 2*n 
;	MOV	mmap(AR1), BSA01	; circular buffer offset      
 ;	MOV	#0, AR1			    ; output pointer (circular)


;END TEST

 	MOV	T0, T1			    ; n in DR1
	SUB	#1, T1
	MOV	mmap(T1), BRC0		; BRC0 = n - 1 						
 
	RPTBLOCAL	loop2-1            
	MOV	dbl(*AR0+), AC0
	MOV	AC0, dbl(*(AR1+T0B))  

loop2:

;//-----------------------------------------------------------------------------
;// Context Restore
;//-----------------------------------------------------------------------------
end:
      BSET	ARMS			; restore C environment 
	POP	mmap(ST2_55)		; restore ST2_55 register

	RET				; return   

	.end     

 