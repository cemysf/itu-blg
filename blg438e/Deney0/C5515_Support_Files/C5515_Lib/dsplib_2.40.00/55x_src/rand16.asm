;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Filename:	rand16.asm
; Processor:   C55xx
; Description: Generates 16 bit random numbers
;
; Useage: ushort oflag= rand16(DATA *r, ushort nr)
;                                                              
; Copyright Texas instruments Inc, 2000
;**************************************************************** 		
;
; Use memory mapped register mnemonics
;-----------------------------------------------------------------------------
			.mmregs

;-----------------------------------------------------------------------------
; Define constants used in the random number generation algorithm
;-----------------------------------------------------------------------------
                                    
RNDMULT		.set	31821					; Multiplier value
RNDINC		.set	13849					; Increment value     
			
;-----------------------------------------------------------------------------
; Initialize Random Number Generator -	Load the SEED value
;-----------------------------------------------------------------------------
        	.ref	rndseed                 ; Global variable initialized in
        									; randinit()
			.def	_rand16
			.text

_rand16: 
      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  
      PSH	mmap(ST3_55)
			AND		#0F9DFh,mmap(@ST1_55) 	; Clear M40, SATD and C54CM
		

			BCLR	ACOV0,ST0_55          	; Clear AC0 overflow flag 
		
			BCLR	SMUL,ST3_55			  	; Clear SMUL bit  

                                    		
			BSET	SXMD,ST1_55			  	; Set SXMD    
		
			BCLR	AR0LC,ST2_55		 	; Set AR0 in linear mode	
								  
  		
			  	   
			SUB		#1,T0                	; Set up count to 'nr-1'	
			
	   
		    MOV		T0,BRC0		    	 	; Store number of vector
										  	; elements in repeat cntr  
	    ||  MOV		#RNDMULT,T1			  	; Initialize register with
										 	; constant	    	     						               		      			
	   										  
		    MOV		#RNDINC,AC1		      	; Initialize register with
										  	; constant  
	        
    		

			MACM	*abs16(#rndseed),T1,AC1,AC0	
										                     
	        MOV		#0,T0                 	; Clear flag for returning overflow 
	        							  	; status              									  		 
	        RPTBLOCAL loop_end       
	        
	        MOV		AC0, *AR0		      	; Store random number in array
loop_end:    	
			MACM    T3=*AR0+,T1,AC1,AC0	  	; Generate new random number
	        
	        MOV		T3,*abs16(#rndseed)  	; Store final result as random seed 
	        
	        XCC	    set_flag, overflow(AC0) ; Test AC0 overflow flag
	
set_flag:	MOV		#1,T0                 	; If overflow, set return flag		

      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
			RET                    
;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
    

