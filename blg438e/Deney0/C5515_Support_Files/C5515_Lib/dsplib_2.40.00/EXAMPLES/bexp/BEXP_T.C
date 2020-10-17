//*****************************************************************************
//  Filename:	 bexp_t.c
//  Version:	 1.0
//  Description: test for bexp routine
//*****************************************************************************

#include <math.h>
#include <tms320.h>
#include <stdio.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h"
#include "test.h"

short i;
short eflag= PASS;

void main()
{
    // clear
    r = 0;

    // compute
    r = bexp(x, NX);

    // test
    eflag = test(&r, &rtest, 1, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }


    return;
}
