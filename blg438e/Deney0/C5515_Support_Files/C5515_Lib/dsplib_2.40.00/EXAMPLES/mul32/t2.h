/* This is a test for mul32: tst2 */
#define NX 5
#define FNAME "t2"
#define MAXERROR 100

LDATA x[NX] ={
2145336164,
-2147483648,
2145336164,
-2147483648,
264140488,
};

LDATA y[NX] ={
2145336164,
-2147483648,
-2147483648,
2145336164,
429496729,
};

LDATA rtest[NX] ={
2143190828,
2145336164,
-2145336165,
-2145336165,
52828097,
};

LDATA r[NX]; 
