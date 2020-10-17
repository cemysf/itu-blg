/* Test for atan2: nois */
#define NX 400
#define FNAME "t7"
#define MAXERROR 20

DATA x1[NX] ={
1636,
-14994,
-8783,
-3316,
-12429,
-1880,
-14698,
16274,
6369,
3769,
3839,
10805,
15705,
-2050,
11345,
-3372,
-2609,
12845,
-5057,
10106,
16196,
9210,
11528,
5263,
-7467,
-8492,
-2427,
3197,
-2620,
8766,
-15542,
6317,
8305,
14862,
-3692,
-14544,
-4085,
5161,
6611,
-13411,
14680,
1142,
13443,
-6248,
7369,
-3819,
13070,
-14141,
-7700,
4082,
5907,
7763,
14188,
3758,
7809,
4474,
-10809,
-7460,
10238,
-3170,
5246,
-7010,
15119,
2509,
15290,
456,
11935,
-9000,
-8406,
13069,
6855,
15569,
-1325,
7922,
5537,
-15414,
-4904,
-13695,
-14390,
8523,
4189,
998,
16032,
-6457,
-10463,
2269,
-1095,
-3531,
-15486,
-5194,
15609,
2521,
8868,
4142,
7637,
-11490,
-2797,
-14123,
12589,
10879,
-6055,
13043,
8294,
-11385,
7059,
11195,
9288,
16313,
2822,
-4562,
-4132,
15965,
12688,
-10301,
-8384,
-8295,
-10688,
-5429,
-3073,
4056,
13042,
5871,
-12074,
-888,
15317,
-41,
-3372,
15998,
8793,
15832,
-8544,
-1096,
-15226,
7771,
11459,
547,
-11679,
9076,
-1722,
-10962,
-7977,
7515,
-14375,
-12672,
10310,
-1261,
13395,
12986,
-9602,
12258,
-8608,
6039,
15077,
-2406,
-10677,
-3363,
5601,
-489,
-3847,
2081,
-331,
-11301,
4953,
7438,
-16264,
13407,
5304,
-14757,
-1565,
-11007,
-961,
10599,
11468,
15212,
10246,
-7720,
-9622,
14163,
-3495,
-14340,
-14949,
-16183,
10391,
13605,
7918,
-9705,
-8709,
13058,
9429,
-10388,
188,
-14386,
-11951,
-15655,
12118,
3740,
-5271,
6084,
-9261,
-8800,
-1893,
-5444,
-7651,
8356,
-2743,
14761,
11029,
12972,
-8019,
692,
-5349,
5118,
-3446,
-13085,
-1248,
1847,
-6477,
4285,
796,
-6262,
-1209,
-12039,
8554,
-11963,
-2257,
11773,
-1082,
-7005,
-14245,
5145,
4268,
7587,
14906,
-4282,
-14110,
12043,
-6728,
1749,
9246,
-14084,
4370,
-15037,
-15590,
7266,
12641,
14326,
13917,
8399,
-4017,
10951,
6116,
1809,
-13561,
1795,
5879,
-2375,
-11046,
6340,
628,
9848,
9124,
14026,
7413,
-13259,
-1661,
15617,
15366,
4760,
-13345,
8914,
-3147,
-7219,
-8964,
-11639,
-13343,
6643,
5938,
-1388,
1060,
-6608,
-3179,
-11388,
9509,
-9878,
-181,
-6447,
-11536,
15205,
7763,
614,
13051,
6783,
-3447,
4659,
-6412,
-13604,
12629,
-13305,
14785,
3873,
8538,
3956,
2596,
-7181,
-13115,
7260,
11188,
10527,
1428,
-4443,
31,
-5558,
-8829,
3438,
-14833,
7751,
-402,
15918,
15679,
-11721,
14056,
-15865,
7462,
7660,
-14157,
9748,
-1530,
-9479,
7709,
2536,
9485,
-13673,
-4070,
-9799,
4775,
-12325,
247,
-12925,
-15430,
-14723,
-10397,
317,
4837,
314,
3250,
-5360,
7324,
-12515,
650,
16226,
-6116,
190,
10479,
-6596,
6835,
12108,
5127,
11868,
13979,
14376,
5430,
3202,
-3128,
-11992,
-6490,
-1300,
107,
8616,
14558,
4910,
14627,
-1189,
-7498,
-14110,
-10244,
-4947,
13576,
-15933,
15975,
-10682,
-3180,
-3301,
9360,
193,
2044,
6594,
-7033,
15946,
-9034,
31,
-2296,
524,
-14849,
15226,
-14229,
328,
6730,
4093,
-8929,
4282,
};

DATA x2[NX] ={
-11365,
-6200,
4893,
10996,
-15804,
-3133,
9814,
-11155,
-6146,
4295,
2983,
-14599,
12107,
7471,
-15841,
7998,
-6826,
8404,
-12984,
-8932,
-395,
12231,
2591,
-2579,
10265,
6399,
-1924,
-960,
12498,
4755,
-11592,
-9425,
-12256,
1183,
11136,
-8523,
-15652,
-11523,
-797,
12387,
11902,
16257,
8432,
12641,
-4303,
7076,
-7022,
9486,
-9653,
-2299,
4222,
1945,
-8312,
5129,
-12048,
439,
-7406,
2862,
-7588,
9315,
-11514,
8955,
652,
2841,
622,
-11778,
-6032,
11838,
-2181,
-14435,
12644,
-7996,
-6962,
-9046,
2989,
2108,
11991,
-9187,
-6513,
2853,
13174,
778,
5530,
5796,
14841,
4061,
-1380,
4842,
15691,
-2574,
15591,
610,
1406,
-3961,
11442,
1494,
10327,
-467,
-12577,
-11684,
9329,
-7572,
1860,
-11937,
-2473,
-14495,
9726,
1950,
8892,
16221,
-13449,
7253,
16296,
-12842,
-1417,
-12024,
6679,
-6348,
-14276,
-10690,
-10076,
5582,
-3701,
-14081,
5933,
11670,
-13202,
-3543,
-4065,
508,
12919,
4647,
-9723,
-14127,
9835,
-2521,
12855,
16119,
-3248,
-5220,
-6005,
-4447,
3792,
3193,
6070,
15526,
-7198,
-10683,
13825,
-7856,
-4094,
4743,
-6014,
-10079,
-8743,
-9180,
-13781,
-12325,
1232,
6189,
7213,
14379,
-16115,
2677,
1846,
6206,
8551,
10626,
907,
-5193,
-14146,
-7732,
16193,
-3754,
9380,
12111,
-13592,
-534,
11290,
-1119,
3252,
-9563,
559,
-11206,
8008,
-358,
4904,
-15016,
-5413,
-2184,
-13153,
5928,
-15495,
-5870,
-14664,
-4274,
-3805,
-5378,
12802,
-8581,
-13731,
-6505,
-10485,
7083,
9511,
-5527,
9228,
9066,
-12953,
-5604,
-7828,
-3657,
13021,
8742,
-8379,
-1486,
-7459,
-2517,
6520,
10402,
10665,
-3170,
4968,
-11389,
-5246,
-15752,
8791,
-1380,
-14957,
-13122,
14972,
3565,
-8299,
14074,
-2296,
-14779,
13267,
15671,
5170,
7437,
-373,
6088,
-4491,
-3244,
470,
-14893,
16101,
-6239,
-7980,
3608,
-1737,
-2673,
-2889,
7014,
-13016,
-3927,
8272,
-11496,
5272,
-8620,
7458,
-7912,
-999,
11715,
10925,
-787,
-5238,
1383,
2015,
13934,
-7393,
-6696,
3688,
12800,
7027,
-9781,
-12840,
7800,
8586,
-7242,
11312,
4076,
3987,
14906,
-6704,
4319,
1025,
12162,
2767,
3363,
-388,
14505,
-5029,
-9841,
-13169,
4985,
3472,
10193,
-1253,
-13313,
-13019,
12273,
-14393,
11378,
-1504,
-8252,
16010,
2108,
-9158,
12370,
7457,
11570,
-10562,
1321,
-911,
7615,
15748,
5466,
6001,
12301,
252,
-1052,
-8361,
2164,
8543,
-5073,
-1719,
517,
-11228,
15757,
-6594,
-11318,
14278,
5697,
-2362,
10905,
-10770,
-1945,
8272,
3785,
-8055,
-4902,
3703,
-5317,
4456,
544,
640,
4143,
14719,
-9061,
16208,
12367,
4127,
-9441,
13616,
-11985,
15338,
3929,
4613,
-15939,
9487,
13093,
-16313,
535,
4077,
-7694,
-3310,
15651,
-6432,
2187,
-9302,
-11947,
15683,
-9361,
-11935,
-14658,
-7712,
8432,
-2107,
218,
-173,
-13297,
15441,
-2461,
-7530,
14262,
-9150,
-10171,
-7189,
5704,
3218,
-3642,
14282,
10713,
-14704,
10738,
-3676,
-1778,
-16083,
-7203,
};

DATA rtest[] ={
31277,
-20474,
-11083,
-3055,
-25817,
-27130,
-10243,
22651,
24390,
7512,
9495,
26122,
9534,
-2794,
26286,
-4162,
-28960,
10341,
-28894,
23933,
16638,
6732,
14078,
21137,
-6560,
-9649,
-23374,
19428,
-2155,
11200,
-23068,
26609,
26556,
15556,
-3339,
-21913,
-30105,
28376,
17635,
-8606,
9278,
731,
10541,
-4789,
21896,
-5162,
21526,
-10221,
-25745,
21734,
9912,
13824,
21911,
6595,
26770,
15363,
-22649,
-12563,
23036,
-3421,
28309,
-6928,
15934,
7544,
15960,
32364,
21265,
-6780,
-19031,
25094,
5182,
21333,
-30806,
25266,
11221,
-14966,
-4049,
-22547,
-20817,
13015,
3211,
9479,
12920,
-8754,
-6405,
5315,
-25768,
-6573,
-8123,
-21183,
8198,
13909,
14744,
24342,
6139,
-15036,
-2759,
-16729,
24571,
24948,
-6005,
21870,
14083,
-24823,
19899,
25909,
7952,
15143,
3205,
-2860,
-29659,
11936,
6900,
-25717,
-18130,
-26469,
-10558,
-25388,
-30557,
28986,
23245,
8455,
-19486,
-32111,
12530,
-36,
-30159,
18658,
20901,
16049,
-6094,
-2416,
-22312,
27523,
8986,
30539,
-7692,
5349,
-27684,
-21020,
-23115,
21957,
-13694,
-13809,
10834,
-845,
21527,
23564,
-6332,
22329,
-21014,
9440,
20343,
-30324,
-23541,
-29105,
28741,
-32354,
-13153,
3384,
-479,
-6948,
29658,
12781,
-15205,
11862,
5791,
-9875,
-10905,
-20982,
-32061,
22958,
6428,
18907,
8652,
-5919,
-26343,
16777,
-3131,
-17197,
-14150,
-21951,
15823,
23571,
8133,
-16769,
-11035,
25302,
21819,
-18545,
32619,
-12307,
-25915,
-20126,
25565,
25271,
-22906,
23935,
-6532,
-24444,
-31339,
-25500,
-26193,
9050,
-2928,
20121,
9117,
10022,
-26986,
31487,
-26515,
22855,
-2698,
-10241,
-31226,
23452,
-25310,
21924,
1267,
-5653,
-1178,
-19069,
10896,
-24320,
-28531,
26074,
-1277,
-18413,
-24830,
28870,
2897,
11802,
21682,
-3080,
-18067,
25636,
-4896,
1159,
11066,
-11317,
17271,
-12372,
-19310,
20764,
15996,
24778,
7435,
23048,
-27904,
13064,
19271,
26562,
-18573,
2613,
28343,
-27093,
-9679,
27511,
1237,
23883,
9236,
21741,
17781,
-8836,
-1574,
16909,
19811,
13434,
-14821,
5936,
-28571,
-24185,
-12313,
-7697,
-11328,
26545,
28250,
-1837,
1281,
-25054,
-2857,
-12799,
12243,
-6104,
-32486,
-10227,
-15459,
9347,
12812,
1885,
16694,
4563,
-26501,
28156,
-28042,
-12721,
13585,
-9565,
17266,
29815,
26713,
3252,
30907,
-5872,
-17575,
25242,
6362,
14323,
31155,
-3597,
43,
-4671,
-25505,
12559,
-17024,
8284,
-266,
12934,
12571,
-7940,
16197,
-17075,
25168,
13513,
-10721,
21389,
-25181,
-15815,
26493,
1664,
22721,
-23596,
-2897,
-10891,
21176,
-8829,
32529,
-17942,
-11251,
-13760,
-23260,
32095,
9569,
32153,
6573,
-15329,
15475,
-13049,
460,
21696,
-3764,
160,
12471,
-26407,
4853,
24523,
3365,
13049,
13059,
25113,
5422,
2502,
-30792,
-15919,
-10533,
-31022,
32430,
5249,
20723,
12013,
22292,
-31733,
-4652,
-22493,
-25370,
-29373,
21773,
-11307,
17752,
-16171,
-16951,
-30230,
5684,
31952,
30004,
4517,
-25933,
22306,
-23395,
57,
-6465,
31277,
-8395,
9989,
-24747,
319,
21599,
20659,
-27482,
27174,
};

DATA r[NX];
