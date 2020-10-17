/* Test for sqrtv: rand */
#define NX 10
#define FNAME "t1"
#define MAXERROR 20

DATA x[NX] ={
31133,
7573,
19885,
15924,
29206,
24972,
14957,
606,
26915,
14572,
};

DATA rtest[NX] = {
31940,
15753,
25526,
22843,
30935,
28605,
22138,
4457,
29698,
21851,
};

DATA r[NX];
