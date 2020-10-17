;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function UNPACK
; Processor:   C55xx
; Decription: Unpacks the output of a Radix-2 DIF complex IFFT using bit-reversed input data
;    and bit-reversed twiddle table (length N/2, cosine/sine format)
; Usage:  void unpacki(DATA *xy, ushort nx);
; Copyright Texas instruments Inc, 2000
; History;
;	- 07/17/2003	C. Iovescu changed the way the twiddle table is included
;****************************************************************

            .mmregs
            .cpl_on
            .arms_off
            .ref twiddle

;//-----------------------------------------------------------------------------
;// Program section
;//-----------------------------------------------------------------------------

            .sect ".fftcode"
            .global _unpacki

_unpacki:

;//-----------------------------------------------------------------------------
;// Context save / get arguments
;//-----------------------------------------------------------------------------
            PSH        mmap(ST0_55)
            PSH        mmap(ST1_55)
            PSH        mmap(ST2_55)
            PSH        mmap(ST3_55)

            AADD       #-2,SP                   ; create local frame
            MOV        pair(T2),dbl(*SP(#00h))  ; save on entry

;//-----------------------------------------------------------------------------
;// Initialization code
;//-----------------------------------------------------------------------------

Initialize:
            AND         #0FF00h,mmap(ST2_55)    ; linear addr for CDP,AR2,AR3,AR0, AR1
                                                ; AR0, AR1
            BSET        #6,ST1_55               ; set FRCT
            BSET        #8,ST1_55               ; set SXMD
            BCLR        #9,ST1_55               ; set SATD
            BCLR        #15,ST2_55              ; reset ARMS
            BSET        #10,ST1_55              ; reset M40

;//-----------------------------------------------------------------------------
;// Unpack for IRFFT
;//-----------------------------------------------------------------------------
            MOV         XAR0,XAR1               ; AR1 = pointer to input data = rm[0]
            ADD         T0,AR1                  ; AR1 = pointer to input data = rm[N]
            SFTS        T0,#-1                  ; T0 = RFFT size/2 (req. for loop)
            MOV         T0,T1                   ; T1 = T0 = RFFT size/2
            SFTS        T1,#-1                  ; T1 = RFFT size/4 (req. for loop)
            SUB         #2,AR1                  ; element in the data buffer
            SUB         #2,T1                   ; loop = N/4 - 2
            MOV         T1,BRC0                 ; and store in repeat counter 
            MOV         #-1,T2
            AMOV        #twiddle,XAR2           ; pointer to sin and cos tables
            AMOV        #(twiddle+1),XAR3       ; 
            AMAR        *(AR2+T0B)              ; set to 2nd entry of bit reversed
            AMAR        *(AR3+T0B)              ; sin/cos table 
            
;--------------------------------------------------------------------------------
; process yre[0] (DC) and yre[0] (Nyquist)
; yre[0] = 1/2(xre[0] + xim[0])    store in yre[0] 
; yre[N] = 1/2(xre[0] - xim[0])    store in yim[0]
;
;Scaling by 2 added to avoid overflow
;--------------------------------------------------------------------------------
            MOV         *AR0+,AC1                  ; AC1=xre[0]
            ADD         *AR0,AC1,AC0               ; AC0=xre[0]+xim[0]
            SUB         *AR0-,AC1,AC1              ; AC1=xre[0]-xim[0]
            MOV			AC0 << #-2, *AR0+          ; yre[0]=0.5*xre[0]+xim[0]
            MOV			AC1 << #-2, *AR0+          ; yim[0]=0.5*xre[0]-xim[0]
;--------------------------------------------------------------------------------
; process y1re/im
;
;Scaling by 2 added to avoid overflow
;--------------------------------------------------------------------------------
            RPTB        unpacki_end             ; setup loopcounter (RFFT-size)/4 - 2
             ADD         *AR0,*AR1,AC0          ; AC0 = x1Re+x2Re   
             SUB         *AR0+,*AR1+,AC3        ; AC3 = x1Re-x2Re
             SUB         *AR0,*AR1,AC1          ; AC1 = x1Im-x2Im
             ADD         *AR0-,*AR1-,AC2        ;  
             NEG		 AC2                    ; AC2 = -(x1Im+x2Im)
             SFTL        AC2,#-1,AC2            ; im = 0.5*AC3 = -0.5*(x1Re-x2Re)
             SFTL        AC3,#-1,AC3            ; rm = 0.5*AC2 = 0.5*(x1Im+x2Im)
             SFTL        AC0,#-1,AC0            ; rp = 0.5*AC0 = 0.5*(x1Re+x2Re)
             SFTL        AC1,#-1,AC1            ; ip = 0.5*AC1 = 0.5*(x1Im-x2Im)
             MOV         HI(AC2),T1             ; save rm to T1
             MOV         HI(AC3),T3             ; save im to T3  

;-----------------------------------------------------------------------
             MASM        *AR2,T1,AC0,AC2        ; y2re=AC2=rp-cos*rm
             MASM        *AR2,T3,AC1,AC3        ; y2im=AC3=ip-cos*im
             MACM        *AR2,T1,AC0,AC0        ; y1re=AC0=rp+cos*rm
             MACM        *(AR2+T0B),T3,AC1,AC1  ; y1im=AC1=ip+cos*im
;-----------------------------------------------------------------------
             ; y1re=rp+cos*rm-sin*im
             MASM        *AR3,T3,AC0,AC0        
             ; y1im=ip+cos*im+sin*rm                                         
             MACM        *AR3,T1,AC1,AC1 :: MOV         HI(AC0<<T2),*AR0+       
             ; y2re=-rp-cos*rm+sin*im
             MACM        *AR3,T3,AC2,AC2 :: MOV         HI(AC1<<T2),*AR0+       
             ; y2im=ip-cos*im-sin*rm
             MASM        *(AR3+T0B),T1,AC3,AC3       
             NEG		 AC3
             MOV         HI(AC2<<T2),*AR1+
             MOV         HI(AC3<<T2),*AR1 

unpacki_end: SUB         #3,AR1                 ; adjust to next rm
;//-----------------------------------------------------------------------------
;       yre(N/2) = yre(N/2)
;       yim(N/2) = - yim(N/2)
;
;Scaling by 2 added to avoid overflow
;//-----------------------------------------------------------------------------
            MOV         dbl(*AR0),pair(HI(AC0))
            NEG         AC1,AC1
            SFTS        AC0,#-1,AC0            
            SFTS        AC1,#-1,AC1            
            MOV         pair(HI(AC0)),dbl(*AR0)

;//-----------------------------------------------------------------------------
;// Context restore
;//-----------------------------------------------------------------------------

            MOV         dbl(*SP(#00h)),pair(T2)
            AADD        #2,SP                  ; destroy local frame
            POP         mmap(ST3_55)
            POP         mmap(ST2_55)
            POP         mmap(ST1_55)
            POP         mmap(ST0_55)

;//-----------------------------------------------------------------------------
;// Return
;//-----------------------------------------------------------------------------
            RET

        .end
