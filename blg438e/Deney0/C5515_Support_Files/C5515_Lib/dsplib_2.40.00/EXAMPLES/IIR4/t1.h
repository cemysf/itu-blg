/* Test for iircas4 : tst1 */
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
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2... */
3276,
16384,
6553,
19660,

9830,
22937,
13107,
26214,
};

DATA rtest[NX] ={
3277,
9175,
17695,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];

