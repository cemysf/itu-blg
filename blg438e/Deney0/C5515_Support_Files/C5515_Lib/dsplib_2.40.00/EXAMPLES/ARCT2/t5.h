/* Test for atan2: mtst */
#define NX 5
#define FNAME "t5"
#define MAXERROR 20

DATA x1[NX] ={
6554,
6554,
0,
-6554,
6554,
};

DATA x2[NX] ={
6554,
15820,
32767,
15820,
-15820,
};

DATA rtest[] ={
8192,
4096,
0,
-4096,
28672,
};

DATA r[NX];

