#define NX 8
#define NH 4
#define FNAME "t3"
#define MAXERROR 10

DATA x[NX] ={
-19937,
31299,
-8769,
-23631,
-31801,
9217,
15579,
-31015,
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
-5730,
5664,
3800,
1190,
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[2*NH + 2] ;

DATA r[NX] ;

DATA rtest[NX] ={
3486,
-8919,
4632,
5521,
871,
-11342,
-5812,
15050,
};

