#define NX 8
#define NLAGS 8 // max NLAGS = N 
#define FNAME "t1"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
-10433,
-9770,
3262,
-7163,
7967,
-7556,
-7628,
11453,
};

DATA rtest[NLAGS] ={ // lag0, lag1,...  
17583, 
-3062, 
-954, 
3605, 
-3547, 
5820, 
-986, 
-3646, 
};

