;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:  MINVEC
; Processor:   C55xx
; Description: minimum Value and Index of the minimum element of a vector
; Useage:	void minvec (DATA *x, ushort nx, DATA *val, DATA *idx)
; Copyright Texas instruments Inc, 2000
;********************************************************************************

        .text
        .global	_minvec
	
_minvec:
      PSH	mmap(ST0_55)
      PSH	mmap(ST1_55)
      PSH	mmap(ST2_55)  
      PSH	mmap(ST3_55)

        MOV *AR0+,AC1
        || SUB #2,T0

        MOV T0,BRC0
        || MOV #0,AR3


        MOV #0,T0
        || RPTBLOCAL end_block-1
        MOV *AR0+,AC0
        || MAR *AR3+
        MIN AC0,AC1
        XCCPART end_block, !CARRY
        || MOV AR3,*AR2
end_block:
        MOV AC1,*AR1
      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
        RET

