//*****************************************************************************
//  Filename:	 arct2_t.c
//  Version:	 1.00
//  Description: test for atan2 routine
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
//#include "t8.h"	
#include "test.h"

short i;
short eflag= PASS;

void main()
{
    // compute
    atan2_16(x2, x1, r, NX);

    // test
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
