#define NX 16
#define NBIQ 2
#define NH   5 * NBIQ 
#define FNAME "t1"
#define MAXERROR 10

DATA x[NX] ={
29499,
-17621,
7002,
-919,
25644,
17176,
-2853,
-31556,
21063,
-3624,
7564,
19132,
27643,
15611,
-21217,
-6180,
};

#pragma DATA_SECTION(h,".coeffs")
LDATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
-96934394,
84064907,
-118677531,
-24086634,
116895390,
-79788275,
-131570474,
-39495371,
105669385,
111911821,
};

#pragma DATA_SECTION(dbuffer,".dbuffer")
LDATA dbuffer[2*NBIQ+2] ;

LDATA *dp = dbuffer;

DATA r[NX] ;

DATA rtest[NX] ={
29,
57,
-33,
48,
49,
57,
57,
-8,
-1,
62,
-45,
14,
113,
90,
56,
3,
};

