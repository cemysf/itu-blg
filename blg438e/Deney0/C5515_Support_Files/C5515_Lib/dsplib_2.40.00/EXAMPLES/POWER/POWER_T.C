//*****************************************************************************
//  Filename:	 power_t.c
//  Version:	 0.01
//  Description: test for power routine
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


void main()
{
    // clear
    r = 0;                       // clear output buffer (optional)

    // compute
    power(x,&r,NX);

    // test
    eflag = ltest (&r, &rtest, 1, (LDATA) MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
