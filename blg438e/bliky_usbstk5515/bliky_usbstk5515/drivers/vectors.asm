;****************************************************************************
; Interrupt Vector Table, aligned at 256-byte boundary
;
; 32 interrupt vector addresses.  Each is 64 bits long.  The first 32 bits
; contains the 24-bit program address of the Interrupt Service Routine (ISR).
; The second 32 bits are executed before transferring control to the ISR.
;****************************************************************************

    .sect   "vectors"
    .align  256 

;****************************************************************************
;* Point Reset Vector to C Environment Entry Point
;****************************************************************************
    .def    _Reset
    .ref    _c_int00

    .global _VECSTART
_VECSTART:

    .if __TMS320C55X_PLUS_BYTE__
_Reset:    .ivec _c_int00, STK_LINEAR | RET_FAST | DATA_PTR_BYTE
    .else
_Reset:    .ivec _c_int00, USE_RETA
    .endif

;****************************************************************************
;* Other interrupt vector definitions go here
;****************************************************************************
nmi:      .ivec _no_handler  ; Non-maskable hardware interrupt
int02:    .ivec _no_handler
int03:    .ivec _no_handler
int04:    .ivec _no_handler
int05:    .ivec _no_handler
int06:    .ivec _no_handler
int07:    .ivec _no_handler
int08:    .ivec _no_handler
int09:    .ivec _no_handler
int10:    .ivec _no_handler
int11:    .ivec _no_handler
int12:    .ivec _no_handler
int13:    .ivec _no_handler
int14:    .ivec _no_handler
int15:    .ivec _no_handler
int16:    .ivec _no_handler
int17:    .ivec _no_handler
int18:    .ivec _no_handler
int19:    .ivec _no_handler
int20:    .ivec _no_handler
int21:    .ivec _no_handler
int22:    .ivec _no_handler
int23:    .ivec _no_handler
int24:    .ivec _no_handler  ; Bus error interrupt
int25:    .ivec _no_handler  ; Data log interrupt
int26:    .ivec _no_handler  ; Real-time OS interrupt
int27:    .ivec _no_handler  ; General-purpose software-only interrupt
int28:    .ivec _no_handler  ; General-purpose software-only interrupt
int29:    .ivec _no_handler  ; General-purpose software-only interrupt
int30:    .ivec _no_handler  ; General-purpose software-only interrupt
int31:    .ivec _no_handler  ; General-purpose software-only interrupt

    .text
_no_handler: goto _no_handler

    .end
