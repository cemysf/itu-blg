;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Processor:   C55xx
; Description: Radix-2 DIT complex FFT using normal input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
;    First two stages are in radix-4.
; Usage:    void cfft (DATA *xy, ushort nx);
; Copyright Texas instruments Inc, 2000
; History:
; 	- 07/18/2002	Sira fixed the bug in the kernal.
;	- 07/17/2003	C. Iovescu changed the way the twiddle table is included
;****************************************************************

;-----------------------------------------------------------------------
; Arguments passed to _fft
;
; ar0       ->    fftdata pointer
; t0        ->    fft size
;
;-----------------------------------------------------------------------



;//-----------------------------------------------------------------------------
;// Array declarations
;//-----------------------------------------------------------------------------


        .ref twiddle		;reference to twiddle table
	         


        .def _cfft_NOSCALE     ; make function visible to other fnct
        .cpl_on
        .arms_off     ; enable assembler for arms mode
        .mmregs
        .noremark    5579, 5573
  
; Stack frame
; -----------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-entry registers saved
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ


; Local variables
; --------------      
       
       .asg    0, data_ptr
       .asg    1, data_sz

;//-----------------------------------------------------------------------------
;// Temp data
;//-----------------------------------------------------------------------------

		.bss tempmem, 2, , 2
		.bss tempmem1, 2, , 2 

;//-----------------------------------------------------------------------------
;// Register aliases
;//-----------------------------------------------------------------------------
		.asg	T3,groups		; number of butterfly groups
		.asg	T1,index		; addess adjustment
		.asg	AR7,bflies		; number of butterflies/group
		.asg	AR4,k			; outer loop counter
		.asg	AR2,a			; top butterfly pointer
		.asg	AR3,b			; bottom butterfly pointer
		.asg	AR5,temp		; temp register	


      
        .text           


_cfft_NOSCALE



;
; Save any save-on-entry registers that are used
;----------------------------------------------------------------
;



      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  
      PSH	mmap(ST3_55)


      PSH T2
      PSH T3
	PSHBOTH XAR5
	PSHBOTH XAR6
	PSHBOTH XAR7

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
	AADD	#-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP



;
; Save entry values for later
;----------------------------------------------------------------

	MOV AR0, *sp(data_ptr) ; 
      MOV T0, *sp(data_sz)   ;

;-----------------------------------------------------------------------
; FFT implementation
;
; The FFT is implemented in three different steps:
;
;  1) - a radix-4 stage with twiddle factors only equal to -1, 0 and 1
;  2) - a group of log2(FFT_SIZE)-3 radix-2 stages
;  3) - on out-of-place bit-reversal
;
;  No need to implement the last stage in a different way
;  to the other stages.

        
            ; save all save-on-entry regs that are modified
            


;-----------------------------------------------------------------------
; Modification of status registers

	  
        BSET #FRCT, ST1_55          
        BCLR #ARMS, ST2_55          
	  BCLR #C54CM, ST1_55  
   



              
;-----------------------------------------------------------------------
; First two stages computed as one radix-4 stage


    ; --------------------------------------------------------------        
        ; First in-place radix-4 stage
        ;
        ;        ----------
        ; a -----|   R    |----- a'
        ;            A
        ; b -----|   D    |----- b'
        ;            I
        ; c -----|   X    |----- c'
        ;  
        ; d -----|   4    |----- d'
        ;        ---------
        ;
        ; ar' =  (ar + cr) + (br + dr)
        ; ai' =  (ai + ci) + (bi + di) 
        ;
        ; br' =  (ar + cr) - (br + dr)
        ; bi' =  (ai + ci) - (bi + di)
        ;
        ; cr' =  (ar - cr) + (bi - di)
        ; ci' =  (ai - ci) - (br - dr)
        ;
        ; dr' =  (ar - cr) - (bi - di)
        ; di' =  (ai - ci) + (br - dr)
        ;        
        ; ar7, -> temp
        ; ar6  -> temp1
        ;
        ; ar0-> a
        ; ar1-> b
        ; ar2-> c
        ; ar3-> d
        ;
        ; ar5 = ar2
        ;
        ; t0 = 1
        ; t1 = 2
        ;       
        ;
        ; ac0-ac3 modified
        ; t1-t2 modified
        ;
        ; --------------------------------------------------------------        


       
    ; AR0 contains    #(fftdata)                 ; a
	
	  MOV  XAR0, XAR2
      ADD  *sp(data_sz), AR2			; c: ar2 = #(fftdata + 2*2*FFT_SIZE/4)
     
      SFTS T0, #-1					; T0 = FFT_SIZE/2
      mov xar2, xar3    
    MOV  XAR0, XAR1
	ADD  *sp(data_ptr), T0, AR1			; b: ar1 = #(fftdata + 1*2*FFT_SIZE/4)
	

      ADD  T0, AR3					; d: ar3 = #(fftdata + 3*2*FFT_SIZE/4)
      SFTS T0, #-1					;T0 = FFT_SIZE/4
	
      SUB #2, T0
	
	AMOV #(tempmem1), XAR7
      AMOV #tempmem, XAR6
       

	MOV #2, T1 							; 
	||MOV dbl(*AR0), AC0					; in (ar,ai)
       
      MOV T0, BRC0
	||ADD	dual(*AR2), AC0, AC2	 		; (ar+cr)/ ; (ai+ci) 
			    		   
	 		    		    		   
	 		    		    		    		   
	 		    		    		    		    		    		   
    
    MOV XAR2, XAR5 
    MOV #1, 	T0 
       
    MOV dbl(*AR1) ,AC1 				; in (br,bi)
	||	MOV AC2, dbl(*AR6) 		; temp (ar+cr),(ai+ci)   
    
    SUB	dual(*AR3), AC1, AC2   		; (br-dr)/(bi-di)
	 		
    
        
    SUB	dual(*AR2+), AC0    		; (ar-cr)/(ai-ci) 
    || MOV Hi(AC2),T3 	                    ; move (br-dr)
    
  	ADD	dual(*AR3), AC1, AC3 		; (br+dr)/ (bi+di)
 	||	MOV AC2, T2				; move (bi-di)        
        	    
        
    ADD	dual(*AR6), AC3, AC0   		; (ar+cr) + (dr+br) = ar'
	                        		; (ai+ci) + (di+bi)	= ai'
	||MOV AC0, dbl(*AR7(T0))            ; (ar-cr),(ai-ci) unaligned

          
    SUB	AC3, dual(*AR6), AC3    		; (ar+cr) - (dr+br) = br'
					 		; (ai+ci) - (di+bi)	= bi'
    ||MOV AC0, dbl(*AR0+)                 ; out (ar';ai')
         
    SUBADD	T2, *AR7(T0), AC0   		; (ar-cr) - (bi-di)	= dr'
							; (ar-cr) + (bi-di)	= cr'

   ADDSUB	T3, *AR7, AC1 			; (ai-ci) + (br-dr)	= di'
 							; (ai-ci) - (br-dr)	= ci'

        
        
        
        RPTBLOCAL r4_loop
        
    
      MOV AC3, dbl(*AR1+)				; out(br', bi')								; 
	||MOV  dbl(*AR0), AC3				; in (ar,ai)
       
       MOV 	pair(HI(AC0)),dbl(*AR3+)       		; out(dr',di')
	||ADD	dual(*AR2), AC3, AC2 			; (ar+cr) 
	    							; (ai+ci)   
       
       MOV   dbl(*AR1), AC1				; in (br,bi)
	|| MOV  pair(LO(AC0)), dbl(*AR5+) 	            ; out (cr', ci')
    
    SUB	dual(*AR3), AC1, AC2      		; (br-dr)/(bi-di) 
    || MOV AC2, dbl(*AR6) 				; temp (ar+cr),(ai+ci)
    
        
   SUB	dual(*AR2+), AC3, AC0     	      ; (ar-cr)/(ai-ci) 
    || MOV  Hi(AC2), T3                         ; move(br-dr)
    
       ADD	dual(*AR3), AC1, AC3    		; (br+dr)/(bi+di) 
 	||	MOV AC2, T2 				; move (bi-di)        
        	    
        
   	ADD dual(*AR6), AC3, AC0 			; (ar+cr) + (dr+br) = ar'
						 		; (ai+ci) + (di+bi)	= ai' 
	||MOV AC0, dbl(*AR7(T0))			; (ar-cr),(ai-ci) unaligned
	  
           
   SUB	AC3, dual(*AR6), AC3     		; (ar+cr) - (dr+br) = br'
							; (ai+ci) - (di+bi)	= bi'
    ||MOV AC0, dbl(*AR0+) 
         
    SUBADD	T2, *AR7(T0), AC0    			; (ar-cr) - (bi-di)	= dr'
								; (ar-cr) + (bi-di)	= cr'

r4_loop:    ADDSUB	T3, *AR7, AC1   		; (ai-ci) + (br-dr)	= di'
 								; (ai-ci) - (br-dr)	= ci'

     
    MOV AC3, dbl(*AR1+) 				; out(br', bi')	   
    MOV pair(HI(AC0)), dbl(*AR3+)      ; out(dr',di')       
    MOV pair(LO(AC0)),	dbl(*AR5+)	    ; out (cr', ci')      




;-----------------------------------------------------------------------
; radix-2 stages (stages 3->log2(FFT_SIZE) )
        


        ; main initialization
        ; --------------------
        
       MOV *sp(data_ptr), AR0		; ar0 = #fftdata
       
            ; 1 - circular buffer initializations

        
            ; modify ST2 to select linear or circular addressing modes
       OR	#0x57 , mmap(ST2_55)  ; circular ar0, ar1, ar2, ar4 and ar6
         

            ; circular buffer starting addresses
        ADD #2, ar0,ar1
        MOV mmap(@ar0),bsa23       ; P  leg
        MOV mmap(@ar0),bsa45       ; P' leg    (in-place butterflies)
        MOV mmap(@ar1),bsa01       ; Q  leg
        MOV mmap(@ar1),bsa67       ; Q' leg    (in-place butterflies)
                            
            ; circular buffer sizes 
	  MOV *sp(data_sz), T0
        MOV T0, T1		; T1 =  #FFT_SIZE
	  SFTS T0, #1        
        SUB #2, T0
    
        MOV mmap(@T0_L), bk03          	; bk03 = (2*FFT_SIZE-2), 
        MOV mmap(@T0_L), bk47   ; bk47 = (2*FFT_SIZE-2), 

            ; 2 - register initializations
        
       MOV *sp(data_sz), T0
       SFTS T0, #-1
       SFTS T0, #-1
        
        MOV T0, ar5   ; 2*number of groups for stage 3    
        MOV #2, ar7          ; 1/2 * number of butterflies per group for stage 3
       

        AMOV #twiddle, xar3        ; not modified during iteration of the stages
        ADD #2, AR3
        MOV xar0,xar1            ; data page = data page of indata
        MOV xar0,xar2            ; data page = data page of indata
        MOV xar0,xar4   ; data page = data page of indata (in-place butterflies)
        MOV xar0,xar6   ; data page = data page of indata (in-place butterflies)
        MOV xar3,xcdp      ; data page = data page of twiddles
        

        
stage:    ; begining of a new stage

        ; stage initialization
        ; --------------------


            ; 1 - loop counter updates
        
            ; butterfly counter update
       SFTS ar7, #1
    ||    MOV #0, ar4 
        SUB #2,ar7,ar0
        MOV ar0, brc1        ;1 butterflies executed out of the loop

            ; group counter update
        SFTS ar5, #-1
        SUB  #1,ar5,ar0     
        MOV ar0, brc0         

            ; stage "counter" update (t0=0 <=> last stage)
         AMOV ar0, t0

            ; 2 - pointer modifier update
                            
            ; t1 is the pointer modifier                    
    ||   SFTS  t1,#-1        

            ; 3 - index updates                  
            ; ar0 -> Qr[0]
            ; ar1 -> Qi[0]
            ; ar2 -> Pr[0]
            ; ar4 -> Pr'[0]  (performed above to use parallelism)
            ; ar6 -> Qr'[0]

 
        SFTS ar0, #1
        ADD #1, ar0,ar1
        MOV #0, ar2
    ||  MOV ar0, ar6 
        
        
        
group:  ; begining of a new group
        

        ; note:
        ; - circular buffers are used for data pointers so that no
        ;   initialization of data pointers is required before a new
        ;   iteration of a group
        ; - twiddle pointer (cdp) is updated inside the loop
        
                
        RPTBLOCAL r2_loop1

        
                ; ac2=Qr[0]:Qi[0] 
        MOV dbl(*(ar0+t1)), ac2
    ||  ADD  t1,ar1       
                
                ; ac0 = Pr[0]+Qr[0]:Pi[0]+Qi[0]
                ;     = Pr'[0]:Pr'[0]
                ; cdp = #twiddle
       ADD	dual(*AR2), AC2, AC0 
      ||    MOV ar3, cdp

        
                ; ac1 = Pr[0]-Qr[0]:Pi[0]-Qi[0]
                ;     = Qr'[0]:Qi'[0]
                ; store P'[0]

  	SUB	AC2, dual(*(AR2+T1)), AC1    
      || MOV ac0, dbl(*(ar4+t1))   
      
                  
              
                                   
                                                                  
                                                                    
          RPTBLOCAL r2_loop2          


                    ; ac2=Qr[n]*Wr                                    
                    ; ac3=Qi[n]*Wr
          MPY	*AR0, *CDP+, AC2               
        ::MPY	*AR1, *CDP+, AC3                           
                
        
                    ; ac3=Qi[n]*Wr+Qr[n]*Wi
                    ; ac2=Qr[n]*Wr-Qi[n]*Wi

        MASR	*(AR0+T1), *CDP+, AC3  
        ::MACR	*(AR1+T1), *CDP+, AC2   
            
            
                    ; ac2=(Qr[n]*Wr-Qi[n]*Wi):(Qi[n]*Wr+Qr[n]*Wi)

        OR AC3 << #-16, AC2
                
                    ; hi(ac0)=Pr[n]+(Qr[n]*Wr-Qi[n]*Wi)=Pr'[n]
                    ; lo(ac0)=Pi[n]+(Qr[n]*Wi+Qi[n]*Wr)=Pi'[n]
                    ; store Qr'[n-1]:Qi'[n-1]

	   ADD	dual(*AR2), AC2, AC0
	   ||  MOV ac1, dbl(*(ar6+t1)) 
    
    
                    ; hi(ac1)=Pr[n]-(Qr[n]*Wr-Qi[n]*Wi)=Qr'[n] 
                    ; lo(ac1)=Pi[n]-(Qr[n]*Wi+Qi[n]*Wr)=Qi'[n]
                    ; store Pr'[n]:Pi'[n]

r2_loop2:	SUB	AC2, dual(*(AR2+T1)), AC1
		|| MOV ac0, dbl(*(ar4+t1)) 
        
                                   ; end of butterfly loop
        
r2_loop1:        MOV AC1, dbl(*(ar6+t1))      ; store last Qr':Qi'
        
                                   ; end of group loop
    
        
        BCC stage,t0!=#0       ; end of stage loop       	
   	   
        
              
end_benchmark:

;
; Allocate the local frame and argument block
;----------------------------------------------------------------
	AADD	#(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP


;Context restore 
	POPBOTH XAR7
	POPBOTH XAR6
	POPBOTH XAR5
      POP T3
      POP T2 

      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)

 

	
	RET 

	.end         
        






