#define NX 16
#define NLAGS 15 // max NLAGS = N 
#define FNAME "t8"
#define MAXERROR 10 // max absolute error allowed 

DATA x[NX] ={
-6046,
7222,
3307,
5696,
-4764,
-736,
-6864,
5752,
1016,
-2961,
-2050,
6025,
-2095,
-6985,
-4918,
-7382,
};

DATA rtest[NLAGS] ={ // lag0, lag1,...  
12747, 
311, 
299, 
-3587, 
1946, 
-1084, 
2012, 
-1951, 
196, 
3010, 
1161, 
-2060, 
-2933, 
-540, 
-719, 
};

