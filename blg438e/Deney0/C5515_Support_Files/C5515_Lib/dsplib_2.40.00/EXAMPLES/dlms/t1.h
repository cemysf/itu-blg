/* Test for dlms: mtst */
#define NX 3
#define NH 3
#define STEP 32767
#define FNAME "t1"
#define MAXERROR 20

DATA x[NX] ={
32764,
0,
0,
};

DATA des[NX] ={
3276,
6553,
0,
};

DATA htest[NH] ={ /* C54x: hn-1 ... h0 (backward order) */
0,
6553,
3276,
};

DATA rtest[NX] ={
0,
0,
0,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[NH+2];

#pragma DATA_SECTION (h,".coeffs")
DATA h[NH];

DATA r[NX];

DATA error;

