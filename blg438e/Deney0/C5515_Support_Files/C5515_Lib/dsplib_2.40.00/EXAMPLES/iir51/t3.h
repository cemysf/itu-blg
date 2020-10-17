/* Test for iircas51: rand */
#define NX 16
#define NBIQ 3
#define FNAME "t3"
#define MAXERROR 20

DATA x[NX] ={
-1233,
424,
-933,
-1233,
-1984,
1009,
-225,
1766,
-140,
-333,
1416,
102,
-1217,
704,
1383,
-1966,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: b0 b1 b2 a1 a2 ... */
-7683,
7165,
-13729,
7128,
110,
-12204,
-7756,
7781,
-4739,
8236,
-12055,
1638,
-4783,
13046,
-2797,
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
-121,
-47,
71,
69,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

