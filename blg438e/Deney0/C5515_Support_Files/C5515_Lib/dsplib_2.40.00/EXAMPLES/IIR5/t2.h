/* Test for iircas5: rand */
#define NX 16
#define NBIQ 2
#define FNAME "t2"
#define MAXERROR 20

DATA x[NX] ={
1843,
-1102,
437,
-58,
1602,
1073,
-179,
-1973,
1316,
-227,
472,
1195,
1727,
975,
-1327,
-387,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: a1 a2 b2 b0 b1 ... */
17123,
-3529,
-14200,
-17385,
12314,
16393,
15478,
-11688,
-5786,
-19274,
};

DATA rtest[NX] ={
172,
173,
-433,
576,
-36,
142,
122,
-175,
80,
368,
-607,
436,
518,
-77,
48,
-5,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

