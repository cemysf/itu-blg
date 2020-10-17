//*****************************************************************************
//  Filename:	 maxidx_t.c
//  Version:	 0.01
//  Description: test for maxidx routine
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
#include "t6.h"		
//#include "test.h"

short i;
short eflag = PASS;		// error flag or index into r vector where error


void main()
{
    // clear
    r = 0;                      // clear output index (optional)

    // compute
    r = maxidx34(x, NX);

    // test  
    eflag = test(&r, &rtest, 1, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}

