;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Processor:   C55xx
; Descripac1on: 32-bit radix-2 DIT complex iFFT using normal input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
;    First two stages are in radix-4.
; Usage:    void cifft32_NOSCALE (DATA *xy, ushort nx);
; Copyright Texas instruments Inc, 2002
; History:
;	- 07/17/2003	C. Iovescu changed the way the twiddle table is included
;***********************************************************************

;-----------------------------------------------------------------------
; Arguments passed to _ifft
; 	ar0       ->    ifftdata pointer
; 	t0        ->    ifft size
;-----------------------------------------------------------------------

;-----------------------------------------------------------------------
; Array declaraac1ons
;-----------------------------------------------------------------------

        .ref twiddle32

        .def _cifft32_NOSCALE     	; make funcac1on visible to other fnct
        .cpl_on
        .arms_off     				; enable assembler for arms mode
        .mmregs
        .noremark    5579, 5573
        
;-----------------------------------------------------------------------  
; Stack frame
;-----------------------------------------------------------------------
RET_ADDR_SZ       .set 1            ;return address
REG_SAVE_SZ       .set 0            ;save-on-enac0y registers saved
FRAME_SZ          .set 2            ;local variables
ARG_BLK_SZ        .set 0            ;argument block

PARAM_OFFSET      .set ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ + RET_ADDR_SZ

;-----------------------------------------------------------------------
; Local variables
;-----------------------------------------------------------------------            
       .asg    0, data_pac0
       .asg    1, data_sz

;-----------------------------------------------------------------------
; Temp data
;-----------------------------------------------------------------------
		.bss tempmem, 2, , 2
      
        .text           
_cifft32_NOSCALE

;-----------------------------------------------------------------------
; Condiac1onal compile
;-----------------------------------------------------------------------
SCALED	.set	1			; SCALED = 0 - not scaled version
						; SCALED = 1 - scaled version
;-----------------------------------------------------------------------
; Save any save-on-entry registers that are used
;-----------------------------------------------------------------------
		PSH	mmap(ST0_55)
    	PSH	mmap(ST1_55)
    	PSH	mmap(ST2_55)  
    	PSH	mmap(ST3_55)
    	PSH T2
    	PSH T3
		PSHBOTH XAR5
		PSHBOTH XAR6
		PSHBOTH XAR7

;-----------------------------------------------------------------------
; Allocate the local frame and argument block
;-----------------------------------------------------------------------
		AADD	#-(ARG_BLK_SZ + FRAME_SZ + REG_SAVE_SZ), SP

;-----------------------------------------------------------------------
; Save entry values for later
;-----------------------------------------------------------------------
		MOV AR0, *sp(data_pac0) ; 
   		MOV T0, *sp(data_sz)   ;

;-----------------------------------------------------------------------
; iFFT implementation
;
; The iFFT is implemented in three different steps:
;
;  1) - a radix-4 stage with twiddle factors only equal to -1, 0 and 1
;  2) - a group of log2(iFFT_SIZE)-3 radix-2 stages
;  3) - on out-of-place bit-reversal
;
;  No need to implement the last stage in a different way
;  to the other stages.        
;-----------------------------------------------------------------------
; Modificaac1on of status registers	  
      	BSET #FRCT, ST1_55          
      	BCLR #ARMS, ST2_55          
	  	BCLR #C54CM, ST1_55  
      
      	BSET SXMD
      	BCLR SATD
      	BSET M40
	                                   
;-----------------------------------------------------------------------
; First two stages computed as one radix-4 stage
;-----------------------------------------------------------------------      
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
        ; cr' =  (ar - cr) - (bi - di)
        ; ci' =  (ai - ci) - (br - dr)
        ;
        ; dr' =  (ar - cr) + (bi - di)
        ; di' =  (ai - ci) + (br - dr)
        ;        
        ; ar6  -> tempmem
        ;
        ; ar0-> a
        ; ar1-> b
        ; ar2-> c
        ; ar3-> d
        ;
        ; --------------------------------------------------------------        
       
    	MOV XAR0, XAR1					; AR0 contains    #(ifftdata) a
    	ADD *sp(data_pac0),T0, AR1		; b: ar1 = #(ifftdata+4*iFFT_SIZE/4)
	
		MOV XAR1, XAR2 
		ADD T0,AR2						; c: ar2 = #(ifftdata+4*iFFT_SIZE/2)
 	        
    	MOV XAR2, XAR3    
		ADD T0, AR3						; d: ar3 = #(ifftdata+4*3*iFFT_SIZE/4)
		
		SFTS T0, #-1					;T0 = iFFT_SIZE/4
		SFTS T0, #-1	
		SUB #1, T0
		
		AMOV #tempmem, XAR6
		MOV T0,BRC0
	        
    	RPTB stage12
;-----------------------------------------------------------------------
; Benchmark: 21 stages for stage1_2 loop
;-----------------------------------------------------------------------   	
		;Instruction					Ac0	Ac1	Ac2	Ac3	Ar0	Ar1	Ar2	Ar3    	
		mov dbl(*ar0), ac0				;ar				ar	br	cr	dr
		sub dbl(*ar2),ac0,ac3			;			ar-cr				
		add dbl(*ar2+),ac0,ac1			;	ar+cr				ci	
		mov dbl(*ar1),ac0				;br							
		sub ac0,dbl(*ar3+),ac2			;		dr-br				di
		mov ac2,dbl(*ar6) 	;ar6->dr-br								
	||	add ac0<<#1,ac2					;		dr+br					
		add ac2,ac1						;ar+cr+dr+br						
	|| 	mov dbl(*ar3-),ac0				;di							dr 
		mov ac1,dbl(*ar0+)				;				ai			
	|| 	sub ac2<<#1,ac1					;ar+cr-(dr+br)						
		mov ac1, dbl(*ar1+)				;					bi		 
		add dbl(*ar1),ac0,ac1			;	bi+di						 
		sub ac0, dbl(*ar1), ac2			;		bi-di					
		sub ac2, ac3					;			ar-cr-(bi-di)				
	|| 	mov dbl(*ar2-),ac0				;ci						cr	
		mov ac3,dbl(*ar2+)				;						ci	
	|| 	add ac2<<#1,ac3					;			ar-cr+(bi-di)				
		mov ac3, dbl(*ar3+)				;							di 
		sub ac0, dbl(*ar0), ac3			;			ai-ci				
		add dbl(*ar0),ac0				;ai+ci							
		add ac1,ac0						;ai+ci+di+bi							
	||	mov dbl(*ar6),ac2				;		dr-br					
		mov ac0, dbl(*ar0+)				;				arn			
	||	sub ac1<<#1,ac0					;ai+ci-(di+bi)							
		mov ac0, dbl(*ar1+)				;					brn		
	||	sub ac2,ac3						;			ai-ci-(dr-br)				
		mov ac3,dbl(*ar2+)				;						crn	
	||	add ac2<<#1,ac3					;			ai-ci+(dr-br)				
stage12:mov ac3,dbl(*ar3+)				;							drn
;-----------------------------------------------------------------------
; End of stage 1 and 2
;-----------------------------------------------------------------------    	
		
;-----------------------------------------------------------------------
; radix-2 stages (stages 3->log2(iFFT_SIZE) )  
; register usage
; ar0->Pr, ar1->Qr, ar3->twiddle
; ar4=Re distance of butterfly
; ar6=group count, t1=butterfly count, ar5= stage count  
;-----------------------------------------------------------------------
        ; main iniac1alizaac1on      	   

        ; modify ST2 to select linear or circular addressing modes
       	OR	#0x3, mmap(ST2_55)		; circular ar0,ar1        
       	MOV *sp(data_pac0), AR1		; ar1 = #ifftdata  

        ; circular buffer starac1ng addresses       	     	
       	MOV mmap(@AR1),bsa01		; circular buffer start address
       	
        ; circular buffer sizes 
        MPYMK *sp(data_sz),#2,AC0	; because FRCT==1, it actually x4
        MOV mmap(@AC0_L), bk03		; bk03 = (4*iFFT_SIZE-4), ar0-ar3
		MOV *sp(data_sz), T2
		SFTS T2,#-1					; T2 = iFFT_SIZE/2
    	MOV T2,AR4    				; AR4 = iFFT_SIZE/2(Re distance between p q)
    	SFTS T2,#-1
  	||  MOV	#4, AR6					; AR6 = group    
    	SFTS T2,#-1					; T2 = iFFT_SIZE/8
    	BCC end_benchmark, T2==#0
    	MOV T2, T1					; T1 = number of butterfly,
    	MOV T2, AR5					; AR5 = stage	       	      	 		 			
    	AMOV #twiddle32, XAR3        ; AR3->twiddle32	  


	    mov     #2, t0          	; moving from real->imag
        mov     #-2, t2         	; restoring cdp, and imag->real       	
                        
stage:  ; begining of a new stage
        ; stage initialization
        
        ; 1 - loop counter updates     
		SFTS AR5,#-1				; shift right stage count
	||	MOV #0,AR0		
		MOV XAR3, XCDP
		ADD #1,AR4,AR1				;AR1->QR_LOW
		ADD	#2,AR1,AR2				;AR2->QI_LOW
		   
        ; butterfly counter update		      		
        SUB #1,T1,T3        
        MOV T3, BRC1        		;butterflies loop count

        ; group counter update
        SUB #1,AR6,T3     
		MOV T3, BRC0              
       	
		RPTB group   	
;-----------------------------------------------------------------------
; Benchmark: 12 cycles for the butterfly loop
;-----------------------------------------------------------------------
       	rptb BFly 								;             (ar1,cdp)
        mpy     uns(*ar1), *(cdp+t0), ac0       ; ac0  = yrl*crh (1,0)
::      mpy     uns(*ar1(t0)), *(cdp+t0), ac1   ; ac1  = yil*crh (3,0)

        mas     uns(*ar1(t0)), *cdp+, ac0       ; ac0 -= yil*cih (3,2)
::      mac     uns(*ar1+), *cdp+, ac1          ; ac1 += yrl*cih (1,2)
||      swap    t0, t2                          ; t0=-2

        mas     *ar1, uns(*(cdp+t0)), ac0       ; ac0 -= yih*cil (2,3)
::      mac     *ar1(t0), uns(*(cdp+t0)), ac1   ; ac1 += yrh*cil (0,3)

        mac    *ar1(t0), uns(*cdp-), ac0       	; ac0 += yrh*crl (0,1)
::      mac    *(ar1+t0), uns(*cdp-), ac1      	; ac1 += yih*crl (2,1)
||      swap    t0, t2                          ; t0=2

        mac     *ar1, *(cdp+t0), ac0>>#16  		; ac0 += yrh*crh (0,0)
::      mac     *ar1(t0), *(cdp+t0), ac1>>#16   ; ac1 += yih*crh (2,0)

        mas     *ar1(t0), *(cdp+t0), ac0        ; ac0 -= yih*cih (2,2)
::      mac     *ar1, *(cdp+t0), ac1        	; ac1 += yrh*cih (0,2)

        add     dbl(*ar0), ac0,ac2
     	mar		*+cdp(-4)
        mov     ac2,dbl(*ar0)                 	; new xr=ac0+xr  (0,4)
||	    sub     ac0,dbl(*ar0+),ac3             	;                (0,4)

        mov     ac3, dbl(*ar1+)                 ; new yr=xr-ac0  (2,4)
||      sub     ac1,dbl(*ar0), ac2

        mov     ac2, dbl(*ar1+)                 ; new yi=xi-ac1  (2,4)
||      add     dbl(*ar0),ac1,ac3               ;                (4,4)

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
; End of radix-2 stage 
;-----------------------------------------------------------------------
				
end_benchmark:

;-----------------------------------------------------------------------
; De-allocate the local frame and argument block
;-----------------------------------------------------------------------
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
        
