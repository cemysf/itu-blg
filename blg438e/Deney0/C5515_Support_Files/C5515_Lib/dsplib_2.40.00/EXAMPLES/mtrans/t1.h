/* Test for mtrans: step */
#define row 3
#define col 3
#define FNAME "t1"
#define MAXERROR 0

DATA x[row*col] ={
20,
1020,
-2020,
15020,
16020,
-31020,
32020,
0,
-2318,
};

DATA rtest[] ={
20,
15020,
32020,
1020,
16020,
0,
-2020,
-31020,
-2318,
};

DATA r[row*col];

