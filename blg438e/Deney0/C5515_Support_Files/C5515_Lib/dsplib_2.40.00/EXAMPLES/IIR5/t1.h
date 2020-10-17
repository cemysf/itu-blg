/* Test for iircas5: tst1 */
#define NX 3
#define NBIQ 2
#define FNAME "t1"
#define MAXERROR 20

DATA x[NX] ={
3276,
6553,
9830,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[5*NBIQ] ={ /* C54x: a1 a2 b2 b0 b1 ... */
3276,
6553,
19660,
32735,
16384,
9830,
13107,
26214,
32735,
22937,
};

DATA rtest[NX] ={
3270,
9160,
17672,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

