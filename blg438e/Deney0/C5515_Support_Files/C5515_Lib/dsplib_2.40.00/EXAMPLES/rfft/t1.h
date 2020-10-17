/* Test for rfft: rand */
#define NX 8
#define FNAME "t1"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
29496,	/* 0 */ 
-17619,	/* 1 */ 
7001,	/* 2 */ 
-919,	/* 3 */ 
25641,	/* 4 */ 
17175,	/* 5 */ 
-2853,	/* 6 */ 
-31553,	/* 7 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
3296, 
11525, 
-5302, 
-865, 
6373, 
-4004, 
6264, 
1599, 
};

DATA error;

