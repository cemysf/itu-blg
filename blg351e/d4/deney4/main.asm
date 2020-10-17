;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
			mov.w #000001,R5
			mov.w #000007,R6
			mov.w #000007,R7
SetupP1		bis.b R5, &P1DIR

Mainloop	xor.b R5, &P1OUT	;xor.b R1, &P1OUT
Wait		mov.w #050000,R15
L1			dec.w R15
			jnz L1
			;xor.b R1, &P1OUT

			rla.b R5
			clr.b &P1OUT
			dec.w R6
			jz SetupP2
			jmp SetupP1


SetupP2		bis.b R5, &P1DIR

Mainloop2	xor.b R5, &P1OUT	;xor.b R1, &P1OUT
Wait2		mov.w #050000,R15
L2			dec.w R15
			jnz L2
			;xor.b R1, &P1OUT
			clrc
			rrc.b R5
			clr.b &P1OUT
			inc.w R6
			cmp.w R6, R7
			jz SetupP1
			jmp SetupP2

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
