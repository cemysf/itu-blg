#define NX 16
#define NLAGS 14 // max NLAGS = N 
#define FNAME "t7"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
-4557,
3337,
361,
7092,
3495,
-4456,
-826,
-5371,
7681,
-2364,
-7389,
4183,
6468,
-3504,
-4077,
7089,
};

DATA rtest[NLAGS] ={ // lag0, lag1,...  
12256, 
-2356, 
-4920, 
978, 
2123, 
-400, 
-3272, 
1889, 
-378, 
1025, 
-633, 
-88, 
233, 
150, 
};

