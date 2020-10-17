/* Test for iircas5: rand */
#define NX 16
#define NBIQ 4
#define FNAME "t4"
#define MAXERROR 20

DATA x[NX] ={
1474,
1448,
383,
-15,
1637,
1317,
593,
1302,
656,
-648,
-862,
-651,
139,
930,
-782,
1386,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: a1 a2 b2 b0 b1 ... */
2676,
-2168,
9331,
17963,
18864,
-5096,
7650,
-14293,
888,
-8988,
7972,
4770,
-19199,
14947,
-9739,
1831,
11592,
15488,
-12860,
14774,
};

DATA rtest[NX] ={
-4,
39,
80,
-157,
-409,
30,
670,
290,
-470,
-189,
403,
253,
111,
396,
308,
-329,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

