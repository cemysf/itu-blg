/* Test for iircas4 : rand */
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
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2 ... */
17123,
-17385,
-3529,
12314,

16393,
-5786,
15478,
-19274,
};

DATA rtest[NX] ={
1842,
-4287,
4228,
-1779,
1006,
-651,
-643,
-785,
4021,
-4734,
2475,
1263,
-1244,
-458,
-900,
2107,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

