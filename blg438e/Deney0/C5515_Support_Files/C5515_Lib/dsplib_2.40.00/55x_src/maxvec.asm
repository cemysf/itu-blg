;***********************************************************
; Version 2.40.00                                           
;***********************************************************
; Function:  MAXVEC
; Processor:   C55xx
; Description: maxvec: Value and Index of the maximum element of a vector
; Useage:	void maxvec (DATA *x, ushort nx, DATA *r_val, DATA *r_idx)
; Copyright Texas instruments Inc, 2000
;********************************************************************************

        .text
        .global	_maxvec
	
_maxvec:
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
        MAX AC0,AC1
        XCCPART end_block, !CARRY
        || MOV AR3,*AR2
end_block:
        MOV AC1,*AR1
      POP	mmap(ST3_55)
      POP	mmap(ST2_55)
      POP	mmap(ST1_55)
      POP	mmap(ST0_55)
        RET

