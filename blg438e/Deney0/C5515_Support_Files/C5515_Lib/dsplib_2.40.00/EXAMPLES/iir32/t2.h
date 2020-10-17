#define NX 16
#define NBIQ 3
#define NH   5 * NBIQ 
#define FNAME "t2"
#define MAXERROR 10

DATA x[NX] ={
-19745,
6802,
-14930,
-19739,
-31768,
16173,
-3599,
28299,
-2229,
-5332,
22689,
1648,
-19488,
11281,
22158,
-31481,
};

#pragma DATA_SECTION(h,".coeffs")
LDATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
-93717979,
48915125,
-52447574,
755077,
48661168,
53122916,
-52944976,
-83307855,
56229492,
-32351536,
-32648967,
11186728,
-82293866,
-19087792,
89065726,
};

#pragma DATA_SECTION(dbuffer,".dbuffer")
LDATA dbuffer[2*NBIQ+2] ;

LDATA *dp = dbuffer;

DATA r[NX] ;

DATA rtest[NX] ={
0,
-1,
1,
1,
0,
1,
1,
-1,
-2,
0,
-4,
2,
-1,
-2,
1,
1,
};

