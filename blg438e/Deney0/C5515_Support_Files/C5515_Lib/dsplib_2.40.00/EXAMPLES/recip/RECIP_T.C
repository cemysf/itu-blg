//*****************************************************************************
//  Filename:	 recip_t.c
//  Version:	 0.01
//  Description: test for reciprocal of Q15 number
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

// generic variables
short i;

// test for h values
short eflag = PASS;		 // error flag or index of r vector where error

DATA  r[NX];
DATA  rexp[NX];
float rf1[NX];
float rf2[NX];


void main()
{
    // clear
    for (i=0;i<NX;i++) 
    {
        r[i] =0;	// clear output buffer (optional)
        rexp[i] = 0;
    }

    // compute
    recip16(x, r, rexp, NX);
    q15tofl(r, rf1, NX);

    for (i=0; i<NX; i++)
    {
        rf2[i] = (float)rexp[i] * rf1[i];
    }

    // test
    eflag = ftest(rf2, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
