//*****************************************************************************
//  Filename:	 log_2_t.c
//  Version:	 0.01
//  Description: test for log2 routine
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
short eflag= PASS;


void main()
{
    // clear
    for (i=0; i<NX; i++) r[i] = 0;

    // compute
    log_2(x, r, NX);

    // test
    eflag = ltest(r, rtest, NX, (LDATA)MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
