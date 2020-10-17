;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function UNPACK32
; Processor:   C55xx
; Decription: Unpacks the output of a Radix-2 DIF complex FFT using bit-reversed input 
;    data and bit-reversed twiddle table (length N/2, cosine/sine format).
;
; Usage:  void unpack(DATA *xy, ushort nx);
;
; Copyright Texas instruments Inc, 2000
; History;
;	- 11/20/2003	C. Iovescu initial implementation
;
;************************************************************************************
;
;  DFT of N-point real-valued sequence
;
; Implementation of the rfft based on the equations:
;
;   
;
;  g(n) n=0:N-1 is a real valued sequence. Purpose of the code
;  is to compute the RFFT of this signal: G(k) k=0:N-1 complex sequence. 
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
;  Compute the CFFT of x(n):
;
;        X(k) k=0:N/2-1
;
;  Derive from X(k) the CFFT of xe(n) and xo(n) using the equations
;
;       Xe(k) =  0.5  (X(k) + X*(N/2-k))   k=0:N/2-1  (1)
;       Xo(k) = -0.5j (X(k) - X*(N/2-k))   k=0:N/2-1  (2)
;
;  Separate in Real and Imag parts: 
;
;   Define: 
;            Xe(k) =  Xer(k)+jXei(k)
;            Xo(k) =  Xor(k)+jXoi(k)
;
;   Equations (1) and (2) yield:
;
;       Xer(k) =  0.5  (Xr(k) + Xr(N/2-k))   k=0:N/2-1  (3)
;       Xei(k) =  0.5  (Xi(k) - Xi(N/2-k))   k=0:N/2-1  (4)
;       Xor(k) =  0.5  (Xi(k) + Xi(N/2-k))   k=0:N/2-1  (5)
;       Xoi(k) = -0.5  (Xr(k) - Xr(N/2-k))   k=0:N/2-1  (6)
;
;   The previous equations have special values for:
;
;   DC Offset: 
;             k=0     Xer(0)= Xr(0)
;                     Xei(0)= 0
;                     Xor(0)= Xi(0)
;                     Xoi(0)= 0
;
;
;   Nyquist Frequency:
;             k=N/4   Xer(N/4)= Xr(N/4)
;                     Xei(N/4)= 0
;                     Xor(N/4)= Xi(N/4)
;                     Xoi(N/4)= 0
;
;
;    Computing G(k)
;
;    G(k)   = Xe(k) + W(k,N)Xo(k)     k = 0:N/2-1   (7)
;    G(N/2-k) = Xe*(k) - W(-k,N)Xo*(k)  k = 0:N/2-1   (8)
;
;  Separate in Real and Imag parts: 
;
;   Define: 
;            G(k) =  Gr(k)+jGi(k)
;            G(N-k) =  Gr(N-k)+jGi(N-k)
;            W(k,N) = cos(2Pik/N)-jsin(2Pik/N) = Wr(k)-jWi(k)
;
;   Equations (7) and (8) yield:
;
;          Gr(k)     = Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)   (9)
;          Gi(k)     = Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)   (10)
;          Gr(N/2-k) = Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)   (11)
;          Gi(N/2-k) =-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)   (12)
;
;
;  Equations (9) through (12) will be DIVIDED BY TWO in order to avoid
;  overflow.
;
;          Gr(k)     = 0.5[Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)]   (13)
;          Gi(k)     = 0.5[Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]   (14)
;          Gr(N/2-k) = 0.5[Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)]   (15)
;          Gi(N/2-k) =0.5[-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]   (16)
;
;  Special values:
;        
;     * DC Offset  k = 0                                    (17)
;
;           Gr(0) = 0.5 (Xr(0)+Xi(0)) 
;           Gi(0) = 0
;
;     * k = N/4                                             (18)
;
;           Gr(N/4) = 0.5 Xr(N/4) 
;           Gi(N/4) =-0.5 Xi(N/4)
;
;     * Nyquist Frequency  k = N/2                          (19)
;
;           Gr(N/2) = 0.5 (Xr(0)-Xi(0)) 
;           Gi(N/2) = 0
;
;
;  Practical computation of G(k) k=0:N-1
;      
;      1) Compute G(k) k=0:N/2
;             - G(0),G(N/4), G(N/2) based on special values formulae
;             - G(k) for   (0<k<N/2)
;      2) Deduct G(k) k=N/2+1:N-1 from the values computed in 1) using
;      the complex conjugate symmetry formulae (since g(n) is a real
;      sequence) 
;                   
;              G(k) = G*(N-k)  k=0:N-1
;
;  Algorithm implementation:
;    
;
;     The algorithm computes only G(k) k=0:N/2. In order to store the
;     result in the input array, G(0) and G(N/2) which have zero imag parts are
;     packed together and Gr(N/2) is stored at the location of Gi(0).
;
;        1) Compute Xer(k), Xei(k), Xor(k), Xoi(k) for k=1:N/4-1
;               ( k=0 and k=N/4 are special values)
;
;  
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

                .sect ".text:unpack32"
                .global _unpack32

_unpack32:

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
;// Unpack for RFFT
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
;  Special values G(0) and G(N/2):
;        
;     * DC Offset  k = 0                                    
;
;           Gr(0) = 0.5 (Xr(0)+Xi(0)) 
;           Gi(0) = 0
;
;
;     * Nyquist Frequency  k = N/2                          
;
;           Gr(N/2) = 0.5 (Xr(0)-Xi(0)) 
;           Gi(N/2) = 0
;
;     In order to store G(k) in the input array, Gr(0) and Gr(N/2) 
;     are packed as real&imag values.
;
;--------------------------------------------------------------------------------
            MOV         dbl(*AR0+),AC1           ; AC1 = Xr[0]
            ADD         dbl(*AR0),AC1,AC0        ; AC0 = Xr[0] + Xi[0]          										             
            SUB         dbl(*AR0-),AC1,AC1     	 ; AC1 = Xr[0] - Xi[0]
       
            SFTS		AC0, #-1				 ; 0.5x
            SFTS		AC1, #-1				 ; 0.5x
                      
            MOV			AC0, dbl(*AR0+)          ; Gr(0)
            MOV			AC1, dbl(*AR0+)          ; Gr(N/2)
;--------------------------------------------------------------------------------
; Step 2: 
;
; General loop G(k) k=1:N/2-1  (k<>N/4)
;
;    Xer(k) =  0.5  (Xr(k) + Xr(N/2-k))  k=1:N/4-1  
;    Xei(k) =  0.5  (Xi(k) - Xi(N/2-k))  k=1:N/4-1 
;    Xor(k) =  0.5  (Xi(k) + Xi(N/2-k))  k=1:N/4-1  
;    Xoi(k) = -0.5  (Xr(k) - Xr(N/2-k))  k=1:N/4-1  
;
;--------------------------------------------------------------------------------
            RPTB        unpack_end              ; setup loopcounter (RFFT-size)/4 - 2

            MOV         dbl(*AR1+),AC1          ; AC1= Xr[N/2-k]           								 	
            ADD         dbl(*AR0),AC1,AC0       ; Xer = AC0 =   Xr[k] + Xr[N/2-k]  
    		SUB         dbl(*AR0+),AC1,AC3      ; Xoi = AC3 = -(Xr[k] - Xr[N/2-k])
    		
            MOV         dbl(*AR0-),AC2          ; AC2 = Xi[k]                 
            SUB			dbl(*AR1), AC2, AC1	    ; Xei = AC1 =  Xi[k] - Xi[N/2-k]             
            ADD         dbl(*AR1-),AC2,AC2      ; Xor = AC2 =  Xi[k] + Xi[N/2-k]

            SFTS        AC0,#-1                 ; Xer = 0.5*AC0
            SFTS        AC1,#-1                 ; Xei = 0.5*AC1 
            SFTS        AC2,#-1                 ; Xor = 0.5*AC2
            SFTS        AC3,#-1                 ; Xoi = 0.5*AC3
                                             
            MOV         AC0 ,dbl(*SP(#00h))     ; save Xer
            MOV         AC1 ,dbl(*SP(#02h))     ; save Xei            
            MOV         AC2 ,dbl(*SP(#04h))     ; save Xor
            MOV         AC3 ,dbl(*SP(#06h))     ; save Xoi
            
;-----------------------------------------------------------------------
;
;   Output N-point RFFT
;
;    Gr(k)     = 0.5[ Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)]   
;    Gi(k)     = 0.5[ Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]   
;    Gr(N/2-k) = 0.5[ Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)]   
;    Gi(N/2-k) = 0.5[-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]  
;
;    Wr(k)     = cos(2Pik/N)
;    Wi(k)     = sin(2Pik/N)
;
;--------------------------------------------------------------------------------


             ; Wr(k)Xor(k)
			
			 ;  AR2 -> cos_H
			 ;		   cos_L
			 ; 
			 ;  AR4 -> Xor_H
			 ;	       Xor_L
			 ;
			 

             AMAR *AR2+
             MPYM uns(*AR2-), *AR4+, AC0	    ; AC0 = cos_L*Xor_H

             MACM *AR2, uns(*AR4-), AC0		    ; AC0 = AC0 + cos_H*Xor_L
             MACM *AR2+, *AR4, AC0 >> #16, AC0	; AC0 = AC0>>16 + cos_H*Xor_H 
             MOV  AC0 ,dbl(*SP(#08h))           ; save cos*Xor

             
             ; Wi(k)Xor(k)
			
			 ;  AR3 -> sin_H
			 ;	       sin_L
			 ; 
			 ;  AR4 -> Xor_H
			 ;	       Xor_L
			 ;
			 
			 AMAR *AR3+
             MPYM uns(*AR3-), *AR4+, AC0	    ; AC0 = sin_L*Xor_H
             MACM *AR3, uns(*AR4-), AC0		    ; AC0 = AC0 + sin_H*Xor_L
             MACM *AR3+, *AR4+, AC0 >> #16, AC0	; AC0 = AC0>>16 + sin_H*Xor_H 
             MOV  AC0 ,dbl(*SP(#0Ah))           ; save sin*Xor
			 AMAR *AR4+
			 
			 
             ; Wr(k)Xoi(k)
			
			 ;         cos_H
			 ;	AR2 -> cos_L
			 ; 
			 ;  AR4 -> Xoi_H
			 ;	       Xoi_L
			 ;
			 
			 
             MPYM uns(*AR2-), *AR4+, AC0	    ; AC0 = cos_L*Xoi_H
             MACM *AR2, uns(*AR4-), AC0		    ; AC0 = AC0 + cos_H*Xoi_L
             MACM *AR2, *AR4, AC0 >> #16, AC0	; AC0 = AC0>>16 + cos_H*Xoi_H 
             MOV  AC0 ,dbl(*SP(#0Ch))           ; save cos*Xoi
             
             			 			 
   
             ; Wi(k)Xoi(k)
			
			 ;         sin_H
			 ;	AR3 -> sin_L
			 ; 
			 ;  AR4 -> Xoi_H
			 ;	       Xoi_L
			 ;
			 
			 
            
             MPYM uns(*AR3-), *AR4+, AC0	    ; AC0 = sin_L*Xoi_H
             MACM *AR3, uns(*AR4-), AC0		    ; AC0 = AC0 + sin_H*Xoi_L
             MACM *AR3, *AR4, AC0 >> #16, AC0	; AC0 = AC0>>16 + sin_H*Xoi_H 
             MOV  AC0 ,dbl(*SP(#0Eh))           ; save sin*Xoi
       		             
          
          
          	; update AR4, local var pointer for next loop iteration 
          	SUB	        #2, AR4

            
            ; update the sin/cos pointers
            ; bit-reversed addressing used because twiddle table 
            ; is in bit-reversed format and normal format is needed
            ; in this algorithm.
            
         ;   !!!this requires special alignement of twiddle table ??


         	 ;  AR2 -> cos_H
			 ;	       cos_L         
         	 ;  AR3 -> sin_H
			 ;	       sin_L
         
         
            AMAR 	*(AR3+T0B)		; sin
            AMAR 	*(AR2+T0B)      ; cos
                
            
            
;    Gr(k)     = 0.5[ Xer(k) + Wr(k)Xor(k)+Wi(k)Xoi(k)]            
                                                                                                  
            MOV         dbl(*SP(#00h)),AC0       ; AC0 = Xer(k)           								 	 
            ADD         dbl(*SP(#08h)),AC0,AC1   ; AC1 = Xer(k)+Wr(k)Xor(k)          										             
            ADD         dbl(*SP(#0Eh)),AC1,AC1   ; AC1 = Xer(k)+Wr(k)Xor(k)+Wi(k)Xoi(k)
            SFTS		AC1, #-1				 ; 0.5x
            MOV 		AC1, dbl(*AR0+)          ; Gr(k)
                                                                                                                   
;    Gi(k)     = 0.5[ Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]                                                                                                                                                            
            
            MOV         dbl(*SP(#02h)),AC1       ; AC1 = Xei(k) 
            ADD         dbl(*SP(#0Ch)),AC1,AC2   ; AC2 = Xei(k)+ Wr(k)Xoi(k)  
            SUB         dbl(*SP(#0Ah)),AC2,AC2   ; AC2 = Xei(k)+ Wr(k)Xoi(k)-Wi(k)Xor(k)  
            SFTS		AC2, #-1				 ; 0.5x    
            MOV 		AC2, dbl(*AR0+)			 ; Gi(k)
                 
            
;    Gr(N/2-k) = 0.5[ Xer(k) - Wr(k)Xor(k)-Wi(k)Xoi(k)]                
             
            MOV         dbl(*SP(#00h)),AC1       ; AC1 = Xer(k) 
            SUB         dbl(*SP(#08h)),AC1,AC2   ; AC2 = Xer(k)- Wr(k)Xor(k)  
            SUB         dbl(*SP(#0Eh)),AC2,AC2   ; AC2 = Xer(k)- Wr(k)Xor(k)-Wi(k)Xoi(k)  
            SFTS		AC2, #-1				 ; 0.5x    
            MOV 		AC2, dbl(*AR1+)			 ; Gr(N/2-k)            
             
;    Gi(N/2-k) = 0.5[-Xei(k) + Wr(k)Xoi(k)-Wi(k)Xor(k)]                
             
            MOV         dbl(*SP(#0Ch)),AC1       ; AC1 = Wr(k)Xoi(k) 
            SUB         dbl(*SP(#02h)),AC1,AC2   ; AC2 = -Xei(k)+ Wr(k)Xoi(k)  
            SUB         dbl(*SP(#0Ah)),AC2,AC2   ; AC2 = -Xei(k)+ Wr(k)Xoi(k)-Wi(k)Xor(k)  
            SFTS		AC2, #-1				 ; 0.5x    
            MOV 		AC2, dbl(*AR1)			 ; Gi(N/2-k)             
 
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
