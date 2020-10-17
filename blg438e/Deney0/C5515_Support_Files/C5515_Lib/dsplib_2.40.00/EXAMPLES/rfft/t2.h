/* Test for rfft: rand */
#define NX 16
#define FNAME "t2"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
21061,	/* 0 */ 
-3624,	/* 1 */ 
7564,	/* 2 */ 
19130,	/* 3 */ 
27641,	/* 4 */ 
15609,	/* 5 */ 
-21215,	/* 6 */ 
-6180,	/* 7 */ 
28536,	/* 8 */ 
27319,	/* 9 */ 
-5880,	/* 10 */ 
25795,	/* 11 */ 
-28972,	/* 12 */ 
-9642,	/* 13 */ 
20521,	/* 14 */ 
-32119,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
5347, 
810, 
-2077, 
-3242, 
288, 
-4611, 
-2424, 
5522, 
2954, 
-1440, 
-3389, 
-4056, 
6077, 
-4313, 
6019, 
1334, 
};

DATA error;

