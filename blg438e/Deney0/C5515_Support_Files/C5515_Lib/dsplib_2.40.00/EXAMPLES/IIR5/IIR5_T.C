//*****************************************************************************
//  Filename:	 iir5_t.c
//  Version:	 0.01
//  Description: test for iircas5 routine
//*****************************************************************************

#include <math.h>
#include <stdio.h>
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
short eflag = PASS;		// error flag or index into r vector where error


void main()
{
    // clear
    for (i=0;i<NX;i++) r[i] =0;	                    // clear output buffer (optional)
    for (i=0; i<5*NBIQ; i++) dbuffer[i] = 0;        // clear delay buffer (a must)

    // compute
    iircas5(x, h, r, dp, NBIQ, NX);

    // test  
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
