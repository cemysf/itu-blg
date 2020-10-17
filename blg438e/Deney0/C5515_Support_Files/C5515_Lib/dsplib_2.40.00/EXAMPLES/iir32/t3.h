#define NX 16
#define NBIQ 4
#define NH   5 * NBIQ 
#define FNAME "t3"
#define MAXERROR 10

DATA x[NX] ={
23593,
23177,
6131,
-226,
26199,
21078,
9496,
20838,
10500,
-10357,
-13781,
-10408,
2233,
14884,
-12499,
22183,
};

#pragma DATA_SECTION(h,".coeffs")
LDATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
63701277,
128780948,
122632856,
-14796093,
18273043,
-97571160,
-61351598,
6064044,
52228693,
-34785562,
-131061686,
-66483519,
102043544,
32563907,
54422526,
105736074,
100862347,
-87790080,
79140351,
12501335,
};

#pragma DATA_SECTION(dbuffer,".dbuffer")
LDATA dbuffer[2*NBIQ+2] ;

LDATA *dp = dbuffer;

DATA r[NX] ;

DATA rtest[NX] ={
-1,
0,
0,
-1,
-1,
-1,
0,
0,
-1,
-1,
0,
0,
0,
1,
0,
-1,
};

