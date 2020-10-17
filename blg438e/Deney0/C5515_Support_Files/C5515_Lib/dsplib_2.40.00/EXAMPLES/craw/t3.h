#define NA 128
#define NB 128  // NB <= NA 
#define FNAME "t3"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
-2122,
-1697,
620,
752,
-751,
435,
-282,
-2643,
-2739,
-1086,
-2822,
-673,
1060,
-2359,
-2692,
651,
628,
-2806,
-2802,
-1796,
503,
-2563,
-768,
761,
1260,
1116,
-2410,
-265,
-337,
-851,
-2007,
1017,
1153,
1317,
-126,
317,
-2196,
-286,
1250,
2275,
-1315,
-1421,
2117,
-1551,
1766,
2365,
-1554,
-1511,
-2609,
-2443,
815,
-1791,
1991,
-1889,
-1907,
2863,
-349,
-927,
-1077,
-782,
-619,
530,
-2203,
-2676,
-240,
2142,
2515,
-1365,
-1968,
2159,
-1519,
844,
2704,
955,
2145,
-2839,
-2103,
1846,
-405,
2260,
1360,
1085,
-892,
-1935,
-1995,
-1790,
-450,
2062,
-57,
1830,
-228,
-248,
-286,
-509,
2326,
-2864,
-1174,
-2612,
1119,
869,
2797,
305,
-579,
-1745,
725,
1351,
-719,
-2840,
-465,
1469,
1702,
2432,
1996,
-767,
699,
1339,
-1774,
2344,
400,
763,
-1539,
282,
2499,
-955,
900,
-627,
737,
1153,
};

DATA b[NB] ={
-596,
-501,
899,
1955,
-744,
-433,
548,
380,
1254,
65,
1601,
-62,
-1820,
1162,
2796,
1776,
1179,
-88,
-2233,
954,
-780,
-2086,
386,
1871,
1007,
2893,
2674,
-2556,
-810,
281,
-1380,
563,
-2611,
411,
1163,
2677,
1451,
1390,
-395,
777,
1755,
-2411,
2580,
2409,
590,
-1428,
2163,
77,
1347,
-451,
2672,
-2479,
309,
-1205,
2073,
-952,
1043,
-2587,
-831,
-10,
-380,
361,
675,
-2240,
2306,
1474,
1686,
1824,
984,
-1733,
-1315,
731,
213,
-2552,
-2381,
-1325,
-527,
-151,
2369,
557,
-991,
-127,
562,
-1962,
1908,
2642,
553,
-2730,
1807,
637,
1167,
-2363,
-436,
-721,
-1934,
1929,
1961,
-281,
2644,
-2044,
2142,
1560,
-324,
698,
2616,
811,
-1464,
-854,
-1809,
-55,
-526,
-212,
642,
-2485,
-1076,
627,
-1883,
701,
-1472,
506,
35,
-205,
239,
2562,
-917,
-569,
-1114,
-513,
};

DATA rtest[NA+NB-1] ={
33,
99,
85,
56,
-143,
-160,
31,
136,
34,
257,
229,
59,
-121,
61,
54,
128,
115,
10,
52,
468,
502,
351,
122,
-167,
231,
-82,
8,
429,
782,
317,
-114,
-31,
160,
-299,
-252,
419,
-236,
-99,
19,
-401,
-422,
-71,
-271,
21,
-350,
-659,
-92,
344,
-229,
-144,
-241,
-56,
-665,
-765,
1664,
-83,
-1066,
285,
-129,
-404,
39,
342,
1097,
-358,
373,
1051,
-158,
-53,
412,
-508,
441,
638,
-466,
-156,
268,
-504,
1017,
85,
-727,
-581,
-1238,
678,
192,
172,
1022,
-1629,
-635,
891,
-754,
-295,
-1019,
-1401,
-1147,
208,
6,
49,
174,
-77,
-451,
-1256,
6,
-756,
-1362,
408,
1792,
-708,
-1,
-495,
123,
-1650,
-189,
-881,
-661,
-1008,
-517,
418,
2184,
308,
-160,
-1177,
-1226,
-277,
-689,
366,
-1523,
-765,
-262,
-219,
-475,
722,
-1264,
-1422,
26,
-935,
-914,
206,
701,
885,
-1811,
-596,
229,
-779,
133,
390,
-388,
-1165,
456,
-694,
181,
836,
-139,
-430,
-534,
738,
382,
-1164,
959,
560,
176,
200,
273,
-98,
-383,
-30,
-121,
-427,
-377,
-46,
-693,
-398,
-349,
808,
-346,
875,
-448,
-572,
-967,
653,
-30,
114,
-959,
-126,
439,
769,
-33,
817,
-930,
-1497,
-620,
-33,
1708,
513,
890,
289,
-73,
-116,
75,
-464,
-132,
-162,
-523,
708,
1509,
519,
89,
-25,
436,
74,
-666,
-727,
-376,
560,
461,
1131,
77,
-74,
99,
-239,
352,
-24,
-238,
-510,
348,
626,
130,
445,
-129,
-336,
186,
580,
393,
27,
-128,
-166,
339,
399,
211,
-260,
131,
218,
-3,
155,
-3,
182,
-131,
-50,
219,
49,
8,
-75,
4,
82,
32,
-31,
-21,
};
