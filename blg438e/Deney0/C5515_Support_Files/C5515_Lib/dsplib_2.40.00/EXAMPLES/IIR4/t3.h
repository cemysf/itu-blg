/* Test for iircas4 : rand */
#define NX 16
#define NBIQ 3
#define FNAME "t3"
#define MAXERROR 20

DATA x[NX] ={
-1478,
-1217,
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
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
13295,
8236,
-4739,
-12204,

-18889,
-2797,
13046,
-12055,

7128,
-7683,
110,
7165,
};

DATA rtest[NX] ={
-1478,
-1046,
-261,
1354,
-222,
-1447,
-1547,
1842,
895,
1323,
-446,
-1542,
1453,
229,
-1777,
724,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

