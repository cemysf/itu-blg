//=============================================================================
//  Filename:	 cbias_t.c
//  Version:     1.0				       
//  Description: test for real cross-correlation (bias)
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

#define NR    NA + NB - 1

short i;
short eflag=PASS; 	       // error flag (-1: no error; else error)
DATA r[NR];


void main()
{
ushort of;
    //clear
    for (i=0;i<NR;i++) r[i] =0;

    // compute  
    of = corr(b,a,r,NA,NB,bias);

    // test  
    eflag = test(r, rtest, NR, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
