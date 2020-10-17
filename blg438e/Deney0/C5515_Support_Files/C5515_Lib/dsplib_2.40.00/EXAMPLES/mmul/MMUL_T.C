//*****************************************************************************
//  Filename:	 mmul_t.c
//  Version:	 0.01
//  Description: test for mmul routine
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
    for (i=0;i<row1*col2;i++) r[i] =0;             // clear output buffer (optional)

    // compute
    mmul(x1, row1, col1, x2, row2, col2, r);

    // test
    eflag = test(r, rtest, row1*col2, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
