/* Test for iircas5: rand */
#define NX 16
#define NBIQ 3
#define FNAME "t3"
#define MAXERROR 20

DATA x[NX] ={
-1235,
425,
-934,
-1234,
-1986,
1010,
-225,
1768,
-140,
-334,
1418,
103,
-1218,
705,
1384,
-1968,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: a1 a2 b2 b0 b1 ... */
7128,
110,
-13729,
-7683,
7165,
-4739,
8236,
7781,
-12204,
-7756,
13046,
-2797,
-4783,
-12055,
1638,
};

DATA rtest[NX] ={
39,
-50,
91,
33,
-15,
63,
48,
-40,
-66,
67,
-213,
218,
-122,
-47,
71,
69,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

