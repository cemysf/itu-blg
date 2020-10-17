/* Test for logn: rand */
#define NX 200
#define FNAME "t5"
#define MAXERROR 40

DATA x[NX] ={
18234,
18220,
16822,
25732,
18983,
24690,
15428,
13228,
18049,
16304,
23600,
16682,
19067,
18241,
3175,
25257,
12365,
16004,
11479,
17947,
4758,
8073,
16714,
25502,
12686,
17273,
21573,
8157,
10914,
12572,
7609,
18140,
11570,
14510,
23434,
13371,
21510,
21849,
13402,
24507,
11489,
7328,
11209,
1541,
14784,
14147,
15383,
19180,
2921,
23699,
4367,
19574,
10641,
19445,
8470,
3005,
10177,
21957,
12983,
15273,
7697,
15220,
13592,
29592,
17073,
15328,
22368,
19106,
14907,
17071,
14225,
17698,
14026,
10573,
7193,
20642,
17875,
8081,
12090,
23971,
20748,
24477,
5572,
11222,
18854,
8590,
7982,
22693,
1470,
22475,
31562,
18221,
24795,
15108,
19237,
7651,
21413,
31604,
14701,
17375,
24318,
19709,
18920,
23287,
15511,
16604,
14054,
24750,
25841,
12843,
12943,
13791,
30861,
14014,
6872,
23701,
13305,
6544,
23194,
5442,
23293,
17224,
17081,
21924,
12384,
21463,
11095,
2880,
13411,
21453,
16179,
14966,
8219,
13452,
24542,
27537,
23145,
19548,
13250,
13742,
21323,
10477,
5720,
24119,
17284,
3829,
18631,
14072,
18150,
27515,
12547,
9158,
11879,
23750,
13420,
28727,
21281,
19532,
26617,
6892,
20855,
18109,
25301,
14135,
18453,
28377,
20793,
12827,
2202,
21163,
11142,
6650,
14044,
18319,
14118,
5077,
16719,
20617,
6077,
9372,
8634,
10413,
21693,
30589,
21565,
30673,
18823,
17052,
15463,
16380,
8256,
17371,
12799,
26485,
13201,
19257,
13542,
19394,
8121,
15779,
};

long rtest[] ={
-19207,
-19232,
-21848,
-7921,
-17888,
-9276,
-24682,
-29724,
-19541,
-22873,
-10755,
-22122,
-17744,
-19195,
-76489,
-8531,
-31935,
-23483,
-34370,
-19727,
-63230,
-45905,
-22059,
-8215,
-31094,
-20982,
-13697,
-45566,
-36024,
-31390,
-47845,
-19377,
-34112,
-26692,
-10986,
-29372,
-13794,
-13281,
-29295,
-9519,
-34342,
-49079,
-35152,
-100169,
-26080,
-27523,
-24779,
-17551,
-79220,
-10618,
-66043,
-16884,
-36856,
-17100,
-44331,
-78288,
-38317,
-13119,
-30337,
-25015,
-47467,
-25128,
-28834,
-3340,
-21364,
-24896,
-12512,
-17676,
-25809,
-21366,
-27343,
-20185,
-27805,
-37066,
-49689,
-15143,
-19860,
-45875,
-32671,
-10244,
-14975,
-9560,
-58055,
-35113,
-18112,
-43872,
-46278,
-12040,
-101725,
-12354,
-1229,
-19231,
-9136,
-25370,
-17453,
-47667,
-13941,
-1185,
-26264,
-20788,
-9773,
-16659,
-17997,
-11193,
-24506,
-22276,
-27740,
-9196,
-7781,
-30693,
-30439,
-28358,
-1965,
-27834,
-51183,
-10615,
-29534,
-52788,
-11323,
-58828,
-11183,
-21075,
-21349,
-13169,
-31885,
-13864,
-35486,
-79679,
-29274,
-13880,
-23125,
-25679,
-45317,
-29175,
-9472,
-5699,
-11392,
-16927,
-29670,
-28475,
-14080,
-37366,
-57197,
-10042,
-20962,
-70344,
-18501,
-27699,
-19359,
-5725,
-31457,
-41773,
-33250,
-10547,
-29251,
-4313,
-14144,
-16954,
-6813,
-51089,
-14807,
-19433,
-8474,
-27552,
-18816,
-4715,
-14903,
-30733,
-88482,
-14326,
-35346,
-52260,
-27762,
-19055,
-27591,
-61103,
-22049,
-15183,
-55213,
-41016,
-43705,
-37565,
-13516,
-2255,
-13709,
-2165,
-18166,
-21404,
-24609,
-22722,
-45172,
-20796,
-30805,
-6975,
-29791,
-17419,
-28956,
-17186,
-45712,
-23947,
};

long r[NX];
