;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Processor:   C55xx
; Description: 32-bit radix-2 DIT complex FFT using normal input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
;    First two stages are separately implmented for MIPS optimization.
; Usage:    void cfft32_SCALE (DATA *xy, ushort nx);
; Copyright Texas instruments Inc, 2002
; History:
;    Original: 08/16/2002 ZhengTing He
;    08/19/2002 Li Yuan
;        - Changed || to :: in several dual MAC instructions
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


        
        .ref twiddle32
        .def _cfft32_SCALE     		; make function visible to other fnct
        .cpl_on
        .arms_off     				; enable assembler for arms mode
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
      
        .text           
_cfft32_SCALE

;----------------------------------------------------------------
; Conditional compile
;----------------------------------------------------------------
SCALED	.set	1		; SCALED = 0 - not scaled version
						; SCALED = 1 - scaled version
						
;----------------------------------------------------------------
; Save any save-on-entry registers that are used
;----------------------------------------------------------------

		PSH	mmap(ST0_55)
    	PSH	mmap(ST1_55)
    	PSH	mmap(ST2_55)  
    	PSH	mmap(ST3_55)
    	PSH T2
    	PSH T3
		PSHBOTH XAR5
		PSHBOTH XAR6
		PSHBOTH XAR7

;----------------------------------------------------------------
; Allocate the local frame and argument block
;----------------------------------------------------------------
		AADD	#-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP

;----------------------------------------------------------------
; Save entry values for later
;----------------------------------------------------------------

		MOV AR0, *sp(data_ptr) ; 
   		MOV T0, *sp(data_sz)   ;

;-----------------------------------------------------------------------
; FFT implementation
;
; The FFT is implemented in 5 different steps:
;
;  1) - a radix-2 stage without any multiplications.
;  2) - a radix-2 stage with two groups, only the 2nd group has
;       multiplications with 0x7FFFFFFH and 0x00000000
;  3) - a group of log2(FFT_SIZE)-3 radix-2 stages
;  4) - a radix-2 stage without scaling.
;  5) - on out-of-place bit-reversal
;-----------------------------------------------------------------------
        
;-----------------------------------------------------------------------
; Modification of status registers
;-----------------------------------------------------------------------	  
      	BSET #FRCT, ST1_55          
      	BCLR #ARMS, ST2_55          
	  	BCLR #C54CM, ST1_55  
      
      	BSET SXMD
      	BCLR SATD
      	BSET M40             
                     
      	; Define CSR for scaling loop
      	SUB #1, T0, T1                          
      	MOV T1, BRC0       			; BRC0 = fftsize - 1
		MOV XAR0,XAR1

;-----------------------------------------------------------------------
; Scaling loop: Data scaled by 2 before first stage 
;-----------------------------------------------------------------------       
	 	RPTBLOCAL scaling
     	MOV dbl(*AR1+), AC0       
     	MOV dbl(*AR1-), AC1
     ||	SFTS AC0,#-1 
     	SFTS AC1,#-1     
     ||	MOV	AC0, dbl(*AR1+)
scaling:MOV AC1, dbl(*AR1+)

;-----------------------------------------------------------------------
; Radix-2 stage 1
;-----------------------------------------------------------------------		
		MOV AR0,AR1					; AR0->fft_data 	(a)
		ADD T0,AR1 					; AR1->fft_data+n2  (b)
		MOV XAR1,XAR2				
		ADD T0,AR2					; AR2->fft_data+2*n2(c)
		MOV XAR2,XAR3
		ADD T0,AR3					; AR3->fft_data+3*n2(d)
		MOV XAR2,XAR7
		SFTS T0,#-1					; T0=fft-size/2
		SUB #1,T0,T1				; T1=fft_size/2-1
		MOV T1,BRC0

;-----------------------------------------------------------------------
; Benchmark: 10 cycles for this loop		
;-----------------------------------------------------------------------
		RPTBLOCAL stage1		
		MOV dbl(*AR0+),AC0
		ADD dbl(*AR7),AC0,AC1		; AC1=AR+CR
		SUB dbl(*AR7+),AC0			; AC0=AR-CR
		MOV dbl(*AR0-),AC2
	||	SFTS AC1,#-1
		ADD dbl(*AR7),AC2,AC3		; AC3=AI+CI	
		SUB dbl(*AR7-),AC2			; AC2=AI-CI	
		SFTS AC0,#-1
	||	MOV AC1,dbl(*AR0+)			;(AR+CR)>>1->AR
		SFTS AC2,#-1
	||	MOV AC0,dbl(*AR7+)			;(AR-CR)>>1->CR
		SFTS AC3,#-1
	||	MOV	AC2,dbl(*AR7+)			;(AI-CI)>>1->CI
stage1:	MOV AC3,dbl(*AR0+)			;(AI+CI)>>1->AI
	

;-----------------------------------------------------------------------
; Radix-2 stage2
;-----------------------------------------------------------------------
		MOV *sp(data_ptr), AR0
	||	SFTS T0,#-1
		SUB #1,T0,T1				;T0=fft_size/4
		MOV T1,BRC0					;T1=fft_size/4-1

;-----------------------------------------------------------------------
; Benchmark: 10 cycles for group1
;-----------------------------------------------------------------------
		RPTBLOCAL group1		
		MOV dbl(*AR0+),AC0
		ADD dbl(*AR1),AC0,AC1		; AC1=AR+BR
		SUB dbl(*AR1+),AC0			; AC0=AR-BR
		SFTS AC1,#-1
	||	MOV dbl(*AR0-),AC2
		ADD dbl(*AR1),AC2,AC3		; AC3=AI+BI
		SUB dbl(*AR1-),AC2			; AC2=AI-BI
		SFTS AC0,#-1
	||	MOV AC1,dbl(*AR0+)			; AR+BR->AR
		SFTS AC2,#-1
	||	MOV AC0,dbl(*AR1+)			; AR-BR->BR
		SFTS AC3,#-1
	||	MOV AC2,dbl(*AR1+)			; AI-BI->BI
group1: MOV AC3,dbl(*AR0+)			; AI+BI->AI


;-----------------------------------------------------------------------
; Benchmark: 13 cycles for group2	
;-----------------------------------------------------------------------	
		MOV T1,BRC0
		AMOV #twiddle32, XCDP
		MOV XAR3, XAR4			
		ADD #3,AR4					; AR4->DI_LOW

		RPTBLOCAL group2
		AMAR *AR3+					; 							AR3->DR_LOW
		MPY uns(*AR3-),*CDP+,AC0	;DR_LOW * 7FFF 				AR3->DR_HI	CDP->FFFF
	::	MPY uns(*AR4-),*CDP+,AC1    ;DI_LOW * 7FFF	 			AR4->DI_HI  
		MAC	*AR3,uns(*CDP-),AC0		;DR_HI*FFFF+DR_LOW*7FFF, 	AR3->DR_HI	CDP->7FFF
	:: 	MAC	*AR4,uns(*CDP-),AC1		;DI_HI*FFFF+DI_LOW*7FFF, 	AR4->DI_HI	
		MAC *AR3,*CDP,AC0>>#16		;DR_HI*7FFF+AC0>>16			AR3->DR_HI	CDP_>7FFF
	::	MAC *AR4,*CDP,AC1>>#16		;DI_HI*7FFF+AC1>>16			AR4->DI_HI	CDP_>7FFF				
		SUB AC1,dbl(*AR2),AC2		;AC2=CR-AC1
		ADD dbl(*AR2+),AC1			;AC1=CR+AC1					AR2->CI
		SUB AC0,dbl(*AR2),AC3		;AC3=CI-AC0			
		ADD dbl(*AR2-),AC0			;AC0=CI+AC0					AR2->CR
		SFTS AC1,#-1
	||	ADD #5, AR4					;							AR4->DI(next)
		SFTS AC3,#-1
	||	MOV AC1,dbl(*AR2+)			;AC1->CR					AR2->CI
		SFTS AC2,#-1	
	||	MOV AC3,dbl(*AR2+)			;AC3->CI					AR2->CR(next)
		SFTS AC0,#-1
	||	MOV AC2,dbl(*AR3+)			;AC2->DR					AR3->DI
group2:	MOV AC0,dbl(*AR3+)			;AC0->DI					AR3->DR(next)

;-----------------------------------------------------------------------
; End of stage 1 and 2
;----------------------------------------------------------------------- 		
		SFTS T0,#-1
		BCC end_benchmark, T0==#0

					    			 			    			    			    			    			    			    		
;-----------------------------------------------------------------------
; radix-2 stages (stages 3->log2(FFT_SIZE) )  
; 	register usage
; 	ar0->Pr, ar1->Qr, ar3->twiddle
; 	ar4=Re distance of butterfly
; 	ar6=group count, t1=butterfly count, ar5= stage count  
;-----------------------------------------------------------------------
        ; main initialization     	   
		
        ; modify ST2 to select linear or circular addressing modes
       	OR	#0x3 , mmap(ST2_55)		; circular ar0,ar1   
       	MOV *sp(data_ptr), AR1		; ar1 = #fftdata  

        ; circular buffer starting addresses       	     	
       	MOV mmap(@AR1),bsa01		; circular buffer start address
       	
        ; circular buffer sizes 
        MPYMK *sp(data_sz),#2,AC0	; because FRCT==1, it actually x4
        MOV mmap(@AC0_L), bk03		; bk03 = (4*FFT_SIZE-4), ar0-ar3
        
        
		MOV *sp(data_sz), T2
		SFTS T2,#-1					; T2 = FFT_SIZE/2
	||  MOV	#4, AR6					; AR6 = group    
    	MOV T2,AR4    				; AR4 = FFT_SIZE/2(Re distance between p q)
    	
    	MOV T0,T1					; T1 = FFT_SIZE/8, nbfly
    	
    	SFTS T0,#-1					; T0=size/16
    ||	MOV #-2, T2
    	MOV T0, AR5					; AR5 is stage count
    	MOV #2,T0
    	AMOV #twiddle32, XAR3
		BCC last_stage, AR5==#0      	      	 		 				  

;-----------------------------------------------------------------------
; Beginning of the stage loop
;	 stage iniac1alizaac1on
;-----------------------------------------------------------------------
stage:  ; stage loop counter updates     
		SFTS AR5,#-1			    ; shift right stage count  

		MOV #0,AR0		
	||	MOV AR3, CDP
		ADD #1,AR4,AR1				;AR1->QR_LOW
				   
        ; butterfly counter update		      		
        SUB #1,T1,T3        
        MOV T3, BRC1        

        ; group counter update
        SUB #1,AR6,T3     
		MOV T3, BRC0              
	     	
		RPTB group   	
;-----------------------------------------------------------------------
; Benchmark: 15 cycles for butterfly loop
;-----------------------------------------------------------------------
       	rptb BFly 								;             (ar1,cdp)
        mpy     uns(*ar1), *(cdp+t0), ac0       ; ac0  = yrl*crh (1,0)
::      mpy     uns(*ar1(t0)), *(cdp+t0), ac1   ; ac1  = yil*crh (3,0)

        mac     uns(*ar1(t0)), *cdp+, ac0       ; ac0 += yil*cih (3,2)
::      mas     uns(*ar1+), *cdp+, ac1          ; ac1 -= yrl*cih (1,2)
||      swap    t0, t2                          ; t0=-2

        mac     *ar1, uns(*(cdp+t0)), ac0       ; ac0 += yih*cil (2,3)
::      mas     *ar1(t0), uns(*(cdp+t0)), ac1   ; ac1 -= yrh*cil (0,3)

        mac    *ar1(t0), uns(*cdp-), ac0       	; ac0 += yrh*crl (0,1)
::      mac    *(ar1+t0), uns(*cdp-), ac1      	; ac1 += yih*crl (2,1)
||      swap    t0, t2                          ; t0=2

        mac     *ar1, *(cdp+t0), ac0>>#16  		; ac0 += yrh*crh (0,0)
::      mac     *ar1(t0), *(cdp+t0), ac1>>#16   ; ac1 += yih*crh (2,0)

        mac     *ar1(t0), *(cdp+t0), ac0        ; ac0 += yih*cih (2,2)
::      mas     *ar1, *(cdp+t0), ac1        	; ac1 -= yrh*cih (0,2)	
		
        add     dbl(*ar0), ac0,ac2        
        sfts 	ac2, #-1
||		mar 	*cdp-    
        mov     ac2,dbl(*ar0)                 	; new xr=ac0+xr  (0,4)
||	    sub     ac0,dbl(*ar0+),ac3             	;                (0,4)
		sfts 	ac3, #-1
||		mar 	*cdp-
        mov     ac3, dbl(*ar1+)                 ; new yr=xr-ac0  (2,4)
||      sub     ac1,dbl(*ar0), ac2
		sfts 	ac2, #-1
||		mar 	*cdp-   
        mov     ac2, dbl(*ar1+)                 ; new yi=xi-ac1  (2,4)
||      add     dbl(*ar0),ac1,ac3               ;                (4,4)
		sfts 	ac3, #-1
||		mar 	*cdp-   
BFly:   mov     ac3, dbl(*ar0+)                 ; new xi=xi+ac1
||      add     #1, ar1                         ;                (4,4)      	       	
       	       	  					       	  					  					       	  					  					  					  					  					  						
		ADD AR4, AR0				;jump to next group
		ADD AR4, AR1
group:	AMAR *+CDP(4)				;CDP+4
		
		SFTS AR6,#1					;group<<1
		SFTS T1,#-1					;butterfly>>1
		SFTS AR4,#-1 				;P Q distance>>1
		BCC stage,AR5!=#0
;-----------------------------------------------------------------------
; END radix-2 stages (stages 3->log2(FFT_SIZE) )  
;-----------------------------------------------------------------------

;-----------------------------------------------------------------------
; Last stage
;-----------------------------------------------------------------------		
last_stage:
        ; stage initialization
		MOV #0,AR0	 	
		MOV AR3, CDP	      		    
		MOV #5,AR1					;AR1->QR_LOW
	
        ; group counter update
        SUB #1,AR6,T3    
		MOV T3, BRC0              
     	
		RPTB lgroup				
        mpy     uns(*ar1), *(cdp+t0), ac0       ; ac0  = yrl*crh (1,0)
::      mpy     uns(*ar1(t0)), *(cdp+t0), ac1   ; ac1  = yil*crh (3,0)

        mac     uns(*ar1(t0)), *cdp+, ac0       ; ac0 += yil*cih (3,2)
::      mas     uns(*ar1+), *cdp+, ac1          ; ac1 -= yrl*cih (1,2)
||      swap    t0, t2                          ; t0=-2

        mac     *ar1, uns(*(cdp+t0)), ac0       ; ac0 += yih*cil (2,3)
::      mas     *ar1(t0), uns(*(cdp+t0)), ac1   ; ac1 -= yrh*cil (0,3)

        mac    *ar1(t0), uns(*cdp-), ac0       	; ac0 += yrh*crl (0,1)
::      mac    *(ar1+t0), uns(*cdp-), ac1      	; ac1 += yih*crl (2,1)
||      swap    t0, t2                          ; t0=2

        mac     *ar1, *(cdp+t0), ac0>>#16  		; ac0 += yrh*crh (0,0)
::      mac     *ar1(t0), *(cdp+t0), ac1>>#16   ; ac1 += yih*crh (2,0)

        mac     *ar1(t0), *(cdp+t0), ac0        ; ac0 += yih*cih (2,2)
::      mas     *ar1, *(cdp+t0), ac1        	; ac1 -= yrh*cih (0,2)

        add     dbl(*ar0), ac0,ac2
        mov     ac2,dbl(*ar0)                 	; new xr=ac0+xr  (0,4)
||	    sub     ac0,dbl(*ar0+),ac3             	;                (0,4)

        mov     ac3, dbl(*ar1+)                 ; new yr=xr-ac0  (2,4)
||      sub     ac1,dbl(*ar0), ac2

        mov     ac2, dbl(*ar1+)                 ; new yi=xi-ac1  (2,4)
||      add     dbl(*ar0),ac1,ac3               ;                (4,4)

		mov     ac3, dbl(*ar0+)                 ; new xi=xi+ac1
||      add     #5, ar1                         ;                (4,4)      	       	
lgroup:	add		#4, ar0       	  				; jump to next group	       	  				
;-----------------------------------------------------------------------
; END last stage
;-----------------------------------------------------------------------
						
end_benchmark:
;-----------------------------------------------------------------------
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
        
