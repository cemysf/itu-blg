#define NX 16
#define NLAGS 1 // max NLAGS = N 
#define FNAME "t4"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
99,
-578,
678,
7247,
-2593,
-1609,
-3151,
-1449,
-3508,
-1735,
49,
3636,
-3176,
-6355,
-930,
-545,
};

DATA rtest[NLAGS] ={ // lag0, lag1,...  
4725, 
};

