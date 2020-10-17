/* Test for cfft: rand */
#define NX 8
#define FNAME "t1"
#define MAXERROR 16

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
3204,	2288,	/* 0 */ 
-1915,	-394,	/* 1 */ 
760,	821,	/* 2 */ 
-100,	2078,	/* 3 */ 
2785,	3002,	/* 4 */ 
1865,	1695,	/* 5 */ 
-310,	-2305,	/* 6 */ 
-3428,	-672,	/* 7 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
358,	814,	 /* 0 */ 
-1026,	-424,	 /* 1 */ 
705,	1281,	 /* 2 */ 
1013,	164,	 /* 3 */ 
1252,	137,	 /* 4 */ 
348,	512,	 /* 5 */ 
679,	411,	 /* 6 */ 
-127,	-611,	 /* 7 */ 
};

DATA error;

