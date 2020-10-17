#define NX 8
#define NH 6
#define FNAME "t1"
#define MAXERROR 10

DATA x[NX] ={
26214,
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
-6960,
0,
-12905,
0,
12904,
0,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[NH] ;

DATA rtest[NX] ={
-5568,
0,
-10323,
0,
10323,
0,
0,
0,
};

DATA r[NX];
