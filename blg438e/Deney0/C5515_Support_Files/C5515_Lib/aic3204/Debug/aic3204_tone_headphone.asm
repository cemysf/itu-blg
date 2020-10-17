;*******************************************************************************
;* TMS320C55x C/C++ Codegen                                          PC v4.3.8 *
;* Date/Time created: Thu Jun 09 17:19:12 2011                                 *
;*******************************************************************************
	.compiler_opts --hll_source=on --mem_model:code=flat --mem_model:data=large --silicon_core_3_3 --symdebug:dwarf 
	.mmregs
	.cpl_on
	.arms_on
	.c54cm_off
	.asg AR6, FP
	.asg XAR6, XFP
	.asg DPH, MDP
	.model call=c55_std
	.model mem=large
	.noremark 5002  ; code respects overwrite rules
;*******************************************************************************
;* GLOBAL FILE PARAMETERS                                                      *
;*                                                                             *
;*   Architecture       : TMS320C55x                                           *
;*   Optimizing for     : Speed                                                *
;*   Memory             : Large Model (23-Bit Data Pointers)                   *
;*   Calls              : Normal Library ASM calls                             *
;*   Debug Info         : Standard TI Debug Information                        *
;*******************************************************************************

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../aic3204_tone_headphone.c")
	.dwattr $C$DW$CU, DW_AT_producer("TMS320C55x C/C++ Codegen PC v4.3.8 Copyright (c) 1996-2010 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Users\Kurt\Documents\Little_Projects\MCUs\C5515\usbstk5515_BSL_RevA\usbstk5515_v1\tests\aic3204\Debug")

$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("USBSTK5515_wait")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_USBSTK5515_wait")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("..\..\..\include\usbstk5515.h")
	.dwattr $C$DW$1, DW_AT_decl_line(0x6d)
	.dwattr $C$DW$1, DW_AT_decl_column(0x06)
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$13)
	.dwendtag $C$DW$1


$C$DW$3	.dwtag  DW_TAG_subprogram, DW_AT_name("AIC3204_rset")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("_AIC3204_rset")
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$3, DW_AT_declaration
	.dwattr $C$DW$3, DW_AT_external
	.dwattr $C$DW$3, DW_AT_decl_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$3, DW_AT_decl_line(0x0c)
	.dwattr $C$DW$3, DW_AT_decl_column(0x0e)
$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$11)
$C$DW$5	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$11)
	.dwendtag $C$DW$3

	.sect	".const:_$P$T0$1"
	.clink
	.align	1
_$P$T0$1:
	.field  	0,16			; _$P$T0$1[0] @ 0
	.field  	4276,16			; _$P$T0$1[1] @ 16
	.field  	8480,16			; _$P$T0$1[2] @ 32
	.field  	12539,16			; _$P$T0$1[3] @ 48
	.field  	16383,16			; _$P$T0$1[4] @ 64
	.field  	19946,16			; _$P$T0$1[5] @ 80
	.field  	23169,16			; _$P$T0$1[6] @ 96
	.field  	25995,16			; _$P$T0$1[7] @ 112
	.field  	28376,16			; _$P$T0$1[8] @ 128
	.field  	30271,16			; _$P$T0$1[9] @ 144
	.field  	31649,16			; _$P$T0$1[10] @ 160
	.field  	32485,16			; _$P$T0$1[11] @ 176
	.field  	32765,16			; _$P$T0$1[12] @ 192
	.field  	32485,16			; _$P$T0$1[13] @ 208
	.field  	31649,16			; _$P$T0$1[14] @ 224
	.field  	30447,16			; _$P$T0$1[15] @ 240
	.field  	28376,16			; _$P$T0$1[16] @ 256
	.field  	25995,16			; _$P$T0$1[17] @ 272
	.field  	23169,16			; _$P$T0$1[18] @ 288
	.field  	19946,16			; _$P$T0$1[19] @ 304
	.field  	16383,16			; _$P$T0$1[20] @ 320
	.field  	12539,16			; _$P$T0$1[21] @ 336
	.field  	8480,16			; _$P$T0$1[22] @ 352
	.field  	4276,16			; _$P$T0$1[23] @ 368
	.field  	0,16			; _$P$T0$1[24] @ 384
	.field  	-4276,16			; _$P$T0$1[25] @ 400
	.field  	-8480,16			; _$P$T0$1[26] @ 416
	.field  	-12538,16			; _$P$T0$1[27] @ 432
	.field  	-16382,16			; _$P$T0$1[28] @ 448
	.field  	-19946,16			; _$P$T0$1[29] @ 464
	.field  	-23169,16			; _$P$T0$1[30] @ 480
	.field  	-25995,16			; _$P$T0$1[31] @ 496
	.field  	-28376,16			; _$P$T0$1[32] @ 512
	.field  	-30271,16			; _$P$T0$1[33] @ 528
	.field  	-31649,16			; _$P$T0$1[34] @ 544
	.field  	-32485,16			; _$P$T0$1[35] @ 560
	.field  	-32766,16			; _$P$T0$1[36] @ 576
	.field  	-32485,16			; _$P$T0$1[37] @ 592
	.field  	-31649,16			; _$P$T0$1[38] @ 608
	.field  	-30271,16			; _$P$T0$1[39] @ 624
	.field  	-28376,16			; _$P$T0$1[40] @ 640
	.field  	-25994,16			; _$P$T0$1[41] @ 656
	.field  	-23169,16			; _$P$T0$1[42] @ 672
	.field  	-19946,16			; _$P$T0$1[43] @ 688
	.field  	-16382,16			; _$P$T0$1[44] @ 704
	.field  	-12538,16			; _$P$T0$1[45] @ 720
	.field  	-8480,16			; _$P$T0$1[46] @ 736
	.field  	-4276,16			; _$P$T0$1[47] @ 752

$C$DW$6	.dwtag  DW_TAG_variable, DW_AT_name("$P$T0$1")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("_$P$T0$1")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$6, DW_AT_location[DW_OP_addr _$P$T0$1]
	.dwattr $C$DW$6, DW_AT_decl_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$6, DW_AT_decl_line(0x18)
	.dwattr $C$DW$6, DW_AT_decl_column(0x0b)
;	C:\Program Files (x86)\Texas Instruments\ccsv5\tools\compiler\c5500\bin\opt55.exe C:\\Users\\Kurt\\AppData\\Local\\Temp\\050522 C:\\Users\\Kurt\\AppData\\Local\\Temp\\050524 
	.sect	".text"
	.global	_aic3204_tone_headphone

$C$DW$7	.dwtag  DW_TAG_subprogram, DW_AT_name("aic3204_tone_headphone")
	.dwattr $C$DW$7, DW_AT_low_pc(_aic3204_tone_headphone)
	.dwattr $C$DW$7, DW_AT_high_pc(0x00)
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("_aic3204_tone_headphone")
	.dwattr $C$DW$7, DW_AT_external
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$7, DW_AT_TI_begin_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$7, DW_AT_TI_begin_line(0x15)
	.dwattr $C$DW$7, DW_AT_TI_begin_column(0x07)
	.dwattr $C$DW$7, DW_AT_decl_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$7, DW_AT_decl_line(0x15)
	.dwattr $C$DW$7, DW_AT_decl_column(0x07)
	.dwattr $C$DW$7, DW_AT_TI_max_frame_size(0x32)
	.dwpsn	file "../aic3204_tone_headphone.c",line 22,column 1,is_stmt,address _aic3204_tone_headphone

	.dwfde $C$DW$CIE, _aic3204_tone_headphone
;*******************************************************************************
;* FUNCTION NAME: aic3204_tone_headphone                                       *
;*                                                                             *
;*   Function Uses Regs : AC0,AC0,T0,T1,AR1,AR2,XAR2,AR3,XAR3,AR4,SP,CSR,RPTC, *
;*                        CARRY,TC1,M40,SATA,SATD,RDM,FRCT,SMUL                *
;*   Stack Frame        : Compact (No Frame Pointer, w/ debug)                 *
;*   Total Frame Size   : 50 words                                             *
;*                        (2 return address/alignment)                         *
;*                        (48 local values)                                    *
;*   Min System Stack   : 1 word                                               *
;*******************************************************************************

;*******************************************************************************
;*                                                                             *
;* Using -g (debug) with optimization (-o3) may disable key optimizations!     *
;*                                                                             *
;*******************************************************************************
_aic3204_tone_headphone:
	.dwcfi	cfa_offset, 1
	.dwcfi	save_reg_to_mem, 91, -1
        AADD #-49, SP
	.dwcfi	cfa_offset, 50
;* AR3   assigned to $O$U58
;* AR1   assigned to _sample
$C$DW$8	.dwtag  DW_TAG_variable, DW_AT_name("sample")
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("_sample")
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$8, DW_AT_location[DW_OP_reg18]
;* AR4   assigned to $O$C1
$C$DW$9	.dwtag  DW_TAG_variable, DW_AT_name("sinetable")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("_sinetable")
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$9, DW_AT_location[DW_OP_bregx 0x24 0]
	.dwpsn	file "../aic3204_tone_headphone.c",line 24,column 11,is_stmt
        AMOV #_$P$T0$1, XAR3 ; |24| 

        RPT #47   ; |24| 
||      AMAR *SP(#0), XAR2

                                            ; loop starts ; |24| 
$C$L1:    
$C$DW$L$_aic3204_tone_headphone$2$B:
            MOV *AR3+, *AR2+ ; |24| 
                                        ; loop ends ; |24| 
$C$DW$L$_aic3204_tone_headphone$2$E:
$C$L2:    
	.dwpsn	file "../aic3204_tone_headphone.c",line 36,column 5,is_stmt
        MOV #0, T0
$C$DW$10	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$10, DW_AT_low_pc(0x00)
	.dwattr $C$DW$10, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$10, DW_AT_TI_call

        CALL #_AIC3204_rset ; |36| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |36| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 37,column 5,is_stmt
        MOV #1, T0
$C$DW$11	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$11, DW_AT_low_pc(0x00)
	.dwattr $C$DW$11, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$11, DW_AT_TI_call

        CALL #_AIC3204_rset ; |37| 
||      MOV #1, T1

                                        ; call occurs [#_AIC3204_rset] ; |37| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 38,column 5,is_stmt
        MOV #0, T0
$C$DW$12	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$12, DW_AT_low_pc(0x00)
	.dwattr $C$DW$12, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$12, DW_AT_TI_call

        CALL #_AIC3204_rset ; |38| 
||      MOV #1, T1

                                        ; call occurs [#_AIC3204_rset] ; |38| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 39,column 5,is_stmt
        MOV #1, T0
$C$DW$13	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$13, DW_AT_low_pc(0x00)
	.dwattr $C$DW$13, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$13, DW_AT_TI_call

        CALL #_AIC3204_rset ; |39| 
||      MOV #8, T1

                                        ; call occurs [#_AIC3204_rset] ; |39| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 40,column 5,is_stmt
        MOV #2, T0
$C$DW$14	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$14, DW_AT_low_pc(0x00)
	.dwattr $C$DW$14, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$14, DW_AT_TI_call

        CALL #_AIC3204_rset ; |40| 
||      MOV #1, T1

                                        ; call occurs [#_AIC3204_rset] ; |40| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 41,column 5,is_stmt
        MOV #0, T0
$C$DW$15	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$15, DW_AT_low_pc(0x00)
	.dwattr $C$DW$15, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$15, DW_AT_TI_call

        CALL #_AIC3204_rset ; |41| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |41| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 43,column 5,is_stmt
        MOV #27, T0 ; |43| 
$C$DW$16	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$16, DW_AT_low_pc(0x00)
	.dwattr $C$DW$16, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$16, DW_AT_TI_call

        CALL #_AIC3204_rset ; |43| 
||      MOV #13, T1

                                        ; call occurs [#_AIC3204_rset] ; |43| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 44,column 5,is_stmt
        MOV #28, T0 ; |44| 
$C$DW$17	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$17, DW_AT_low_pc(0x00)
	.dwattr $C$DW$17, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$17, DW_AT_TI_call

        CALL #_AIC3204_rset ; |44| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |44| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 45,column 5,is_stmt
        MOV #4, T0
$C$DW$18	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$18, DW_AT_low_pc(0x00)
	.dwattr $C$DW$18, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$18, DW_AT_TI_call

        CALL #_AIC3204_rset ; |45| 
||      MOV #3, T1

                                        ; call occurs [#_AIC3204_rset] ; |45| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 46,column 5,is_stmt
        MOV #6, T0
$C$DW$19	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$19, DW_AT_low_pc(0x00)
	.dwattr $C$DW$19, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$19, DW_AT_TI_call

        CALL #_AIC3204_rset ; |46| 
||      MOV #7, T1

                                        ; call occurs [#_AIC3204_rset] ; |46| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 47,column 5,is_stmt
        MOV #7, T0
$C$DW$20	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$20, DW_AT_low_pc(0x00)
	.dwattr $C$DW$20, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$20, DW_AT_TI_call

        CALL #_AIC3204_rset ; |47| 
||      MOV #6, T1

                                        ; call occurs [#_AIC3204_rset] ; |47| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 48,column 5,is_stmt
        MOV #144, T1 ; |48| 
$C$DW$21	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$21, DW_AT_low_pc(0x00)
	.dwattr $C$DW$21, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$21, DW_AT_TI_call

        CALL #_AIC3204_rset ; |48| 
||      MOV #8, T0

                                        ; call occurs [#_AIC3204_rset] ; |48| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 49,column 5,is_stmt
        MOV #136, T1 ; |49| 
        MOV #30, T0 ; |49| 
$C$DW$22	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$22, DW_AT_low_pc(0x00)
	.dwattr $C$DW$22, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$22, DW_AT_TI_call
        CALL #_AIC3204_rset ; |49| 
                                        ; call occurs [#_AIC3204_rset] ; |49| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 51,column 5,is_stmt
        MOV #145, T1 ; |51| 
$C$DW$23	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$23, DW_AT_low_pc(0x00)
	.dwattr $C$DW$23, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$23, DW_AT_TI_call

        CALL #_AIC3204_rset ; |51| 
||      MOV #5, T0

                                        ; call occurs [#_AIC3204_rset] ; |51| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 52,column 5,is_stmt
        MOV #13, T0
$C$DW$24	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$24, DW_AT_low_pc(0x00)
	.dwattr $C$DW$24, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$24, DW_AT_TI_call

        CALL #_AIC3204_rset ; |52| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |52| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 53,column 5,is_stmt
        MOV #128, T1 ; |53| 
$C$DW$25	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$25, DW_AT_low_pc(0x00)
	.dwattr $C$DW$25, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$25, DW_AT_TI_call

        CALL #_AIC3204_rset ; |53| 
||      MOV #14, T0

                                        ; call occurs [#_AIC3204_rset] ; |53| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 54,column 5,is_stmt
        MOV #128, T1 ; |54| 
        MOV #20, T0 ; |54| 
$C$DW$26	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$26, DW_AT_low_pc(0x00)
	.dwattr $C$DW$26, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$26, DW_AT_TI_call
        CALL #_AIC3204_rset ; |54| 
                                        ; call occurs [#_AIC3204_rset] ; |54| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 55,column 5,is_stmt
        MOV #130, T1 ; |55| 
$C$DW$27	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$27, DW_AT_low_pc(0x00)
	.dwattr $C$DW$27, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$27, DW_AT_TI_call

        CALL #_AIC3204_rset ; |55| 
||      MOV #11, T0

                                        ; call occurs [#_AIC3204_rset] ; |55| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 56,column 5,is_stmt
        MOV #135, T1 ; |56| 
$C$DW$28	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$28, DW_AT_low_pc(0x00)
	.dwattr $C$DW$28, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$28, DW_AT_TI_call

        CALL #_AIC3204_rset ; |56| 
||      MOV #12, T0

                                        ; call occurs [#_AIC3204_rset] ; |56| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 57,column 5,is_stmt
        MOV #135, T1 ; |57| 
        MOV #18, T0 ; |57| 
$C$DW$29	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$29, DW_AT_low_pc(0x00)
	.dwattr $C$DW$29, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$29, DW_AT_TI_call
        CALL #_AIC3204_rset ; |57| 
                                        ; call occurs [#_AIC3204_rset] ; |57| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 58,column 5,is_stmt
        MOV #130, T1 ; |58| 
        MOV #19, T0 ; |58| 
$C$DW$30	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$30, DW_AT_low_pc(0x00)
	.dwattr $C$DW$30, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$30, DW_AT_TI_call
        CALL #_AIC3204_rset ; |58| 
                                        ; call occurs [#_AIC3204_rset] ; |58| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 60,column 5,is_stmt
        MOV #0, T0
$C$DW$31	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$31, DW_AT_low_pc(0x00)
	.dwattr $C$DW$31, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$31, DW_AT_TI_call

        CALL #_AIC3204_rset ; |60| 
||      MOV #1, T1

                                        ; call occurs [#_AIC3204_rset] ; |60| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 61,column 5,is_stmt
        MOV #12, T0
$C$DW$32	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$32, DW_AT_low_pc(0x00)
	.dwattr $C$DW$32, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$32, DW_AT_TI_call

        CALL #_AIC3204_rset ; |61| 
||      MOV #8, T1

                                        ; call occurs [#_AIC3204_rset] ; |61| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 62,column 5,is_stmt
        MOV #13, T0
$C$DW$33	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$33, DW_AT_low_pc(0x00)
	.dwattr $C$DW$33, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$33, DW_AT_TI_call

        CALL #_AIC3204_rset ; |62| 
||      MOV #8, T1

                                        ; call occurs [#_AIC3204_rset] ; |62| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 63,column 5,is_stmt
        MOV #0, T0
$C$DW$34	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$34, DW_AT_low_pc(0x00)
	.dwattr $C$DW$34, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$34, DW_AT_TI_call

        CALL #_AIC3204_rset ; |63| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |63| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 64,column 5,is_stmt
        MOV #64, T0 ; |64| 
$C$DW$35	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$35, DW_AT_low_pc(0x00)
	.dwattr $C$DW$35, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$35, DW_AT_TI_call

        CALL #_AIC3204_rset ; |64| 
||      MOV #2, T1

                                        ; call occurs [#_AIC3204_rset] ; |64| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 65,column 5,is_stmt
        MOV #65, T0 ; |65| 
$C$DW$36	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$36, DW_AT_low_pc(0x00)
	.dwattr $C$DW$36, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$36, DW_AT_TI_call

        CALL #_AIC3204_rset ; |65| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |65| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 66,column 5,is_stmt
        MOV #212, T1 ; |66| 
        MOV #63, T0 ; |66| 
$C$DW$37	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$37, DW_AT_low_pc(0x00)
	.dwattr $C$DW$37, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$37, DW_AT_TI_call
        CALL #_AIC3204_rset ; |66| 
                                        ; call occurs [#_AIC3204_rset] ; |66| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 67,column 5,is_stmt
        MOV #0, T0
$C$DW$38	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$38, DW_AT_low_pc(0x00)
	.dwattr $C$DW$38, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$38, DW_AT_TI_call

        CALL #_AIC3204_rset ; |67| 
||      MOV #1, T1

                                        ; call occurs [#_AIC3204_rset] ; |67| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 68,column 5,is_stmt
        MOV #16, T0 ; |68| 
$C$DW$39	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$39, DW_AT_low_pc(0x00)
	.dwattr $C$DW$39, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$39, DW_AT_TI_call

        CALL #_AIC3204_rset ; |68| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |68| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 69,column 5,is_stmt
        MOV #17, T0 ; |69| 
$C$DW$40	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$40, DW_AT_low_pc(0x00)
	.dwattr $C$DW$40, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$40, DW_AT_TI_call

        CALL #_AIC3204_rset ; |69| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |69| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 70,column 5,is_stmt
        MOV #48, T1 ; |70| 
$C$DW$41	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$41, DW_AT_low_pc(0x00)
	.dwattr $C$DW$41, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$41, DW_AT_TI_call

        CALL #_AIC3204_rset ; |70| 
||      MOV #9, T0

                                        ; call occurs [#_AIC3204_rset] ; |70| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 71,column 5,is_stmt
        MOV #0, T0
$C$DW$42	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$42, DW_AT_low_pc(0x00)
	.dwattr $C$DW$42, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$42, DW_AT_TI_call

        CALL #_AIC3204_rset ; |71| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |71| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 72,column 5,is_stmt
        MOV #100, AC0 ; |72| 
$C$DW$43	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$43, DW_AT_low_pc(0x00)
	.dwattr $C$DW$43, DW_AT_name("_USBSTK5515_wait")
	.dwattr $C$DW$43, DW_AT_TI_call
        CALL #_USBSTK5515_wait ; |72| 
                                        ; call occurs [#_USBSTK5515_wait] ; |72| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 74,column 5,is_stmt
        MOV #0, T0
$C$DW$44	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$44, DW_AT_low_pc(0x00)
	.dwattr $C$DW$44, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$44, DW_AT_TI_call

        CALL #_AIC3204_rset ; |74| 
||      MOV #1, T1

                                        ; call occurs [#_AIC3204_rset] ; |74| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 75,column 5,is_stmt
        MOV #48, T1 ; |75| 
        MOV #52, T0 ; |75| 
$C$DW$45	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$45, DW_AT_low_pc(0x00)
	.dwattr $C$DW$45, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$45, DW_AT_TI_call
        CALL #_AIC3204_rset ; |75| 
                                        ; call occurs [#_AIC3204_rset] ; |75| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 77,column 5,is_stmt
        MOV #48, T1 ; |77| 
        MOV #55, T0 ; |77| 
$C$DW$46	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$46, DW_AT_low_pc(0x00)
	.dwattr $C$DW$46, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$46, DW_AT_TI_call
        CALL #_AIC3204_rset ; |77| 
                                        ; call occurs [#_AIC3204_rset] ; |77| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 78,column 5,is_stmt
        MOV #54, T0 ; |78| 
$C$DW$47	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$47, DW_AT_low_pc(0x00)
	.dwattr $C$DW$47, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$47, DW_AT_TI_call

        CALL #_AIC3204_rset ; |78| 
||      MOV #3, T1

                                        ; call occurs [#_AIC3204_rset] ; |78| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 79,column 5,is_stmt
        MOV #192, T1 ; |79| 
        MOV #57, T0 ; |79| 
$C$DW$48	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$48, DW_AT_low_pc(0x00)
	.dwattr $C$DW$48, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$48, DW_AT_TI_call
        CALL #_AIC3204_rset ; |79| 
                                        ; call occurs [#_AIC3204_rset] ; |79| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 80,column 5,is_stmt
        MOV #59, T0 ; |80| 
$C$DW$49	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$49, DW_AT_low_pc(0x00)
	.dwattr $C$DW$49, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$49, DW_AT_TI_call

        CALL #_AIC3204_rset ; |80| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |80| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 81,column 5,is_stmt
        MOV #60, T0 ; |81| 
$C$DW$50	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$50, DW_AT_low_pc(0x00)
	.dwattr $C$DW$50, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$50, DW_AT_TI_call

        CALL #_AIC3204_rset ; |81| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |81| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 82,column 5,is_stmt
        MOV #0, T0
$C$DW$51	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$51, DW_AT_low_pc(0x00)
	.dwattr $C$DW$51, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$51, DW_AT_TI_call

        CALL #_AIC3204_rset ; |82| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |82| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 83,column 5,is_stmt
        MOV #192, T1 ; |83| 
        MOV #81, T0 ; |83| 
$C$DW$52	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$52, DW_AT_low_pc(0x00)
	.dwattr $C$DW$52, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$52, DW_AT_TI_call
        CALL #_AIC3204_rset ; |83| 
                                        ; call occurs [#_AIC3204_rset] ; |83| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 84,column 5,is_stmt
        MOV #82, T0 ; |84| 
$C$DW$53	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$53, DW_AT_low_pc(0x00)
	.dwattr $C$DW$53, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$53, DW_AT_TI_call

        CALL #_AIC3204_rset ; |84| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |84| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 86,column 5,is_stmt
        MOV #0, T0
$C$DW$54	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$54, DW_AT_low_pc(0x00)
	.dwattr $C$DW$54, DW_AT_name("_AIC3204_rset")
	.dwattr $C$DW$54, DW_AT_TI_call

        CALL #_AIC3204_rset ; |86| 
||      MOV #0, T1

                                        ; call occurs [#_AIC3204_rset] ; |86| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 87,column 5,is_stmt
        MOV #200, AC0 ; |87| 
$C$DW$55	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$55, DW_AT_low_pc(0x00)
	.dwattr $C$DW$55, DW_AT_name("_USBSTK5515_wait")
	.dwattr $C$DW$55, DW_AT_TI_call
        CALL #_USBSTK5515_wait ; |87| 
                                        ; call occurs [#_USBSTK5515_wait] ; |87| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 90,column 5,is_stmt
        MOV #0, *port(#10244) ; |90| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 91,column 5,is_stmt
        MOV #32784, *port(#10240) ; |91| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 92,column 5,is_stmt
        MOV #48, AR2 ; |99| 
        MOV #63, *port(#10260) ; |92| 
$C$L3:    
$C$DW$L$_aic3204_tone_headphone$8$B:
        AMAR *SP(#0), XAR3
	.dwpsn	file "../aic3204_tone_headphone.c",line 99,column 19,is_stmt
        MOV #0, AR1
$C$DW$L$_aic3204_tone_headphone$8$E:
$C$L4:    
$C$DW$L$_aic3204_tone_headphone$9$B:
	.dwpsn	file "../aic3204_tone_headphone.c",line 101,column 23,is_stmt
        BTST #5, *port(#10256), TC1 ; |101| 
        BCC $C$L6,TC1 ; |101| 
                                        ; branchcc occurs ; |101| 
$C$DW$L$_aic3204_tone_headphone$9$E:
$C$L5:    
$C$DW$L$_aic3204_tone_headphone$10$B:
        BTST #5, *port(#10256), TC1 ; |101| 
        BCC $C$L5,!TC1 ; |101| 
                                        ; branchcc occurs ; |101| 
$C$DW$L$_aic3204_tone_headphone$10$E:
$C$L6:    
$C$DW$L$_aic3204_tone_headphone$11$B:
	.dwpsn	file "../aic3204_tone_headphone.c",line 102,column 17,is_stmt
        MOV *AR3+, AR4 ; |102| 
        MOV AR4, *port(#10249) ; |102| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 103,column 17,is_stmt
        MOV AR4, *port(#10253) ; |103| 
	.dwpsn	file "../aic3204_tone_headphone.c",line 99,column 32,is_stmt
        ADD #1, AR1 ; |99| 
        CMP AR1 < AR2, TC1 ; |99| 
        BCC $C$L4,TC1 ; |99| 
                                        ; branchcc occurs ; |99| 
$C$DW$L$_aic3204_tone_headphone$11$E:
$C$DW$L$_aic3204_tone_headphone$12$B:
        B $C$L3
                                        ; branch occurs
$C$DW$L$_aic3204_tone_headphone$12$E:
	.dwcfi	cfa_offset, 1

$C$DW$56	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$56, DW_AT_name("C:\Users\Kurt\Documents\Little_Projects\MCUs\C5515\usbstk5515_BSL_RevA\usbstk5515_v1\tests\aic3204\Debug\aic3204_tone_headphone.asm:$C$L3:1:1307654352")
	.dwattr $C$DW$56, DW_AT_TI_begin_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$56, DW_AT_TI_begin_line(0x61)
	.dwattr $C$DW$56, DW_AT_TI_end_line(0x69)
$C$DW$57	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$57, DW_AT_low_pc($C$DW$L$_aic3204_tone_headphone$8$B)
	.dwattr $C$DW$57, DW_AT_high_pc($C$DW$L$_aic3204_tone_headphone$8$E)
$C$DW$58	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$58, DW_AT_low_pc($C$DW$L$_aic3204_tone_headphone$12$B)
	.dwattr $C$DW$58, DW_AT_high_pc($C$DW$L$_aic3204_tone_headphone$12$E)

$C$DW$59	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$59, DW_AT_name("C:\Users\Kurt\Documents\Little_Projects\MCUs\C5515\usbstk5515_BSL_RevA\usbstk5515_v1\tests\aic3204\Debug\aic3204_tone_headphone.asm:$C$L4:2:1307654352")
	.dwattr $C$DW$59, DW_AT_TI_begin_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$59, DW_AT_TI_begin_line(0x63)
	.dwattr $C$DW$59, DW_AT_TI_end_line(0x68)
$C$DW$60	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$60, DW_AT_low_pc($C$DW$L$_aic3204_tone_headphone$9$B)
	.dwattr $C$DW$60, DW_AT_high_pc($C$DW$L$_aic3204_tone_headphone$9$E)
$C$DW$61	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$61, DW_AT_low_pc($C$DW$L$_aic3204_tone_headphone$11$B)
	.dwattr $C$DW$61, DW_AT_high_pc($C$DW$L$_aic3204_tone_headphone$11$E)

$C$DW$62	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$62, DW_AT_name("C:\Users\Kurt\Documents\Little_Projects\MCUs\C5515\usbstk5515_BSL_RevA\usbstk5515_v1\tests\aic3204\Debug\aic3204_tone_headphone.asm:$C$L5:3:1307654352")
	.dwattr $C$DW$62, DW_AT_TI_begin_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$62, DW_AT_TI_begin_line(0x65)
	.dwattr $C$DW$62, DW_AT_TI_end_line(0x65)
$C$DW$63	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$63, DW_AT_low_pc($C$DW$L$_aic3204_tone_headphone$10$B)
	.dwattr $C$DW$63, DW_AT_high_pc($C$DW$L$_aic3204_tone_headphone$10$E)
	.dwendtag $C$DW$62

	.dwendtag $C$DW$59

	.dwendtag $C$DW$56


$C$DW$64	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$64, DW_AT_name("C:\Users\Kurt\Documents\Little_Projects\MCUs\C5515\usbstk5515_BSL_RevA\usbstk5515_v1\tests\aic3204\Debug\aic3204_tone_headphone.asm:$C$L1:1:1307654352")
	.dwattr $C$DW$64, DW_AT_TI_begin_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$64, DW_AT_TI_begin_line(0x18)
	.dwattr $C$DW$64, DW_AT_TI_end_line(0x18)
$C$DW$65	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$65, DW_AT_low_pc($C$DW$L$_aic3204_tone_headphone$2$B)
	.dwattr $C$DW$65, DW_AT_high_pc($C$DW$L$_aic3204_tone_headphone$2$E)
	.dwendtag $C$DW$64

	.dwattr $C$DW$7, DW_AT_TI_end_file("../aic3204_tone_headphone.c")
	.dwattr $C$DW$7, DW_AT_TI_end_line(0x70)
	.dwattr $C$DW$7, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$7

;******************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                              *
;******************************************************************************
	.global	_USBSTK5515_wait
	.global	_AIC3204_rset

;*******************************************************************************
;* TYPE INFORMATION                                                            *
;*******************************************************************************
$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)
$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)
$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)
$C$DW$T$19	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$19, DW_AT_address_class(0x17)
$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x01)
$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x01)
$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x01)
$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x01)

$C$DW$T$27	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$27, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$27, DW_AT_byte_size(0x30)
$C$DW$66	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$66, DW_AT_upper_bound(0x2f)
	.dwendtag $C$DW$T$27

$C$DW$67	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$67, DW_AT_type(*$C$DW$T$10)
$C$DW$T$28	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$28, DW_AT_type(*$C$DW$67)

$C$DW$T$29	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$29, DW_AT_type(*$C$DW$T$28)
	.dwattr $C$DW$T$29, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$29, DW_AT_byte_size(0x30)
$C$DW$68	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$68, DW_AT_upper_bound(0x2f)
	.dwendtag $C$DW$T$29

$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x01)
$C$DW$T$32	.dwtag  DW_TAG_typedef, DW_AT_name("size_t")
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$32, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$T$32, DW_AT_decl_line(0x19)
	.dwattr $C$DW$T$32, DW_AT_decl_column(0x19)
$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x02)
$C$DW$T$33	.dwtag  DW_TAG_typedef, DW_AT_name("fpos_t")
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$33, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$33, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$T$33, DW_AT_decl_line(0x27)
	.dwattr $C$DW$T$33, DW_AT_decl_column(0x0e)
$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x02)
$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x04)
	.dwattr $C$DW$T$14, DW_AT_bit_size(0x28)
	.dwattr $C$DW$T$14, DW_AT_bit_offset(0x18)
$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x04)
	.dwattr $C$DW$T$15, DW_AT_bit_size(0x28)
	.dwattr $C$DW$T$15, DW_AT_bit_offset(0x18)
$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x02)
$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x02)
$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x02)

$C$DW$T$20	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$20, DW_AT_byte_size(0x0c)
$C$DW$69	.dwtag  DW_TAG_member
	.dwattr $C$DW$69, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$69, DW_AT_name("fd")
	.dwattr $C$DW$69, DW_AT_TI_symbol_name("_fd")
	.dwattr $C$DW$69, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$69, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$69, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$69, DW_AT_decl_line(0x1d)
	.dwattr $C$DW$69, DW_AT_decl_column(0x0b)
$C$DW$70	.dwtag  DW_TAG_member
	.dwattr $C$DW$70, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$70, DW_AT_name("buf")
	.dwattr $C$DW$70, DW_AT_TI_symbol_name("_buf")
	.dwattr $C$DW$70, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$70, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$70, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$70, DW_AT_decl_line(0x1e)
	.dwattr $C$DW$70, DW_AT_decl_column(0x16)
$C$DW$71	.dwtag  DW_TAG_member
	.dwattr $C$DW$71, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$71, DW_AT_name("pos")
	.dwattr $C$DW$71, DW_AT_TI_symbol_name("_pos")
	.dwattr $C$DW$71, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$71, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$71, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$71, DW_AT_decl_line(0x1f)
	.dwattr $C$DW$71, DW_AT_decl_column(0x16)
$C$DW$72	.dwtag  DW_TAG_member
	.dwattr $C$DW$72, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$72, DW_AT_name("bufend")
	.dwattr $C$DW$72, DW_AT_TI_symbol_name("_bufend")
	.dwattr $C$DW$72, DW_AT_data_member_location[DW_OP_plus_uconst 0x6]
	.dwattr $C$DW$72, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$72, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$72, DW_AT_decl_line(0x20)
	.dwattr $C$DW$72, DW_AT_decl_column(0x16)
$C$DW$73	.dwtag  DW_TAG_member
	.dwattr $C$DW$73, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$73, DW_AT_name("buff_stop")
	.dwattr $C$DW$73, DW_AT_TI_symbol_name("_buff_stop")
	.dwattr $C$DW$73, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$73, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$73, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$73, DW_AT_decl_line(0x21)
	.dwattr $C$DW$73, DW_AT_decl_column(0x16)
$C$DW$74	.dwtag  DW_TAG_member
	.dwattr $C$DW$74, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$74, DW_AT_name("flags")
	.dwattr $C$DW$74, DW_AT_TI_symbol_name("_flags")
	.dwattr $C$DW$74, DW_AT_data_member_location[DW_OP_plus_uconst 0xa]
	.dwattr $C$DW$74, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$74, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$74, DW_AT_decl_line(0x22)
	.dwattr $C$DW$74, DW_AT_decl_column(0x16)
	.dwendtag $C$DW$T$20

	.dwattr $C$DW$T$20, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$T$20, DW_AT_decl_line(0x1c)
	.dwattr $C$DW$T$20, DW_AT_decl_column(0x10)
$C$DW$T$34	.dwtag  DW_TAG_typedef, DW_AT_name("FILE")
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$34, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$34, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdio.h")
	.dwattr $C$DW$T$34, DW_AT_decl_line(0x23)
	.dwattr $C$DW$T$34, DW_AT_decl_column(0x03)
$C$DW$T$35	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$35, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$35, DW_AT_name("signed char")
	.dwattr $C$DW$T$35, DW_AT_byte_size(0x01)
$C$DW$T$36	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$T$35)
	.dwattr $C$DW$T$36, DW_AT_address_class(0x17)
$C$DW$T$37	.dwtag  DW_TAG_typedef, DW_AT_name("va_list")
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$T$37, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$37, DW_AT_decl_file("C:/Program Files (x86)/Texas Instruments/ccsv5/tools/compiler/c5500/include/stdarg.h")
	.dwattr $C$DW$T$37, DW_AT_decl_line(0x0d)
	.dwattr $C$DW$T$37, DW_AT_decl_column(0x0f)
	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

$C$DW$CIE	.dwcie 91
	.dwcfi	cfa_register, 36
	.dwcfi	cfa_offset, 0
	.dwcfi	undefined, 0
	.dwcfi	undefined, 1
	.dwcfi	undefined, 2
	.dwcfi	undefined, 3
	.dwcfi	undefined, 4
	.dwcfi	undefined, 5
	.dwcfi	undefined, 6
	.dwcfi	undefined, 7
	.dwcfi	undefined, 8
	.dwcfi	undefined, 9
	.dwcfi	undefined, 10
	.dwcfi	undefined, 11
	.dwcfi	undefined, 12
	.dwcfi	undefined, 13
	.dwcfi	same_value, 14
	.dwcfi	same_value, 15
	.dwcfi	undefined, 16
	.dwcfi	undefined, 17
	.dwcfi	undefined, 18
	.dwcfi	undefined, 19
	.dwcfi	undefined, 20
	.dwcfi	undefined, 21
	.dwcfi	undefined, 22
	.dwcfi	undefined, 23
	.dwcfi	undefined, 24
	.dwcfi	undefined, 25
	.dwcfi	same_value, 26
	.dwcfi	same_value, 27
	.dwcfi	same_value, 28
	.dwcfi	same_value, 29
	.dwcfi	same_value, 30
	.dwcfi	same_value, 31
	.dwcfi	undefined, 32
	.dwcfi	undefined, 33
	.dwcfi	undefined, 34
	.dwcfi	undefined, 35
	.dwcfi	undefined, 36
	.dwcfi	undefined, 37
	.dwcfi	undefined, 38
	.dwcfi	undefined, 39
	.dwcfi	undefined, 40
	.dwcfi	undefined, 41
	.dwcfi	undefined, 42
	.dwcfi	undefined, 43
	.dwcfi	undefined, 44
	.dwcfi	undefined, 45
	.dwcfi	undefined, 46
	.dwcfi	undefined, 47
	.dwcfi	undefined, 48
	.dwcfi	undefined, 49
	.dwcfi	undefined, 50
	.dwcfi	undefined, 51
	.dwcfi	undefined, 52
	.dwcfi	undefined, 53
	.dwcfi	undefined, 54
	.dwcfi	undefined, 55
	.dwcfi	undefined, 56
	.dwcfi	undefined, 57
	.dwcfi	undefined, 58
	.dwcfi	undefined, 59
	.dwcfi	undefined, 60
	.dwcfi	undefined, 61
	.dwcfi	undefined, 62
	.dwcfi	undefined, 63
	.dwcfi	undefined, 64
	.dwcfi	undefined, 65
	.dwcfi	undefined, 66
	.dwcfi	undefined, 67
	.dwcfi	undefined, 68
	.dwcfi	undefined, 69
	.dwcfi	undefined, 70
	.dwcfi	undefined, 71
	.dwcfi	undefined, 72
	.dwcfi	undefined, 73
	.dwcfi	undefined, 74
	.dwcfi	undefined, 75
	.dwcfi	undefined, 76
	.dwcfi	undefined, 77
	.dwcfi	undefined, 78
	.dwcfi	undefined, 79
	.dwcfi	undefined, 80
	.dwcfi	undefined, 81
	.dwcfi	undefined, 82
	.dwcfi	undefined, 83
	.dwcfi	undefined, 84
	.dwcfi	undefined, 85
	.dwcfi	undefined, 86
	.dwcfi	undefined, 87
	.dwcfi	undefined, 88
	.dwcfi	undefined, 89
	.dwcfi	undefined, 90
	.dwcfi	undefined, 91
	.dwendentry

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$75	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC0")
	.dwattr $C$DW$75, DW_AT_location[DW_OP_reg0]
$C$DW$76	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC0")
	.dwattr $C$DW$76, DW_AT_location[DW_OP_reg1]
$C$DW$77	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC0_G")
	.dwattr $C$DW$77, DW_AT_location[DW_OP_reg2]
$C$DW$78	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC1")
	.dwattr $C$DW$78, DW_AT_location[DW_OP_reg3]
$C$DW$79	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC1")
	.dwattr $C$DW$79, DW_AT_location[DW_OP_reg4]
$C$DW$80	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC1_G")
	.dwattr $C$DW$80, DW_AT_location[DW_OP_reg5]
$C$DW$81	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC2")
	.dwattr $C$DW$81, DW_AT_location[DW_OP_reg6]
$C$DW$82	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC2")
	.dwattr $C$DW$82, DW_AT_location[DW_OP_reg7]
$C$DW$83	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC2_G")
	.dwattr $C$DW$83, DW_AT_location[DW_OP_reg8]
$C$DW$84	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC3")
	.dwattr $C$DW$84, DW_AT_location[DW_OP_reg9]
$C$DW$85	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC3")
	.dwattr $C$DW$85, DW_AT_location[DW_OP_reg10]
$C$DW$86	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AC3_G")
	.dwattr $C$DW$86, DW_AT_location[DW_OP_reg11]
$C$DW$87	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("T0")
	.dwattr $C$DW$87, DW_AT_location[DW_OP_reg12]
$C$DW$88	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("T1")
	.dwattr $C$DW$88, DW_AT_location[DW_OP_reg13]
$C$DW$89	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("T2")
	.dwattr $C$DW$89, DW_AT_location[DW_OP_reg14]
$C$DW$90	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("T3")
	.dwattr $C$DW$90, DW_AT_location[DW_OP_reg15]
$C$DW$91	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR0")
	.dwattr $C$DW$91, DW_AT_location[DW_OP_reg16]
$C$DW$92	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR0")
	.dwattr $C$DW$92, DW_AT_location[DW_OP_reg17]
$C$DW$93	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR1")
	.dwattr $C$DW$93, DW_AT_location[DW_OP_reg18]
$C$DW$94	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR1")
	.dwattr $C$DW$94, DW_AT_location[DW_OP_reg19]
$C$DW$95	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR2")
	.dwattr $C$DW$95, DW_AT_location[DW_OP_reg20]
$C$DW$96	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR2")
	.dwattr $C$DW$96, DW_AT_location[DW_OP_reg21]
$C$DW$97	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR3")
	.dwattr $C$DW$97, DW_AT_location[DW_OP_reg22]
$C$DW$98	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR3")
	.dwattr $C$DW$98, DW_AT_location[DW_OP_reg23]
$C$DW$99	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR4")
	.dwattr $C$DW$99, DW_AT_location[DW_OP_reg24]
$C$DW$100	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR4")
	.dwattr $C$DW$100, DW_AT_location[DW_OP_reg25]
$C$DW$101	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR5")
	.dwattr $C$DW$101, DW_AT_location[DW_OP_reg26]
$C$DW$102	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR5")
	.dwattr $C$DW$102, DW_AT_location[DW_OP_reg27]
$C$DW$103	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR6")
	.dwattr $C$DW$103, DW_AT_location[DW_OP_reg28]
$C$DW$104	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR6")
	.dwattr $C$DW$104, DW_AT_location[DW_OP_reg29]
$C$DW$105	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR7")
	.dwattr $C$DW$105, DW_AT_location[DW_OP_reg30]
$C$DW$106	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XAR7")
	.dwattr $C$DW$106, DW_AT_location[DW_OP_reg31]
$C$DW$107	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FP")
	.dwattr $C$DW$107, DW_AT_location[DW_OP_regx 0x20]
$C$DW$108	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XFP")
	.dwattr $C$DW$108, DW_AT_location[DW_OP_regx 0x21]
$C$DW$109	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC")
	.dwattr $C$DW$109, DW_AT_location[DW_OP_regx 0x22]
$C$DW$110	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SP")
	.dwattr $C$DW$110, DW_AT_location[DW_OP_regx 0x23]
$C$DW$111	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XSP")
	.dwattr $C$DW$111, DW_AT_location[DW_OP_regx 0x24]
$C$DW$112	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BKC")
	.dwattr $C$DW$112, DW_AT_location[DW_OP_regx 0x25]
$C$DW$113	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BK03")
	.dwattr $C$DW$113, DW_AT_location[DW_OP_regx 0x26]
$C$DW$114	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BK47")
	.dwattr $C$DW$114, DW_AT_location[DW_OP_regx 0x27]
$C$DW$115	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ST0")
	.dwattr $C$DW$115, DW_AT_location[DW_OP_regx 0x28]
$C$DW$116	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ST1")
	.dwattr $C$DW$116, DW_AT_location[DW_OP_regx 0x29]
$C$DW$117	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ST2")
	.dwattr $C$DW$117, DW_AT_location[DW_OP_regx 0x2a]
$C$DW$118	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ST3")
	.dwattr $C$DW$118, DW_AT_location[DW_OP_regx 0x2b]
$C$DW$119	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("MDP")
	.dwattr $C$DW$119, DW_AT_location[DW_OP_regx 0x2c]
$C$DW$120	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("MDP05")
	.dwattr $C$DW$120, DW_AT_location[DW_OP_regx 0x2d]
$C$DW$121	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("MDP67")
	.dwattr $C$DW$121, DW_AT_location[DW_OP_regx 0x2e]
$C$DW$122	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BRC0")
	.dwattr $C$DW$122, DW_AT_location[DW_OP_regx 0x2f]
$C$DW$123	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RSA0")
	.dwattr $C$DW$123, DW_AT_location[DW_OP_regx 0x30]
$C$DW$124	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RSA0_H")
	.dwattr $C$DW$124, DW_AT_location[DW_OP_regx 0x31]
$C$DW$125	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("REA0")
	.dwattr $C$DW$125, DW_AT_location[DW_OP_regx 0x32]
$C$DW$126	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("REA0_H")
	.dwattr $C$DW$126, DW_AT_location[DW_OP_regx 0x33]
$C$DW$127	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BRS1")
	.dwattr $C$DW$127, DW_AT_location[DW_OP_regx 0x34]
$C$DW$128	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BRC1")
	.dwattr $C$DW$128, DW_AT_location[DW_OP_regx 0x35]
$C$DW$129	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RSA1")
	.dwattr $C$DW$129, DW_AT_location[DW_OP_regx 0x36]
$C$DW$130	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RSA1_H")
	.dwattr $C$DW$130, DW_AT_location[DW_OP_regx 0x37]
$C$DW$131	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("REA1")
	.dwattr $C$DW$131, DW_AT_location[DW_OP_regx 0x38]
$C$DW$132	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("REA1_H")
	.dwattr $C$DW$132, DW_AT_location[DW_OP_regx 0x39]
$C$DW$133	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CSR")
	.dwattr $C$DW$133, DW_AT_location[DW_OP_regx 0x3a]
$C$DW$134	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RPTC")
	.dwattr $C$DW$134, DW_AT_location[DW_OP_regx 0x3b]
$C$DW$135	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CDP")
	.dwattr $C$DW$135, DW_AT_location[DW_OP_regx 0x3c]
$C$DW$136	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("XCDP")
	.dwattr $C$DW$136, DW_AT_location[DW_OP_regx 0x3d]
$C$DW$137	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TRN0")
	.dwattr $C$DW$137, DW_AT_location[DW_OP_regx 0x3e]
$C$DW$138	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TRN1")
	.dwattr $C$DW$138, DW_AT_location[DW_OP_regx 0x3f]
$C$DW$139	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BSA01")
	.dwattr $C$DW$139, DW_AT_location[DW_OP_regx 0x40]
$C$DW$140	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BSA23")
	.dwattr $C$DW$140, DW_AT_location[DW_OP_regx 0x41]
$C$DW$141	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BSA45")
	.dwattr $C$DW$141, DW_AT_location[DW_OP_regx 0x42]
$C$DW$142	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BSA67")
	.dwattr $C$DW$142, DW_AT_location[DW_OP_regx 0x43]
$C$DW$143	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BSAC")
	.dwattr $C$DW$143, DW_AT_location[DW_OP_regx 0x44]
$C$DW$144	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CARRY")
	.dwattr $C$DW$144, DW_AT_location[DW_OP_regx 0x45]
$C$DW$145	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TC1")
	.dwattr $C$DW$145, DW_AT_location[DW_OP_regx 0x46]
$C$DW$146	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TC2")
	.dwattr $C$DW$146, DW_AT_location[DW_OP_regx 0x47]
$C$DW$147	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("M40")
	.dwattr $C$DW$147, DW_AT_location[DW_OP_regx 0x48]
$C$DW$148	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SXMD")
	.dwattr $C$DW$148, DW_AT_location[DW_OP_regx 0x49]
$C$DW$149	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ARMS")
	.dwattr $C$DW$149, DW_AT_location[DW_OP_regx 0x4a]
$C$DW$150	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("C54CM")
	.dwattr $C$DW$150, DW_AT_location[DW_OP_regx 0x4b]
$C$DW$151	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SATA")
	.dwattr $C$DW$151, DW_AT_location[DW_OP_regx 0x4c]
$C$DW$152	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SATD")
	.dwattr $C$DW$152, DW_AT_location[DW_OP_regx 0x4d]
$C$DW$153	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RDM")
	.dwattr $C$DW$153, DW_AT_location[DW_OP_regx 0x4e]
$C$DW$154	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FRCT")
	.dwattr $C$DW$154, DW_AT_location[DW_OP_regx 0x4f]
$C$DW$155	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SMUL")
	.dwattr $C$DW$155, DW_AT_location[DW_OP_regx 0x50]
$C$DW$156	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("INTM")
	.dwattr $C$DW$156, DW_AT_location[DW_OP_regx 0x51]
$C$DW$157	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR0LC")
	.dwattr $C$DW$157, DW_AT_location[DW_OP_regx 0x52]
$C$DW$158	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR1LC")
	.dwattr $C$DW$158, DW_AT_location[DW_OP_regx 0x53]
$C$DW$159	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR2LC")
	.dwattr $C$DW$159, DW_AT_location[DW_OP_regx 0x54]
$C$DW$160	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR3LC")
	.dwattr $C$DW$160, DW_AT_location[DW_OP_regx 0x55]
$C$DW$161	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR4LC")
	.dwattr $C$DW$161, DW_AT_location[DW_OP_regx 0x56]
$C$DW$162	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR5LC")
	.dwattr $C$DW$162, DW_AT_location[DW_OP_regx 0x57]
$C$DW$163	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR6LC")
	.dwattr $C$DW$163, DW_AT_location[DW_OP_regx 0x58]
$C$DW$164	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AR7LC")
	.dwattr $C$DW$164, DW_AT_location[DW_OP_regx 0x59]
$C$DW$165	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CDPLC")
	.dwattr $C$DW$165, DW_AT_location[DW_OP_regx 0x5a]
$C$DW$166	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CIE_RETA")
	.dwattr $C$DW$166, DW_AT_location[DW_OP_regx 0x5b]
	.dwendtag $C$DW$CU

