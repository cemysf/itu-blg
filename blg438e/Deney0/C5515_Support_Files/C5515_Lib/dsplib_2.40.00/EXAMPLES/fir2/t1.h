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
17562,
-10491,
4168,
-547,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[NH+2] ;

DATA rtest[NX] ={
17562,
-10490,
4169,
-547,
0,
0,
0,
0,
};

DATA r[NX];
