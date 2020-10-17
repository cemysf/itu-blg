/* This is a test for neg: tst2 */
#define NX 4
#define FNAME "t2"
#define MAXERROR 10

DATA x[NX] ={
3276,
-32768,
32767,
9830,
};

DATA rtest[NX] ={
-3277,
32767,
-32768,
-9830,
};

DATA r[NX]; 
