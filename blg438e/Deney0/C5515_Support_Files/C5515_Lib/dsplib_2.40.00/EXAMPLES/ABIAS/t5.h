#define NX 6
#define NLAGS 6 // max NLAGS = N 
#define FNAME "t5"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
2448,
-10174,
-12358,
-1108,
9895,
11617,
};

DATA rtest[NLAGS] ={ // lag0, lag1,... 
2524,
1111,
-784,
-1256,
-478,
145,
};

