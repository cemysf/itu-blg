#define NX 16
#define NLAGS 8 // max NLAGS = N 
#define FNAME "t6"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
3573,
1133,
-643,
-897,
-6755,
-926,
-2191,
-3236,
5764,
4251,
7368,
949,
-7959,
1575,
5180,
7816,
};

DATA rtest[NLAGS] ={ // lag0, lag1,...  
10293, 
2993, 
-1413, 
-3021, 
-2336, 
2074, 
176, 
349, 
};

