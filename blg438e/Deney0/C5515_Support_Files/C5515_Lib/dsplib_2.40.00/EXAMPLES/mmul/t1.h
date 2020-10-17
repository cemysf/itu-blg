/* Test for mmul: step */
#define row1 3
#define col1 3
#define row2 3
#define col2 3
#define FNAME "t1"
#define MAXERROR 10

DATA x1[row1*col1] ={
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

DATA x2[row2*col2] ={
15,
-1234,
6521,
435,
8888,
-16343,
0,
32012,
1010,
};

DATA rtest[] ={
14,
-1697,
-567,
220,
-26525,
-5957,
15,
-3470,
6301,
};

DATA r[row1*col2];

