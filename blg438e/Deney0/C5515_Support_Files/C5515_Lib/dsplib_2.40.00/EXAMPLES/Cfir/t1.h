#define NX 8
#define NH 4
#define FNAME "t1"
#define MAXERROR 15

DATA x[2*NX] ={
32767, 32767, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[2*NH] ={ /* b0 b1 b2 ... b(NH-1) */
-947, -2064, 
-14598, -4517, 
-7465, -10320, 
-9760, -18635, 
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[2*NH + 2] ;

DATA rtest[2*NX] ={
1117, -3011, 
-10081, -19114, 
2855, -17784, 
8876, -28394, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
};

