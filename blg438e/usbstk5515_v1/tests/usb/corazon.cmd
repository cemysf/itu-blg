-stack 		0x1000
-sysstack	0x1000
-heap		0x1000

MEMORY
{
    MMR     (RW) : origin = 0000000h length = 0000c0h /* 192 bytes memory-mapped registers*/
    VEC     (RX) : origin = 00000c0h length = 000300h /* 768 bytes on-chip ROM vectors   */
    DARAM_0 (RW) : origin = 0000400h length = 001C00h /* 7KB  on-chip DARAM 0 */
    DARAM_1 (RW) : origin = 0002000h length = 002000h /* 8KB  on-chip DARAM 1 */
    DARAM_2 (RW) : origin = 0004000h length = 002000h /* 8KB  on-chip DARAM 2 */
    DARAM_3 (RW) : origin = 0006000h length = 002000h /* 8KB  on-chip DARAM 3 */
    DARAM_4 (RW) : origin = 0008000h length = 008000h /* 32KB on-chip DARAM 4 */
    SARAM_0 (RW) : origin = 0010000h length = 020000h /* on-chip 256KB SARAM 0 */
	USBBUF  (RW) : origin = 0030000h length = 020000h /* USB buffer allocation */
}
 
SECTIONS
{
    vectors     : > VEC      ALIGN = 256
    .text       : > SARAM_0  ALIGN = 4
    .stack      : > SARAM_0  ALIGN = 4
    .sysstack   : > SARAM_0  ALIGN = 4
    .data       : > DARAM_1
    .bss        : > DARAM_1, fill = 0
    .cinit 	    : > DARAM_2
    .const 	    : > DARAM_2
    .sysmem     : > DARAM_3
    .buffer1   	: > DARAM_0
    .buffer2   	: > DARAM_0
    .switch     : > DARAM_4
	.cio        : > DARAM_1
	.usbBuffer  : > USBBUF
}