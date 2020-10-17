#define NX 8
#define NH 6
#define FNAME "t3"
#define MAXERROR 10

DATA x[NX] ={
23599,
-14097,
5601,
-735,
20515,
13741,
-2283,
-25245,
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
-5012,
2994,
-10483,
5707,
2730,
-8180,
-5388,
-339,
};

DATA r[NX];
