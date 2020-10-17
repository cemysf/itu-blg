//*****************************************************************************
//  Filename:	 mul_t.c
//  Version:	 0.01
//  Description: test for mul32 routine
//*****************************************************************************

#include <math.h>
#include <tms320.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h"		
#include "test.h"

// generic variables
short i;

// test for h values
short eflag = PASS;		 // error flag or index of r vector where error
LDATA elevel = 0;		 // error level at failing eflag index location
LDATA emax = 0; 		 // max error level detected across when NOERROR

void main()
{
    // clear
    for (i=0;i<NX;i++) r[i] =0;	// clear output buffer (optional)

    // compute
    mul32(x,y,r,NX);

    // test  
    eflag = ltest(r, rtest, NX, (LDATA) MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}

