/* This is a test for neg32: tst2 */
#define NX 4
#define FNAME "t2"
#define MAXERROR 10

LDATA x[NX] ={
214748364,
-2147483648,
2147483433,
644245094,
};

LDATA rtest[NX] ={
-214748365,
2147483647,
-2147483434,
-644245095,
};

LDATA r[NX]; 
