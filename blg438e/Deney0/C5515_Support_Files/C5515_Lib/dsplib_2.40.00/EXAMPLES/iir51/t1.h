/* Test for iircas51: tst1 */
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
DATA h[5*NBIQ] ={ /* C54x: b0 b1 b2 a1 a2 ... */
32735,
16384,
19660,
3276,
6553,
32735,
22937,
26214,
9830,
13107,
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

