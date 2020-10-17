#define NX 16
#define NLAGS 2 // max NLAGS = N 
#define FNAME "t5"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
-7952,
2687,
3671,
-3578,
-3903,
3415,
4650,
7965,
-437,
6599,
-802,
4989,
5388,
-5468,
-1739,
340,
};

DATA rtest[NLAGS] ={ // lag0, lag1,...  
10377, 
598, 
};

