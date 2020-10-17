//=============================================================================
//  Filename:	 conv2_t.c
//  Version:     1.0				       
//  Description: test for convolution
//=============================================================================
#include <math.h>
#include <stdio.h>
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

#define	NR	NX

short i;
short eflag=PASS; 	       // error flag (-1: no error; else error)

#pragma DATA_SECTION(r, ".coeffs")
DATA r[NR];


void main()
{
    //clear
    for (i=0;i<NX;i++) r[i] =0;

    // compute
    convol2(x_np,h,r,NR,NH);

    // test  
    eflag = test(r, rtest, NR, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
