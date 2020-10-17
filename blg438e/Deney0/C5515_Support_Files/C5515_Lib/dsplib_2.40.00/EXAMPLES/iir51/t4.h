/* Test for iircas51: rand */
#define NX 16
#define NBIQ 4
#define FNAME "t4"
#define MAXERROR 20

DATA x[NX] ={
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
-650,
139,
929,
-781,
1385,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: b0 b1 b2 a1 a2 ... */
17963,
18864,
9331,
2676,
-2168,
888,
-8988,
-14293,
-5096,
7650,
14947,
-9739,
-19199,
7972,
4770,
-12860,
14774,
15488,
1831,
11592,
};

DATA rtest[NX] ={
-4,
39,
79,
-156,
-408,
30,
669,
290,
-469,
-189,
402,
253,
111,
396,
307,
-329,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

