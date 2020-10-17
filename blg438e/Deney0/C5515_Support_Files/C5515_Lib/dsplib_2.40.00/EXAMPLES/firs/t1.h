#define NX 8
#define NH 4
#define FNAME "t1"
#define MAXERROR 10

DATA x[NX] ={
32767,
0,
0,
0,
0,
0,
0,
0,
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
3823,
-6134,
5802,
-625,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[2*NH + 2] ;

DATA r[NX] ;

DATA rtest[NX] ={
3824,
-6133,
5802,
-625,
-625,
5802,
-6133,
3824,
};

