#define NX 8
#define NH 4
#define FNAME "t3"
#define MAXERROR 10  // max absolute value 

DATA x[NX] ={
-10408,
2233,
14884,
-12499,
22183,
4461,
-8493,
13286,
};

DATA h[NH] ={
3654,
-4326,
15268,
9519,
};

DATA rtest[NX+NH-1] ={
-1161,
1622,
-3485,
-5342,
11708,
-3931,
5169,
11126,
};

DATA x_np[NX+NH-1] = {
0,
0,
0,
-10408,
2233,
14884,
-12499,
22183,
4461,
-8493,
13286,
};

