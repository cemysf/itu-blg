//*****************************************************************************
//  Filename:	 fir2_t.c
//  Version:	 0.01
//  Description: test for fir2 routine
//*****************************************************************************

#include <math.h>
#include <tms320.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h"
//#include "t5.h"
//#include "t6.h"
//#include "t7.h"
#include "t8.h"	
//#include "test.h"

short i;
short eflag1= PASS;
short eflag2= PASS;
DATA  r[NX];
DATA  *dbptr = &db[0];


void main()
{
    // 1. Test for single-buffer

    // clear
    for (i=0; i<NX; i++) r[i] = 0;	     // clear output buffer (optional)
    for (i=0; i<NH+2; i++) db[i] = 0;        // clear delay buffer (a must)

    // compute
    fir2(x, h, r, dbptr, NX, NH);

    // test
    eflag1 = test (r, rtest, NX, MAXERROR);

    // 2. Tets for dual-buffer

    // clear
    for (i=0; i<NX; i++) r[i] = 0;	     // clear output buffer (optional)
    for (i=0; i<NH+2; i++) db[i] = 0;        // clear delay buffer (a must)

    dbptr = &db[0];

    // compute
    if (NX>=4)
    {
        fir2(x, h, r, dbptr, NX/4, NH);
        fir2(&x[NX/4], h, &r[NX/4], dbptr, NX/4, NH);
        fir2(&x[2*NX/4], h, &r[2*NX/4], dbptr, NX/4, NH);
        fir2(&x[3*NX/4], h, &r[3*NX/4], dbptr, NX/4, NH);
    }

    // test
    eflag2 = test (r, rtest, NX, MAXERROR);

    if( (eflag1 != PASS) || (eflag2 != PASS) )
    {
        exit(-1);
    }
  
    return;
}
