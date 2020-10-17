/**********************************************************/
/*                                                        */
/*         LINKER command file for LEAD3 memory map       */
/*                                                        */
/**********************************************************/

 
MEMORY
{
  PAGE 0: MMR    (RIX) : origin = 0000000h length = 000c0h 
          DARAM1 (RWX) : origin = 00000c0h length = 01F40h
          DARAM2 (RWX) : origin = 0002000h length = 02000h      /* 8K bytes */
          DARAM3 (RWX) : origin = 0004000h length = 02000h      /* 8K bytes  */
          DARAM4 (RWX) : origin = 0006000h length = 02000h      /* 8K bytes  */
          DARAM5 (RWX) : origin = 0008000h length = 02000h      /* 8K bytes  */
          DARAM6 (RWX) : origin = 000A000h length = 02000h      /* 8K bytes  */
          DARAM7 (RWX) : origin = 000C000h length = 02000h      /* 8K bytes  */
          DARAM8 (RWX) : origin = 000E000h length = 02000h      /* 8K bytes  */

        SARAM0  : origin = 0010000h, length = 0004000h
        SARAM1  : origin = 0014000h, length = 0004000h
        SARAM2  : origin = 0018000h, length = 0004000h
        SARAM3  : origin = 001c000h, length = 0004000h
        SARAM4  : origin = 0020000h, length = 0004000h
        SARAM5  : origin = 0024000h, length = 0004000h
        SARAM6  : origin = 0028000h, length = 0004000h
        SARAM7  : origin = 002c000h, length = 0004000h
        SARAM8  : origin = 0030000h, length = 0004000h
        SARAM9  : origin = 0034000h, length = 0004000h
        SARAM10 : origin = 0038000h, length = 0004000h
        SARAM11 : origin = 003c000h, length = 0004000h
        SARAM12 : origin = 0040000h, length = 0004000h
        SARAM13 : origin = 0044000h, length = 0004000h
        SARAM14 : origin = 0048000h, length = 0004000h
        SARAM15 : origin = 004c000h, length = 0004000h

        CE0     : origin = 0050000h, length = 03b0000h 
        CE1     : origin = 0400000h, length = 0400000h
        CE2     : origin = 0800000h, length = 0400000h
        CE3     : origin = 0c00000h, length = 03f8000h

        PDROM   : origin = 0ff8000h, length = 07f00h
        VECS    : origin = 0ffff00h, length = 00100h  /* reset vector */
}	

 
SECTIONS
{
        vectors  : {} > VECS   PAGE 0         /* interrupt vector table */
        .cinit   : {} > SARAM0 PAGE 0
        .text    : {} > SARAM1 PAGE 0
        isrs     : {} > SARAM2 PAGE 0

        .stack   : {} > DARAM1 PAGE 0
        .sysstack: {} > DARAM1 PAGE 0
        .sysmem  : {} > DARAM1 PAGE 0
        .data    : {} > DARAM1 PAGE 0
        .bss     : {} > DARAM1 PAGE 0
        .const   : {} > DARAM1 PAGE 0

        .coeffs  align(4): {} > DARAM2 PAGE 0 
/*        .scratch align(4): {} > DARAM6 PAGE 0   */
        .dbuffer : {} > DARAM3 PAGE 0
        files    : {} > DARAM2 PAGE 0         /* User-defined sections */
        statvar  : {} > DARAM2 PAGE 0
        statarry : {} > DARAM2 PAGE 0
        tempvar  : {} > DARAM2 PAGE 0
        temparry : {} > DARAM2 PAGE 0
}