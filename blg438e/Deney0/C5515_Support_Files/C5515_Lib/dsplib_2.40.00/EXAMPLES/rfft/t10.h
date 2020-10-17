/* Test for rfft: sine */
#define NX 16
#define FNAME "t10"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

DATA x[NX] ={
0,	/* 0 */ 
21992,	/* 1 */ 
26367,	/* 2 */ 
13633,	/* 3 */ 
0,	/* 4 */ 
-1813,	/* 5 */ 
4523,	/* 6 */ 
6547,	/* 7 */ 
0,	/* 8 */ 
-6548,	/* 9 */ 
-4524,	/* 10 */ 
1812,	/* 11 */ 
0,	/* 12 */ 
-13634,	/* 13 */ 
-26368,	/* 14 */ 
-21993,	/* 15 */ 
};

#pragma DATA_SECTION (rtest,".test")

/* format: y(0)Re,y(N/2)Re,y(1)Re,y(1)Im,y(2)Re,y(2)Im,..y(N/2-1)Re,y(N/2-1)Im */

DATA rtest[NX] ={
-1, 
-1, 
0, 
-5461, 
0, 
-5461, 
0, 
-5461, 
0, 
-1, 
-1, 
-1, 
-1, 
-1, 
-1, 
0, 
};

DATA error;

