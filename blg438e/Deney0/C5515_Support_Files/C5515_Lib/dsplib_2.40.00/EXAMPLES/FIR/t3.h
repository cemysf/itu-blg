#define NX 8
#define NH 4
#define FNAME "t3"
#define MAXERROR 10

DATA x[NX] ={
-10408,
2233,
14884,
-12499,
22183,
4461,
-8493,
13286,
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
3654,
-4326,
15268,
9519,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[NH+2] ;

DATA rtest[NX] ={
-1161,
1623,
-3484,
-5342,
11708,
-3930,
5170,
11126,
};

DATA r[NX];
