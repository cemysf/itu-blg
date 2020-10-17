//*****************************************************************************
//  Filename:	 expn_t.c
//  Version:	 0.01
//  Description: test for expn routine
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
ushort of;
    // compute
    of = expn(x, r, NX);

    // test
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
