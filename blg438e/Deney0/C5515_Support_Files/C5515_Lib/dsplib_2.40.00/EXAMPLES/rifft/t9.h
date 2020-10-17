/* Test for rfft: cosi */
#define NX 8
#define FNAME "t9"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
32764,	/* 0 */ 
0,	/* 1 */ 
-10922,	/* 2 */ 
0,	/* 3 */ 
-10922,	/* 4 */ 
-1,	/* 5 */ 
-10922,	/* 6 */ 
-1,	/* 7 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(1)Re,y(2)Re,y(3)Re, ... y(N-1)Re */

DATA rtest[NX] ={
-2048,	2047,	 /* 0 */ 
3412,	2047,	 /* 1 */ 
3412,	2047,	 /* 2 */ 
3412,	2047,	 /* 3 */ 
};

DATA error;

