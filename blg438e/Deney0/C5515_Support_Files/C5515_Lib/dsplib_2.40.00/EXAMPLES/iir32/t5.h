#define NX 16
#define NBIQ 2
#define NH   5 * NBIQ 
#define FNAME "t5"
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
0,
0,
0,
0,
0,
0,
0,
0,
};

#pragma DATA_SECTION(h,".coeffs")
LDATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
-127987048,
-108450012,
-113233677,
-131271832,
-95620119,
-131846082,
-88374504,
-133354402,
-132393233,
-103923017,
};

#pragma DATA_SECTION(dbuffer,".dbuffer")
LDATA dbuffer[2*NBIQ+2] ;

LDATA *dp = dbuffer;

DATA r[NX] ;

DATA rtest[NX] ={
107,
183,
325,
233,
179,
42,
23,
5,
2,
0,
0,
0,
0,
0,
0,
0,
};

