/* Test for atan2: nois */
#define NX 400
#define FNAME "t4"
#define MAXERROR 20

DATA x1[NX] ={
-11245,
-2741,
-13303,
-1640,
12096,
-3551,
-8101,
-4772,
7962,
4942,
14411,
10905,
-984,
4255,
-14477,
1382,
-1451,
11898,
11639,
-909,
9402,
5111,
-16383,
-12084,
-168,
-15128,
-8931,
-5640,
13090,
-6104,
-8137,
-2196,
11219,
-10339,
268,
-1565,
-5715,
-3930,
12664,
8561,
12575,
-1396,
9804,
-11991,
-14244,
-4091,
-4144,
-524,
15383,
-5175,
-8104,
2782,
777,
-11029,
-446,
-129,
11246,
10033,
11724,
3596,
2154,
3667,
-13010,
-11196,
-2830,
1980,
-7580,
9314,
-3674,
-15369,
2802,
1919,
-9808,
-13519,
14196,
-7885,
-9694,
-14772,
3479,
1519,
-13244,
4489,
-1869,
-14209,
-4119,
-8221,
13922,
4243,
12396,
4642,
9778,
-2129,
15766,
-13240,
901,
1496,
-7067,
-4234,
-14264,
1468,
11022,
-11622,
-10764,
-14154,
10617,
-11994,
12609,
483,
15192,
-12436,
-14802,
-3927,
-2858,
-3231,
-2589,
-4032,
13348,
5576,
15134,
-11043,
8148,
-4127,
-1500,
-15120,
2046,
-4184,
9594,
9674,
-3837,
-8101,
-5147,
15329,
-662,
-4315,
8669,
-4026,
13117,
-10373,
-4315,
13679,
522,
-13425,
7711,
-16230,
3379,
14971,
-3361,
7587,
6050,
15680,
-9706,
3057,
14797,
-7855,
481,
4467,
-3245,
-439,
8207,
-12249,
-14973,
-4229,
6334,
14281,
-735,
-12154,
-530,
14601,
-4334,
-5620,
8942,
-6643,
-10556,
6252,
-7735,
-1385,
11262,
12501,
6554,
8378,
15549,
-3206,
-12082,
7364,
13091,
-10790,
-14974,
-683,
-13306,
4917,
14820,
-1386,
1209,
-14205,
-201,
-2702,
-6807,
-6892,
8318,
-13212,
-13864,
7239,
8681,
5176,
10171,
-4121,
-6349,
-4237,
6775,
-10867,
10280,
-1107,
7284,
16216,
-4505,
7564,
4904,
5942,
-16135,
5051,
14589,
3712,
9271,
-16281,
9731,
4647,
-10536,
963,
-9216,
1575,
-14476,
2870,
-2749,
-10275,
-14290,
-13934,
-6225,
14552,
15752,
1806,
16008,
6277,
-8465,
10152,
14238,
-12163,
6122,
-6644,
4824,
-1188,
13854,
-8463,
5248,
-5496,
-762,
-1023,
6748,
-8521,
7117,
11967,
-2917,
-2465,
14886,
12498,
6507,
-6377,
10791,
15421,
-6550,
16320,
-1942,
-16180,
-6819,
6287,
-234,
-13649,
-9968,
15650,
-4384,
-11815,
-15900,
4609,
7790,
-15507,
-13037,
12889,
8647,
2709,
6076,
15307,
1650,
9083,
3616,
16010,
-14803,
15905,
-9675,
13516,
5425,
-1235,
-14800,
-1296,
9829,
-6900,
6393,
-7888,
6987,
7221,
7644,
4009,
16049,
-11391,
-9722,
10463,
-14469,
1262,
-10153,
3260,
-6807,
-13393,
222,
12587,
3787,
-14864,
14809,
-10845,
10704,
3650,
11380,
-12644,
4890,
-12622,
-871,
6002,
-12016,
-1177,
-14049,
2661,
2162,
-8020,
-8569,
-15861,
-3777,
8431,
2463,
-3012,
-9971,
399,
6991,
12038,
7923,
16215,
12018,
-465,
13215,
-15718,
4482,
14551,
-15048,
-7023,
5808,
2824,
-14255,
12426,
-396,
12828,
8595,
5089,
15449,
-10776,
-11929,
8363,
-6121,
-1204,
-5261,
-16069,
-5446,
-8296,
16189,
13290,
-4923,
-7271,
-13339,
-8502,
13161,
-5759,
2382,
-10320,
7796,
-12722,
-3809,
11874,
11701,
10465,
-8333,
13028,
3412,
-11805,
-11098,
12555,
};

DATA x2[NX] ={
15682,
3320,
-4528,
-8801,
-1647,
4689,
-8349,
-1048,
-84,
-13928,
8736,
-14897,
-10974,
9083,
-9557,
-8134,
-3391,
-633,
304,
4089,
4114,
16095,
-4613,
-7340,
5837,
287,
-7312,
2583,
10579,
14466,
-1825,
-2516,
16259,
3739,
14551,
13503,
10321,
6214,
-6270,
1907,
4481,
8817,
-14613,
-12621,
11337,
-10735,
-15172,
-6142,
10397,
-8695,
2865,
13900,
-5569,
-9649,
-4440,
15588,
7107,
4696,
9259,
-1098,
-8773,
-5968,
9463,
4405,
5236,
1232,
13737,
9192,
-5678,
7823,
-2040,
3008,
-12632,
-5926,
3993,
12929,
15191,
-15727,
-12758,
-3178,
-13199,
-6781,
5856,
15722,
-3295,
10515,
-12071,
11301,
-8758,
-14183,
-5523,
2465,
-11901,
12052,
-5595,
-393,
-2243,
-7847,
15827,
15260,
14697,
-1582,
-5515,
-16130,
-10950,
10753,
4699,
-5824,
-15520,
-4737,
7992,
-6597,
-10446,
-2779,
12037,
4094,
-14575,
-3143,
-6489,
-11393,
-6253,
-16277,
-2051,
5781,
10581,
8384,
-11055,
1705,
822,
13741,
-1904,
-14916,
15223,
-15943,
1705,
14231,
13062,
3866,
6551,
14388,
-1570,
-10595,
3826,
602,
-4440,
8956,
10757,
-5951,
3145,
9235,
-15283,
11697,
5984,
9891,
13687,
-3666,
-918,
-13498,
13930,
5848,
4621,
16250,
-15,
-2292,
10786,
-12560,
3234,
-9135,
-3320,
-6516,
4376,
14581,
-16192,
10374,
6255,
15761,
-14099,
-14911,
7863,
10457,
-7837,
6685,
-6669,
-13687,
12301,
-13846,
7897,
-12286,
-1844,
3030,
4468,
1073,
-9545,
5693,
-8457,
7226,
-3278,
-3472,
-2900,
-11477,
12394,
-15671,
13888,
4346,
-14191,
4347,
8315,
8836,
10094,
1420,
-489,
-1926,
4145,
-13835,
1444,
-9532,
-7537,
-6826,
10559,
-2900,
883,
13769,
-3960,
4551,
-10691,
9365,
-4403,
9075,
-5173,
8984,
-11540,
-11526,
4556,
-13324,
14051,
-487,
-11035,
-7329,
-12092,
-15623,
-8805,
11313,
7417,
6380,
-3830,
-661,
15305,
9291,
-2958,
14987,
-9929,
962,
137,
-544,
-4010,
646,
10347,
-9548,
-3644,
-14872,
-6396,
10284,
5967,
12532,
-13704,
-170,
-2283,
-5064,
13555,
-11135,
-3674,
15310,
-14198,
-6005,
-12232,
-12589,
-10998,
-13306,
1053,
8598,
-2703,
10995,
9985,
-16083,
4742,
-12702,
-9316,
13412,
-11643,
-9585,
11490,
6983,
-13749,
10443,
-4949,
-11058,
1303,
13872,
-2060,
1315,
6500,
-16317,
11030,
12761,
-15737,
-13159,
-4124,
15318,
3919,
5572,
-1436,
11077,
10587,
1380,
-13357,
-6708,
3350,
-10393,
7641,
1602,
-11267,
13929,
-9760,
-16107,
6197,
-3245,
-3946,
13212,
14528,
-853,
-15802,
10484,
-14503,
-13431,
6444,
-11562,
-14497,
-14308,
7302,
-15279,
6413,
-9136,
4109,
436,
2481,
-6972,
12867,
-13350,
-6800,
10548,
16188,
-14162,
15502,
13854,
15032,
2070,
14763,
-5956,
-7671,
-14382,
-5480,
-6802,
-3195,
-15266,
-6964,
-9187,
2160,
12127,
-8029,
3008,
744,
-12152,
-16260,
-5708,
-4563,
16189,
14417,
-2158,
14271,
-104,
15436,
14997,
7233,
4848,
11882,
-15371,
-4395,
-13310,
-5418,
-16144,
10339,
-15564,
-2484,
-15276,
5790,
-5637,
1968,
-2464,
-11465,
-14275,
};

DATA rtest[] ={
-6488,
-7199,
-19806,
-30846,
17796,
-6761,
-24733,
-18639,
16494,
29211,
10700,
26177,
-31835,
4570,
-22470,
31012,
-28551,
16938,
16111,
-2282,
12082,
3207,
-19247,
-22078,
-300,
-16186,
-23539,
-11904,
9294,
-4165,
-18685,
-25283,
6300,
-12764,
192,
-1204,
-5275,
-5882,
21179,
14098,
12813,
-1637,
26604,
-24843,
-9372,
-28970,
-29987,
-31881,
10185,
-27168,
-12839,
2060,
31323,
-23881,
-31725,
-86,
10505,
11818,
9412,
19476,
30257,
27021,
-9825,
-12474,
-5168,
10579,
-5259,
8261,
-26778,
-11473,
22949,
5923,
-25882,
-20693,
13524,
-5712,
-5924,
-24903,
29992,
28118,
-24558,
26669,
-3223,
-7665,
-23422,
-6922,
23834,
3746,
22799,
29469,
21747,
-7430,
23128,
-8681,
31103,
19065,
-19590,
-27607,
-7651,
1001,
6712,
-17795,
-21323,
-25255,
24737,
-8760,
12663,
31905,
24687,
-20180,
-11220,
-27168,
-29983,
-23793,
-2210,
-8112,
25034,
21737,
20609,
-24738,
23212,
-30178,
-26183,
-12575,
1992,
-4828,
25313,
14564,
-14182,
-5556,
-20079,
24434,
-453,
-30011,
14359,
-2875,
8214,
-12663,
-6075,
7929,
29423,
-23353,
11580,
-15997,
25983,
10761,
-3159,
23321,
11384,
10832,
-26866,
2667,
12376,
-7001,
366,
23552,
-19260,
-32429,
5553,
-11738,
-13261,
-2656,
16409,
18044,
-709,
-24748,
-1694,
22215,
-23203,
-25344,
11637,
-4459,
-26742,
5657,
-9291,
-914,
25738,
25491,
7248,
7046,
21253,
-4665,
-21645,
27620,
8517,
-25863,
-11322,
-32189,
-17821,
10623,
13330,
-9513,
31454,
-12408,
-32520,
-3732,
-21065,
-21252,
19883,
-23844,
-8775,
28254,
5827,
9099,
26282,
-7913,
-6802,
-4663,
6166,
-15029,
16880,
-27329,
10988,
23751,
-13149,
25772,
26751,
25297,
-10340,
21820,
15753,
2746,
20595,
-13541,
25066,
4804,
-20513,
1103,
-21718,
1810,
-23404,
30223,
-5662,
-25917,
-8280,
-16748,
-27411,
21250,
23213,
31568,
21629,
5283,
-8879,
10532,
19125,
-16950,
3969,
-6475,
22121,
-825,
22870,
-15204,
16111,
-17413,
-30810,
-10509,
6028,
-25168,
21320,
25701,
-28305,
-2453,
12408,
8178,
28144,
-16661,
18558,
19694,
-4695,
22629,
-27698,
-8480,
-28098,
24337,
-32568,
-24155,
-25088,
23733,
-13926,
-9822,
-18141,
4140,
6910,
-24766,
-12745,
24500,
24964,
2079,
27751,
22219,
1487,
9548,
30086,
10355,
-19750,
22721,
-14988,
8057,
20170,
-7864,
-12068,
-31941,
7592,
-5170,
28743,
-27136,
21945,
4595,
11443,
6505,
17315,
-8338,
-7748,
15016,
-24159,
30829,
-13060,
29598,
-7591,
-15142,
32563,
7665,
28907,
-24995,
12250,
-19417,
20068,
2811,
6931,
-17086,
29638,
-9154,
-32142,
28384,
-11250,
-31710,
-24740,
30850,
3003,
-27727,
-9683,
-21835,
-7753,
15846,
8154,
-28514,
-6876,
32456,
24432,
8879,
4748,
23872,
6878,
-350,
7522,
-15018,
3075,
20437,
-21301,
-28030,
24273,
28664,
-18684,
25642,
-32175,
22867,
13816,
4144,
21383,
-13544,
-15735,
26481,
-29013,
-30599,
-23835,
-8153,
-3767,
-19039,
8848,
16465,
-3220,
-4708,
-11202,
-10978,
8724,
-29029,
27587,
-25889,
22719,
-25807,
-3682,
25971,
18566,
26503,
-10050,
20644,
10926,
-18530,
-24746,
25244,
};

DATA r[NX];

