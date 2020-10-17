/* This is a test for neg32: tst1 */
#define NX 4
#define FNAME "t1"
#define MAXERROR 10

LDATA x[NX] ={
214748364,
429496729,
2147481500,
644245094,
};

LDATA rtest[NX] ={
-214748365,
-429496730,
-2147481501,
-644245095,
};

LDATA r[NX]; 
