#define NX 8
#define NLAGS 8 // max NLAGS = N 
#define FNAME "t1"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
10429,
-6230,
2475,
-325,
9066,
6072,
-1009,
-11157,
};

DATA rtest[NLAGS] ={// lag0, lag1,...  
1520,
-104,
-145,
-889,
441,
427,
900,
-3551,
};

