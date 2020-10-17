//*****************************************************************************
//  Filename:	 atant_t.c
//  Version:	 1.00
//  Description: test for atan routine
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
ushort rValue;

void main()
{
    // clear result
    for (i=0; i<NX; i++) r[i] = 0;

    // compute
    rValue = atan16(x, r, NX);

    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
