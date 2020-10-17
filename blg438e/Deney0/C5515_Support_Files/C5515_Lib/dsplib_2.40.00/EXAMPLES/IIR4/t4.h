/* Test for iircas4 : rand */
#define NX 16
#define NBIQ 4
#define FNAME "t4"
#define MAXERROR 20

DATA x[NX] ={
-808,
170,
-1429,
809,
-498,
1473,
1447,
382,
-15,
1635,
1316,
592,
1301,
655,
-647,
-861,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
-6245,
1831,
13310,
11592,

1340,
-2168,
2676,
17963,

8930,
7650,
-5096,
888,

-7500,
4770,
7972,
14947,
};

DATA rtest[NX] ={
-807,
-213,
-2125,
136,
-1587,
1821,
1584,
2634,
1700,
2578,
2252,
2767,
3114,
2390,
1147,
-277,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

