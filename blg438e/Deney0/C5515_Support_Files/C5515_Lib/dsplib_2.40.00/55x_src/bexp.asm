;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:    bexp
; Version:     2.0
; Processor:   C55xx
; Description: block exponent
; Useage: short r_maxexp = bexp (DATA *x, ushort nx)
;  
; Copyright Texas instruments Inc, 2000
;-----------------------------------------------------------------------------
; Register usage
; --------------
      .asg     AR0, in_ptr  

      .global _bexp
      .text

_bexp:
      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  
      PSH	mmap(ST3_55)

      SUB #1,T0                        ;setup loop counter=nx-1
      MOV T0,BRC0
      MOV #020h,T0                     ;init T0 to the max exp
      ||RPTBLOCAL end_block-1          ;start main loop
      MOV *in_ptr+ << #16,AC0          ;read in the vector with 16 bits left shift
      EXP AC0,T1                       ;calculate exp and store the result into T1
      MIN T1,T0                        ;update T0 with min value
end_block:

      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
      
      RET

;end of file. please do not remove. it is left here to ensure that no lines of code are removed by any editor
