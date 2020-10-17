//*****************************************************************************
//  Filename:	 recip_t.c
//  Version:	 0.01
//  Description: test for reciprocal of Q15 number
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
DATA elevel = 0;		 // error level at failing eflag index location
DATA emax = 0;			 // max error level detected across when NOERROR
float  r[NX];


void main(void)
{
    // clear
    for (i=0;i<NX;i++) 
    { 
        r[i] =0;	// clear output buffer (optional)		    
    }
    
    // compute
    q15tofl(x, r, NX);

    // test
    eflag = ftest(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
