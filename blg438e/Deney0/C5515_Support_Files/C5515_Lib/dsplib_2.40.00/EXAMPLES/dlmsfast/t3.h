/* Test for dlms: rand */
#define NX 20
#define NH 12
#define STEP 327
#define FNAME "t3"
#define MAXERROR 20

DATA x[NX] ={
29499,
-17620,
7001,
-919,
25643,
17176,
-2853,
-31556,
21063,
-3624,
7564,
19132,
27643,
15610,
-21217,
-6180,
28538,
27321,
-5881,
25797,
};

DATA des[NX] ={
-28974,
-9643,
20523,
-32122,
-23666,
-19480,
-19745,
6802,
-14930,
-19739,
-31767,
16173,
-3599,
28299,
-2229,
-5332,
22689,
1648,
-19488,
11281,
};

DATA htest[NH] ={ /* C54x: hn-1 ... h0 (backward order) */
484,
-599,
60,
188,
46,
-767,
-106,
-255,
346,
-38,
-351,
-139,
};

DATA rtest[NX] ={
0,
0,
-56,
-13,
-84,
-362,
93,
431,
-51,
-554,
31,
-331,
-683,
-278,
-415,
361,
-1214,
-910,
-839,
588,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NH+3];

#pragma DATA_SECTION (h,".coeffs")
DATA h[2*NH];

DATA r[NX];

DATA error;

