#define NX 8
#define NH 4
#define FNAME "t1"
#define MAXERROR 10  // max absolute value 

DATA x[NX] ={
32767,
0,
0,
0,
0,
0,
0,
0,
};

DATA h[NH] ={
17562,
-10491,
4168,
-547,
};

DATA rtest[NX+NH-1] ={
17562,
-10491,
4168,
-547,
0,
0,
0,
0,
};

DATA x_np[NX+NH-1] = {
0,
0,
0,
32767,
0,
0,
0,
0,
0,
0,
0,
};

