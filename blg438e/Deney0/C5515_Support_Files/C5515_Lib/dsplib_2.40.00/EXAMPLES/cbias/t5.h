#define NA 32
#define NB 32  // NB <= NA 
#define FNAME "t5"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
4578,
5125,
-1911,
-726,
-335,
-4063,
-4219,
376,
2615,
-1174,
-1641,
-2488,
4270,
1464,
-2999,
5538,
1627,
-3130,
2100,
1921,
-4232,
-5533,
-2755,
-4443,
-4990,
4088,
-3704,
-5418,
2710,
423,
-2595,
-1524,
};

DATA b[NB] ={
-5644,
4509,
4240,
-2848,
804,
-3948,
1093,
-1957,
1837,
4212,
783,
5566,
3380,
-4025,
3858,
-3570,
1610,
1957,
3152,
-1393,
-677,
-197,
1252,
-3754,
-5770,
3362,
157,
-3323,
-4595,
-3970,
-1072,
-1069,
};

DATA rtest[NA+NB-1] ={
-5,
-10,
-21,
-37,
-29,
0,
34,
14,
-19,
24,
19,
-19,
1,
62,
45,
-31,
-34,
0,
11,
-61,
-1,
83,
12,
17,
50,
25,
-25,
4,
33,
66,
81,
30,
7,
4,
38,
24,
-50,
34,
57,
-24,
-54,
-56,
39,
-115,
-64,
61,
-89,
-17,
64,
-30,
-34,
-17,
9,
-27,
17,
45,
-59,
10,
48,
-19,
-20,
7,
8,
};

