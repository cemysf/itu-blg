/*-c */
/*-stack 0x2000 */                  /* PRIMARY STACK SIZE               */
/*-sysstack 0x2000 */               /* SECONDARY STACK SIZE             */
/*-heap  0x1000 */                  /* HEAP AREA SIZE  */  

/*_RTDX_interrupt_mask = ~0x06000010; */

/* Set entry point to Reset vector                                  */
/* - Allows Reset ISR to force IVPD/IVPH to point to vector table.  */
/*-e reset_isr */

MEMORY
{
    MMR     (RW) : origin = 0000000h length = 0000c0h /* MMRs */
    /*DARAM_0 (RW) : origin = 00000C0h length = 001A00h /* on-chip DARAM 0 */
/*    DARAM_1 (RW) : origin = 0002000h length = 002000h /* on-chip DARAM 1 */
/*    DARAM_2 (RW) : origin = 0004000h length = 002000h /* on-chip DARAM 2 */
/*    DARAM_3 (RW) : origin = 0006000h length = 00A000h /* on-chip DARAM 3 */
/*    DARAM_3 (RW) : origin = 0006000h length = 002000h /* on-chip DARAM 3 */
/*    DARAM_4 (RW) : origin = 0008000h length = 002000h /* on-chip DARAM 4 */
/*    DARAM_5 (RW) : origin = 000A000h length = 002000h /* on-chip DARAM 5 */
/*    DARAM_6 (RW) : origin = 000C000h length = 002000h /* on-chip DARAM 6 */
/*    DARAM_7 (RW) : origin = 000e000h length = 002000h /* on-chip DARAM 7 */

    DARAM (RW)    : origin = 00000c0h length = 00ff40h  /* on-chip DARAM */

/*    SARAM_0 (RW)  : origin = 0010000h length = 002000h  /* on-chip SARAM 0 */
/*    SARAM_1 (RW)  : origin = 0012000h length = 002000h  /* on-chip SARAM 1 */
/*    SARAM_2 (RW)  : origin = 0014000h length = 002000h  /* on-chip SARAM 2 */
/*    SARAM_3 (RW)  : origin = 0016000h length = 002000h  /* on-chip SARAM 3 */

/*    SARAM_4 (RW)  : origin = 0018000h length = 002000h  /* on-chip SARAM 4 */
/*    SARAM_5 (RW)  : origin = 001A000h length = 002000h  /* on-chip SARAM 5 */
/*    SARAM_6 (RW)  : origin = 001C000h length = 002000h  /* on-chip SARAM 6 */
/*    SARAM_7 (RW)  : origin = 001e000h length = 002000h  /* on-chip SARAM 7 */

/*    SARAM_8 (RW)  : origin = 0020000h length = 002000h  /* on-chip SARAM 8 */
/*    SARAM_9 (RW)  : origin = 0022000h length = 002000h  /* on-chip SARAM 9 */
/*    SARAM_10 (RW) : origin = 0024000h length = 002000h  /* on-chip SARAM 10 */
/*    SARAM_11 (RW) : origin = 0026000h length = 002000h  /* on-chip SARAM 11 */

/*    SARAM_12 (RW) : origin = 0028000h length = 002000h  /* on-chip SARAM 12 */
/*    SARAM_13 (RW) : origin = 002A000h length = 002000h  /* on-chip SARAM 13 */
/*    SARAM_14 (RW) : origin = 002C000h length = 002000h  /* on-chip SARAM 14 */
/*    SARAM_15 (RW) : origin = 002e000h length = 002000h  /* on-chip SARAM 15 */

/*    SARAM_16 (RW) : origin = 0030000h length = 002000h  /* on-chip SARAM 16 */
/*    SARAM_17 (RW) : origin = 0032000h length = 002000h  /* on-chip SARAM 17 */
/*    SARAM_18 (RW) : origin = 0034000h length = 002000h  /* on-chip SARAM 18 */
/*    SARAM_19 (RW) : origin = 0036000h length = 002000h  /* on-chip SARAM 19 */

/*    SARAM_20 (RW) : origin = 0038000h length = 002000h  /* on-chip SARAM 20 */
/*    SARAM_21 (RW) : origin = 003A000h length = 002000h  /* on-chip SARAM 21 */
/*    SARAM_22 (RW) : origin = 003C000h length = 002000h  /* on-chip SARAM 22 */
/*    SARAM_23 (RW) : origin = 003e000h length = 002000h  /* on-chip SARAM 23 */

/*    SARAM_24 (RW) : origin = 0040000h length = 002000h  /* on-chip SARAM 24 */
/*    SARAM_25 (RW) : origin = 0042000h length = 002000h  /* on-chip SARAM 25 */
/*    SARAM_26 (RW) : origin = 0044000h length = 002000h  /* on-chip SARAM 26 */
/*    SARAM_27 (RW) : origin = 0046000h length = 002000h  /* on-chip SARAM 27 */

/*    SARAM_28 (RW) : origin = 0048000h length = 002000h  /* on-chip SARAM 28 */
/*    SARAM_29 (RW) : origin = 004A000h length = 002000h  /* on-chip SARAM 29 */
/*    SARAM_30 (RW) : origin = 004C000h length = 002000h  /* on-chip SARAM 30 */
/*    SARAM_31 (RW) : origin = 004E000h length = 002000h  /* on-chip SARAM 31 */

    SARAM   (RW)  : origin = 0030000h length = 01e000h /* on-chip SARAM */

    SAROM_0 (RX)  : origin = 0fe0000h length = 008000h 	/* on-chip ROM 0 */
    SAROM_1 (RX)  : origin = 0fe8000h length = 008000h 	/* on-chip ROM 1 */
    SAROM_2 (RX)  : origin = 0ff0000h length = 008000h 	/* on-chip ROM 2 */
    SAROM_3 (RX)  : origin = 0ff8000h length = 008000h 	/* on-chip ROM 3 */
    
    EMIF_CS0 (RW)  : origin = 0050000h  length = 07B0000h   /* mSDR */ 
	EMIF_CS2 (RW)  : origin = 0800000h  length = 0400000h   /* ASYNC1 : NAND */ 
	EMIF_CS3 (RW)  : origin = 0C00000h  length = 0200000h   /* ASYNC2 : NAND  */
	EMIF_CS4 (RW)  : origin = 0E00000h  length = 0100000h   /* ASYNC3 : NOR */
	EMIF_CS5 (RW)  : origin = 0F00000h  length = 00E0000h   /* ASYNC4 : SRAM */
/*	EMIF_CS5 (RW)  : origin = 0F00000h  length = 0100000h*/   /* ASYNC4 : SRAM */

}


SECTIONS
{
    vectors (NOLOAD)
    .bss        : > DARAM /*, fill = 0 */
    vector      : > DARAM      ALIGN = 256 
    .stack      : > DARAM  
    .sysstack   : > DARAM  
	.sysmem 	: > DARAM 
/*	.sysmem 	: > EMIF_CS5 */
    .text       : > SARAM  
/*    .text       : > EMIF_CS5  */
    .data       : > DARAM
	.cinit 		: > DARAM
	.const 		: > DARAM
	.cio		: > DARAM
	.usect   	: > DARAM
	.switch     : > DARAM 
	.emif_cs0   : > EMIF_CS0
	.emif_cs2   : > EMIF_CS2
	.emif_cs3   : > EMIF_CS3
	.emif_cs4   : > EMIF_CS4
	.emif_cs5   : > EMIF_CS5


}
