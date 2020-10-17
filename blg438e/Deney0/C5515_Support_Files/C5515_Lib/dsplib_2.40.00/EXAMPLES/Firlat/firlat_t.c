//*****************************************************************************
//  Filename:	 firlat_t.c
//  Version:	 0.01
//  Description: test for firlat routine
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
    for (i=0; i<NK; i++) dbuffer[i] = 0; // clear delay buffer (a must)

    // compute
    firlat(x, k, r, dbuffer, NX, NK);

    // test
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
