/* Test for sine: rand */
#define NX 128
#define FNAME "t6"
#define MAXERROR 10

DATA x[NX] ={
19281,
-28890,
6741,
-29474,
-5546,
-12780,
24534,
-31785,
17560,
30857,
32118,
18930,
-4021,
-111,
-18746,
9403,
-11795,
30153,
14852,
-5771,
16027,
-15208,
-3938,
28401,
12014,
-18838,
22232,
8440,
-24002,
-19194,
7025,
8512,
-8489,
4924,
-3184,
-29892,
-30987,
-12276,
-31926,
-7605,
12000,
-26684,
-30453,
7365,
7113,
-31736,
-31697,
-20312,
5696,
-28995,
-8680,
8614,
14262,
12626,
-27258,
-2992,
-3813,
-9618,
-22702,
11511,
13055,
14910,
-1417,
3594,
-24836,
-3228,
14148,
25745,
-14870,
-16072,
23960,
-17541,
19980,
26764,
-17571,
-17085,
-29508,
-27632,
9228,
-20259,
22535,
-21372,
-21575,
32394,
-3946,
-10483,
-12176,
-8843,
-6997,
5998,
-24921,
-30270,
-2714,
24239,
28458,
-15438,
-22263,
24435,
-17179,
9557,
30597,
10808,
24273,
-32118,
-23789,
20889,
-4577,
25580,
15394,
12276,
-10086,
-21887,
-22570,
-20243,
-5083,
23329,
-639,
20705,
-2571,
-2795,
-3232,
-5753,
26319,
-32403,
-13278,
-29547,
12660,
9837,
};

DATA rtest[NX] ={
31511,
-11907,
19735,
-10179,
-16614,
-30831,
23262,
-3086,
32559,
5969,
2040,
31796,
-12320,
-348,
-31932,
25700,
-29647,
8129,
32415,
-17218,
32748,
-32560,
-12078,
13319,
29934,
-31866,
27750,
23714,
-24412,
-31587,
20439,
23871,
-23820,
14903,
-9847,
-8924,
-5570,
-30260,
-2646,
-21829,
29916,
-18050,
-7217,
21264,
20654,
-3240,
-3362,
-30473,
17019,
-11599,
-24227,
24090,
32092,
30664,
-16517,
-9270,
-11712,
-26112,
-26940,
29256,
31113,
32441,
-4437,
11069,
-22588,
-9979,
32018,
20433,
-32424,
-32754,
24497,
-32567,
30839,
17835,
-32557,
-32695,
-10078,
-15494,
25354,
-30534,
27231,
-29094,
-28794,
1174,
-12103,
-27662,
-30137,
-24569,
-20369,
17822,
-22394,
-7776,
-8429,
23905,
13157,
-32634,
-27701,
23480,
-32674,
25996,
6768,
28197,
23833,
-2043,
-24852,
29757,
-13921,
20836,
32620,
30259,
-26973,
-28313,
-27173,
-30551,
-15342,
25768,
-2007,
29996,
-7996,
-8676,
-9991,
-17171,
18991,
-1150,
-31326,
-9962,
30701,
26522,
};

DATA r[NX];
