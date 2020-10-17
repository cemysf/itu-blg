;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function UNPACKI32
; Processor:   C55xx
; Decription: Unpacks the output of a Radix-2 DIF complex FFT using bit-reversed input 
;    data and bit-reversed twiddle table (length N/2, cosine/sine format).
;
; Usage:  void unpacki32(DATA *xy, ushort nx);
;
; Copyright Texas instruments Inc, 2000
; History;
;	- 11/20/2003	C. Iovescu initial implementation
;
;************************************************************************************
;
;  IDFT of N-point frequency domain sequence obtained from
;  a real-valued sequence.      
;
; Implementation of the rifft based on the derivation
;   
;  g(n) n=0:N-1 is a real valued sequence. The RFFT of this signal is
;  denoted G(k) k=0:N-1 complex sequence. The objective of the code is to
;  recover g(n) based on G(k).
;
;  g(n) is split in two real sequences, odd and even part
;    
;          xe(n) = g(2n)    n=0:N/2-1
;          xo(n) = g(2n+1)  n=0:N/2-1
;
;  Form the complex sequence:
;
;         x(n) = xe(n) + jxo(n)  n=0:N/2-1
;
;  The CFFT of x(n)can be expressed as:
;
;        X(k) k=0:N/2-1
;
;        X(k) = Xe(k) +j*Xo(k) k=0:N/2-1                (1)
;
;  The RFFT of g(n)can be expressed as:
;
;      G(k)     = Xe(k) + W(k,N)Xo(k)     k = 0:N/2-1   (2)
;      G(N/2+k) = Xe(k) - W(k,N)Xo(k)     k = 0:N/2-1   (3)
;
;   where W(k,n) = cos(2*PI*k/N)-j*sin(2*PI*k/N)
;         W(k,n) = Wr(k)-j*Wi(k)
;
;  (2) and (3) yield
;
;      Xe(k) = (G(k) + G(N/2+k))/2          k = 0:N/2-1       
;      Xo(k) = (G(k) - G(N/2+k))/(2*W(k,N)) k = 0:N/2-1
;
;  since g(n) is a real valued sequence the DFT has the complex
;  conjugate symmetry:
;
;     G(k) = G*(N-k)                      k = 0:N-1     (4)
;
;   And since 1/W(k,N) = W(-k, N)
;   Therefore:
;   
;     Xe(k) = (G(k) + G*(N/2-k))/2          k = 0:N/2-1  (5) 
;     Xo(k) = W(-k,N)(G(k) - G*(N/2-k))/2   k = 0:N/2-1  (6)
;
;  Separate in Real and Imag parts: 
;
;    Xr(k)+j*Xi(k) = (Xer(k)+ j*Xei(k)) +j*(Xor(k)+jXoi(k)) k=0:N/2-1 
;
;  define:
;
;     Grp(k) = (Gr(k) + Gr(N/2-k))/2   k = 0:N/2-1     (7)
;     Grm(k) = (Gr(k) - Gr(N/2-k))/2   k = 0:N/2-1     (8)
;     Gip(k) = (Gi(k) + Gi(N/2-k))/2   k = 0:N/2-1     (9)
;     Gim(k) = (Gi(k) - Gi(N/2-k))/2   k = 0:N/2-1     (10)
;
;
;    Xr(k)     = 0.5 [Grp(k)-Gip(k)*Wr(k)-Grm(k)*Wi(k)]       k = 0:N/2-1  (11)
;    Xi(k)     = 0.5 [Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]       k = 0:N/2-1  (12)
;    Xr(N/2-k) = 0.5 [Grp(k)+Gip(k)*Wr(k)+Grm(k)*Wi(k)]       k = 0:N/2-1  (13)
;    Xi(N/2-k) = 0.5 [-Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]       k = 0:N/2-1  (14)
;       
;  Special values:
;        
;     * DC Offset  k = 0                                 
;
;     Xr(0) = 0.5*0.5*(Gr(0)+Gr(N/2))
;     Xi(0) = 0.5*0.5*(Gr(0)-Gr(N/2))
;
;    This was derived based on:
;
;           Wr(0) = 1
;           Wi(0) = 0
;           Gi(0) = Gi(N/2) = 0
;
;     * Nyquist Frequency  k = N/4                          
;
;      Xr(N/4) =  0.5*Gr(N/4) 
;      Xi(N/4) = -0.5*Gi(N/4)
;
;     This was derived based on:
;
;           Wr(N/4) = 0
;           Wi(N/4) = 1
;
;
;****************************************************************

                .mmregs
                .cpl_on
                .arms_off
                .ref twiddle32

;//-----------------------------------------------------------------------------
;// Program section
;//-----------------------------------------------------------------------------

                .sect ".text:unpacki32"
                .global _unpacki32

_unpacki32:

;//-----------------------------------------------------------------------------
;// Context save / get arguments
;//-----------------------------------------------------------------------------
  
; upon entry stack aligned on 32-bit boundary
  
      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  
      PSH	mmap(ST3_55)

      AADD        #-21,SP             ; create local frame
	  
	  
;//-----------------------------------------------------------------------------
;// Initialization code
;//-----------------------------------------------------------------------------

Initialize:
            AND         #0FF00h,mmap(ST2_55)    ; linear addr for CDP,AR2,AR3,AR0, AR1

            BSET        #6,ST1_55               ; set FRCT
            BSET        #8,ST1_55               ; set SXMD

            ; SATD = 0 required for 32-bit multiplication
            BCLR        #9,ST1_55               ; set SATD
           
            BCLR        #15,ST2_55              ; reset ARMS
            BCLR        #10,ST1_55              ; reset M40

;//-----------------------------------------------------------------------------
;// Unpack for RIFFT
;//
;//  T0 = N (Rfft size) 
;//
;//
;//
;//-----------------------------------------------------------------------------
            MOV         XAR0,XAR1               ; AR0 = start ptr input data = Xr[0]
            ADD         T0,AR1                  ; AR1 = end ptr input data 
            ADD         T0,AR1                  ; 32-bit data 
            MOV         T0,T1                   ; T1 = T0 = RFFT size/2
            SFTS        T1,#-1                  ; T1 = RFFT size/2 
            SFTS        T1,#-1                  ; T1 = RFFT size/4 (req. for loop)
            SUB         #4,AR1                  ; AR1 = Xr[N/2-1] - last 32-bit elt
            SUB         #2,T1                   ; loop = N/4 - 2
            MOV         T1,BRC0                 ; and store in repeat counter
            AMOV        #twiddle32,XAR2         ; pointer to sin and cos tables
            AMOV        #(twiddle32+2),XAR3     ; 32-bit values (add 2)
            AMAR        *(AR2+T0B)              ; set to 2nd entry of bit reversed
            AMAR        *(AR3+T0B)              ; sin/cos table 
												; T0 = RFFT size for bitrev because 32-bit values
			MOV         XSP,XAR4   				; XAR4 local var ptr (stack)
			ADD	        #4, AR4

;--------------------------------------------------------------------------------
; Step1: 
;  Special values X(0):
;        
;     * DC Offset  k = 0                                    
;
;           Xr(0) = 0.5*0.5 (Gr(0)+Gi(N/2)) 
;           Xi(0) = 0.5*0.5 (Gr(0)-Gi(N/2))
;
;     Note: Gi(N/2) is stored as the imag part of G(0).
;
;--------------------------------------------------------------------------------
            MOV         dbl(*AR0+),AC1           ; AC1 = Gr[0]
            ADD         dbl(*AR0),AC1,AC0        ; AC0 = Gr[0] + Gi[N/2]          										             
            SUB         dbl(*AR0-),AC1,AC1     	 ; AC1 = Gr[0] - Gi[N/2]
       
            SFTS		AC0, #-2			 ; 0.25x
            SFTS		AC1, #-2			 ; 0.25x
                      
            MOV			AC0, dbl(*AR0+)    ; Xr(0)
            MOV			AC1, dbl(*AR0+)    ; Xi(0)
;--------------------------------------------------------------------------------
; Step 2: 
;
; General loop X(k) k=1:N/2-1  k<>N/4 (X(k)&X(N/2-k) computed in same iteration)
;  
;     Grp(k) = 0.5 (Gr(k) + Gr(N/2-k))   k = 1:N/4-1     
;     Grm(k) = 0.5 (Gr(k) - Gr(N/2-k))   k = 1:N/4-1     
;     Gip(k) = 0.5 (Gi(k) + Gi(N/2-k))   k = 1:N/4-1     
;     Gim(k) = 0.5 (Gi(k) - Gi(N/2-k))   k = 1:N/4-1      
;
;--------------------------------------------------------------------------------
            RPTB        unpack_end              ; setup loopcounter (RFFT-size)/4 - 2

            MOV         dbl(*AR0+),AC1          ; AC1 = Gr[k]           								 	
            ADD         dbl(*AR1),AC1,AC0       ; Grp = AC0 =   Gr[k] + Gr[N/2-k]  
    		SUB         dbl(*AR1+),AC1,AC3      ; Grm = AC3 =   Gr[k] - Gr[N/2-k]
    		
            MOV         dbl(*AR0-),AC2          ; AC2 = Gi[k]                 
            ADD			dbl(*AR1), AC2, AC1		; Gip = AC1 =  Gi[k] + Gi[N/2-k]             
            SUB         dbl(*AR1-),AC2,AC2      ; Gim = AC2 =  Gi[k] - Gi[N/2-k]

            SFTS        AC0,#-1                 ; Grp = 0.5*AC0
            SFTS        AC1,#-1                 ; Gip = 0.5*AC1 
            SFTS        AC2,#-1                 ; Gim = 0.5*AC2
            SFTS        AC3,#-1                 ; Grm = 0.5*AC3
                                             
            MOV         AC0 ,dbl(*SP(#00h))     ; save Grp
            MOV         AC1 ,dbl(*SP(#04h))     ; save Gip            
            MOV         AC2 ,dbl(*SP(#02h))     ; save Gim
            MOV         AC3 ,dbl(*SP(#06h))     ; save Grm
            
;-----------------------------------------------------------------------
;
;   Output for N/2-point CIFFT
;
;    Xr(k)     = 0.5 [Grp(k)-Gip(k)*Wr(k)-Grm(k)*Wi(k)]      
;    Xi(k)     = 0.5 [Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]       
;    Xr(N/2-k) = 0.5 [Grp(k)+Gip(k)*Wr(k)+Grm(k)*Wi(k)]       
;    Xi(N/2-k) = 0.5 [-Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]         
;
;    Wr(k)     = cos(2Pik/N)
;    Wi(k)     = sin(2Pik/N)
;
;--------------------------------------------------------------------------------


             ; Wr(k)Gip(k)
			
			 ;  AR2 -> cos_H
			 ;	     cos_L
			 ; 
			 ;  AR4 -> Gip_H
			 ;	     Gip_L
			 ;
			 

             AMAR *AR2+
             MPYM uns(*AR2-), *AR4+, AC0	    ; AC0 = cos_L*Gip_H

             MACM *AR2, uns(*AR4-), AC0		    ; AC0 = AC0 + cos_H*Gip_L
             MACM *AR2+, *AR4, AC0 >> #16, AC0	; AC0 = AC0>>16 + cos_H*Gip_H 
             MOV  AC0 ,dbl(*SP(#08h))           ; save cos*Gip

             
             ; Wi(k)Gip(k)
			
			 ;  AR3 -> sin_H
			 ;	     sin_L
			 ; 
			 ;  AR4 -> Gip_H
			 ;	     Gip_L
			 ;
			 
			 AMAR *AR3+
             MPYM uns(*AR3-), *AR4+, AC0	    ; AC0 = sin_L*Gip_H
             MACM *AR3, uns(*AR4-), AC0		    ; AC0 = AC0 + sin_H*Gip_L
             MACM *AR3+, *AR4+, AC0 >> #16, AC0	; AC0 = AC0>>16 + sin_H*Gip_H 
             MOV  AC0 ,dbl(*SP(#0Ah))           ; save sin*Gip
			 AMAR *AR4+
			 
			 
             ; Wr(k)Grm(k)
			
			 ;         cos_H
			 ;  AR2 -> cos_L
			 ; 
			 ;  AR4 -> Grm_H
			 ;	     Grm_L
			 ;
			 
			 
             MPYM uns(*AR2-), *AR4+, AC0	    ; AC0 = cos_L*Grm_H
             MACM *AR2, uns(*AR4-), AC0		    ; AC0 = AC0 + cos_H*Grm_L
             MACM *AR2, *AR4, AC0 >> #16, AC0	; AC0 = AC0>>16 + cos_H*Grm_H 
             MOV  AC0 ,dbl(*SP(#0Ch))           ; save cos*Grm
             
             			 			 
   
             ; Wi(k)Grm(k)
			
			 ;         sin_H
			 ;	AR3 -> sin_L
			 ; 
			 ;  AR4 -> Grm_H
			 ;	       Grm_L
			 ;
			 
			 
            
             MPYM uns(*AR3-), *AR4+, AC0	    ; AC0 = sin_L*Grm_H
             MACM *AR3, uns(*AR4-), AC0		    ; AC0 = AC0 + sin_H*Grm_L
             MACM *AR3, *AR4, AC0 >> #16, AC0	; AC0 = AC0>>16 + sin_H*Grm_H 
             MOV  AC0 ,dbl(*SP(#0Eh))           ; save sin*Grm
       		             
          
          
          	; update AR4, local var pointer for next loop iteration 
          	SUB	        #2, AR4

            
            ; update the sin/cos pointers
            ; bit-reversed addressing used because twiddle table 
            ; is in bit-reversed format and normal format is needed
            ; in this algorithm.
            
         


         	 ;  AR2 -> cos_H
			 ;	       cos_L         
         	 ;  AR3 -> sin_H
			 ;	       sin_L
         
         
            AMAR 	*(AR3+T0B)		; sin
            AMAR 	*(AR2+T0B)      ; cos
                
            
;     Xr(k)     =0.5 [Grp(k)-Gip(k)*Wr(k)-Grm(k)*Wi(k)]                       
                                                                                                  
            MOV         dbl(*SP(#00h)),AC0       ; AC0 = Grp(k)           								 	 
            SUB         dbl(*SP(#08h)),AC0,AC1   ; AC1 = Grp(k)-Wr(k)Gip(k)          										             
            SUB         dbl(*SP(#0Eh)),AC1,AC1   ; AC1 = Grp(k)-Wr(k)Gip(k)-Wi(k)Grm(k)
            SFTS		AC1, #-1				 ; 0.5x
            MOV 		AC1, dbl(*AR0+)          ; Xr(k)
 

;    Xi(k)     =0.5 [Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]                                                                                                                        
                                                                                                                                                            
            
            MOV         dbl(*SP(#02h)),AC1       ; AC1 = Gim(k) 
            ADD         dbl(*SP(#0Ch)),AC1,AC2   ; AC2 = Gim(k)+ Wr(k)Grm(k)  
            SUB         dbl(*SP(#0Ah)),AC2,AC2   ; AC2 = Gim(k)+ Wr(k)Grm(k)-Wi(k)Gip(k)  
            SFTS		AC2, #-1				 ; 0.5x    
            MOV 		AC2, dbl(*AR0+)			 ; Xi(k)
                 

;    Xr(N/2-k) =0.5 [Grp(k)+Gip(k)*Wr(k)+Grm(k)*Wi(k)]                   
             
             
            MOV         dbl(*SP(#00h)),AC1       ; AC1 = Grp(k) 
            ADD         dbl(*SP(#08h)),AC1,AC2   ; AC2 = Grp(k)+ Wr(k)Gip(k)  
            ADD         dbl(*SP(#0Eh)),AC2,AC2   ; AC2 = Grp(k)+ Wr(k)Gip(k)+Wi(k)Grm(k)  
            SFTS		AC2, #-1				 ; 0.5x    
            MOV 		AC2, dbl(*AR1+)			 ; Xr(N/2-k)            

;    Xi(N/2-k) =0.5 [-Gim(k)+Grm(k)*Wr(k)-Gip(k)*Wi(k)]                              
             
            MOV         dbl(*SP(#0Ch)),AC1       ; AC1 = Wr(k)Grm(k) 
            SUB         dbl(*SP(#02h)),AC1,AC2   ; AC2 = -Gim(k)+ Wr(k)Grm(k)  
            SUB         dbl(*SP(#0Ah)),AC2,AC2   ; AC2 = -Gim(k)+ Wr(k)Grm(k)-Wi(k)Gip(k)  
            SFTS		AC2, #-1				 ; 0.5x    
            MOV 		AC2, dbl(*AR1)			 ; Xi(N/2-k)             
 
unpack_end: SUB         #6,AR1                   ; adjust to Gr(N/2-k-1)          
                        

;--------------------------------------------------------------------------------
; Step3: 
;  Special values G(N/4):
;
;           Gr(N/4) = 0.5 Xr(N/4) 
;           Gi(N/4) =-0.5 Xi(N/4)
;
;//-----------------------------------------------------------------------------
            MOV         dbl(*AR0+),AC0		; Xr(N/4)
            MOV         dbl(*AR0-) ,AC1		; Xi(N/4)          
            NEG         AC1,AC1				;-Xi(N/4)
            SFTS        AC0,#-1,AC0 		; 0.5*Xr(N/4)           
            SFTS        AC1,#-1,AC1  		;-0.5*Xi(N/4)          
            MOV         AC0 ,dbl(*AR0+)		;Gr(N/4) = 0.5 Xr(N/4)
    		MOV         AC1 ,dbl(*AR0+)		;Gi(N/4) =-0.5 Xi(N/4)        
                      
            
;//-----------------------------------------------------------------------------
;// Context restore
;//-----------------------------------------------------------------------------
            AADD        #21,SP                  ; destroy local frame
;//-----------------------------------------------------------------------------
;// Return
;//-----------------------------------------------------------------------------
      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
            RET

        .end
