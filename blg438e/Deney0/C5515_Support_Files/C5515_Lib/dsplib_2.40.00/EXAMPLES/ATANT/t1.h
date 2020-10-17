/* Test for maxval: tst1 */
#define NX 8
#define FNAME "t1"
#define MAXERROR 40

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
8027,
15192,
21086,
25735,
-8028,
-15193,
-21087,
};

DATA r[NX];
