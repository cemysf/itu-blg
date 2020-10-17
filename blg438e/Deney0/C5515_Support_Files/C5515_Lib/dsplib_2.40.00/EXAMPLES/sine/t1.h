/* Test for sine: tst1 */
#define NX 8
#define FNAME "t1"
#define MAXERROR 10

DATA x[NX] ={
0,
8192,
16384,
24576,
32767,
-8192,
-16384,
-24576,
};

DATA rtest[NX] ={
0,
23170,
32767,
23170,
0,
-23171,
-32768,
-23171,
};

DATA r[NX];
