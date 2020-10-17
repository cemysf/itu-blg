/* Test for iircas51: rand */
#define NX 16
#define NBIQ 2
#define FNAME "t2"
#define MAXERROR 20

DATA x[NX] ={
1841,
-1101,
437,
-58,
1601,
1072,
-179,
-1971,
1315,
-227,
472,
1194,
1726,
974,
-1325,
-386,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: b0 b1 b2 a1 a2 ... */
-17385,
12314,
-14200,
17123,
-3529,
-5786,
-19274,
-11688,
16393,
15478,
};

DATA rtest[NX] ={
172,
173,
-432,
575,
-36,
142,
122,
-175,
80,
368,
-606,
436,
517,
-77,
48,
-5,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

