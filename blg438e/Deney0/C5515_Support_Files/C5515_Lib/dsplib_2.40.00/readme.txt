********************************************************************************
*             TMS320C55x DSPLIB Release Version 2.40.00                                                                              *
*                               Release Notes                                                                                                         *
********************************************************************************
 C55x DSPLIB is a DSP function library for the TMS320C55x containing over 50 
 C-callable hand assembly optimized routines.
 
 DSPLIB is a free-of-charge product to facilitate your programming in C.

 You can download DSPLIB free-of-charge at:
 http://www.ti.com/sc/docs/products/dsp/c5000/index.htm

================================================================================
Table of Contents
================================================================================
 1. Scope
 2. Bugs fixed in this release and previous releases
 3. Open bugs
 4. For bug reports/ suggestions/ user contribued code
 5. C models

================================================================================
 1. Scope
================================================================================

 This package contains release 2.30.00 of the Texas Instruments TMS320C55x
 DSP Library (DSPLIB).

 The User's Guide is located at: \docs\pdf\ in your CCS install folder.
 Read the standard license agreement contained in the User's Guide (Appendix)

 Please notice that the library is build under options -v5510:2. If you would like to build
 the library for device 55x PG 1.0 core. You can rebuild the library by using the following setups(i.e.
 in Blt55x.bat file change the 1st line to): 
 set OPTIONS= -g -v5510:1 -d"SI_BUGS"
 
 For large model build:
 in Blt55xx.bat file change the 1st line to:
 set OPTIONS= -g -v5510:1 -d"SI_BUGS"


================================================================================
 2. Bugs Fixed in this release and previously releases
================================================================================
 ** Bugs fixed in this release (version 2.40.00) 
 -----------------------------------------
(1) abias, araw, aubias, cbias, craw, expn: added overflow checking and return overflow value is in T0 instead of AC0.
(2) IIR4, IIR5, IIR32, IIR51: XDP is cleared instead of only clearing DP.
(3) power.asm: return overflow value is in T0 instead of AC0. Output vector is returned.
(4) fltoq15.asm: T2 registered is used and saved in the function. 


 ** Bugs fixed in this release (version 2.30.00) 
 -----------------------------------------
 (1) Fixed twiddle table addition bug, affects FFT, UNPACK and CBREV routines
 (2) Added 8-point support to cfft_scale() and improved butterfly Kernel to 5 cycles.
 (3) ldiv16(): optimized
 (4) recip16(): optimized
 (5) q15tofl() fixed bug for min and max q15 values
 (6) sine() fixed bug for value 1
 (7) Added unpack32() and unpacki32() for rfft32() and rifft32() support
 (8) acorr_bias(): added psh/pop st1
 (9) add(): added psh/pop st1
 (10) accor_raw(): added psh/pop st1
 (11) accor_unbias(): added psh/pop st1
 (12) cbrev(): improved code performance for inplace version.
 (13) cfir(): added psh/pop st1
 (14) cfir(): added extended register initialization for large memory model
 (15) cor_raw(): added extended register initialization for large memory model
 (16) cor_unbias(): added extended register initialization for large memory model
 (17) firdec(): added psh/pop t2
 (18) dmlsfast(): added extended register initialization for large memory model
 (19) firlat(): added psh/pop st3
 (20) firs(): added psh/pop st3
 (21) iircas4(): added extended register initialization for large memory model
 (22) iircas5(): removed delay buffer index
 (23) iircas51(): removed delay buffer index
 (24) iirlat(): added psh/pop st3
 (25) iirlat(): added extended register initialization for large memory model
 (26) ldiv16(): added psh/pop st3
 (27) recip16(): added psh/pop st3
 (28) log_10(): added psh/pop st1
 (29) log_10(): added extended register initialization for large memory model
 (30) log_2(): added psh/pop st1
 (31) log_2(): added extended register initialization for large memory model
 (32) logn(): added psh/pop st1
 (33) logn(): added extended register initialization for large memory model
 (34) maxidx34(): removed unnecessary .bss section allocation.
 (35) minidx(): replaced "CMP AC1<AC0, TC1" with "CMP AC0>=AC1, TC1"
 (36) neg(): added psh/pop st3
 (37) neg32(): added psh/pop st3
 (38) power(): added psh/pop st3
 (39) sqrt_16(): added psh/pop t2,t3
 (40) sqrt_16(): added extended register initialization for large memory model
 (41) sub(): added psh/pop st3
 (41) sub(): added psh/pop st3
 (41) sub(): added psh/pop st3
 (41) unpack(): modified way twiddle table included
 (42) unpacki(): modified way twiddle table is included




 ** Bugs fixed in this release (version 2.20.02) 
 -----------------------------------------
 (1) added new function: cfft32(cfft32_scale.asm, cfft32_noscale.asm) which does
     32-bit CFFT. 

 (2) added new function: cifft32(cifft32_scale.asm, cifft32_noscale.asm) which does
     32-bit inversed CFFT. 

 (3) added new function: dlmsfast(dlmsfast.asm) which has better performs on large tap filters(
     1.5 cycles per filter tap).



 ** Bugs fixed in version 2.20.01 release 
 -----------------------------------------
 (1) added new functions: cfft_offplace(cfft_o_s.asm, cfft_o_nos.asm) 
     and cifft_offplace(cifft_o_s.asm, cifft_o_nos.asm) which have better benchmark than cfft/cifft fucntions.

 ** Bugs fixed in version 2.20 release 
 -----------------------------------------
 (1) functions: cfft_scale.asm, cfft_noscale.asm, cifft_scale.asm, cifft_noscale.asm
     Fixed bugs in cfft_scale/cfft_noscale/cifft_scale/cifft_noscale functions.

 (2) functions: iir51.asm, iir5.asm, iir32.asm
     Added st0 register save/restore.

 (3) function: minval.asm
     optimized minval function for better benchmark purpose.

 (4) function: minidx.asm
     optimized minidx function for better benchmark purpose, also the funtion prototype changed.

 (5) function: maxidx.asm
     fixed code to make it works when the first element is the max.

 (6). Added project for each function in example directory.


 ** Bugs Fixed in version 2.10.03 release 
 -----------------------------------------
 (1) added 4096 twiddle table to src as a option.
     fixed cfft.cmd/rfft.cmd .input/.twiddle alignment comment.
 
 (2) function: unpack.asm and unpacki.asm
     fixed T2/T3 restore problem in unpack/unpacki funcions.

 (3) function sqrvt.asm
     fixed the bug where NX should be stored in register T0 instead of AR2.
     fixed code to work in large block memory by correct XAR loading.

 (4) funtions: cbrev.asm cfft.asm and cifft.asm
  	For cbrev.asm:
	- reset C54CM bit
	- push/pop ST2, ST1
	
	For CIFFT
	cifft_noscale.asm: 
		- Changed the Radix 4 stage and radix 2 stages according to IFFT C model
		- Corrected the context save
	cifft_scale.asm: 
		- Modified stack to make correct XAR restore (this problem was found by visual inspection of the XAR5, 6, 7 - not detected by the test)

        Added test vectors for NOSCALE version

	For CFFT:
	cfft_noscale.asm: 
		- Corrected the context save

	cfft_scale.asm: 
		- Modified stack 

        Added test vectors for NOSCALE version


 (5)functions: abias.asm, cbias.asm, fltoq15.asm, mul32.asm, and q15tofl.asm
    fixed assembly code to make them work in large memory module(XAR fixes).


================================================================================
 3. Open Bugs
================================================================================
(1).Functions log_10(); log_2(); logn() return Q15 values instead of Q31


================================================================================
 4. For bug reports/ suggestions/ user contribued code
================================================================================

 For bug reports/ suggestions/ user contribued code
 email to:  dsph@ti.com

================================================================================
 5. C models
================================================================================

 C models are provided for the following functions

 (1) fir()
 (2) acorr_raw()
 (3) acorr_bias()
 (4) acorr_unbias()
 (5) dlms()
 (6) iir5()
 (7) iir51()
 (8) iir4() 