//=============================================================================
//  Filename:	 cubias_t.c
//  Version:     0.001				       
//  Description: test for real cross-correlation (unbiased)
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

#define NLAGS    NA + NB - 1

short i;
short eflag=PASS; 	       // error flag (-1: no error; else error)
DATA r[NLAGS];


void main()
{
    //clear
    for (i=0;i<NLAGS;i++) r[i] =0;

    // compute  
    corr(b,a,r,NA,NB,unbias);

    // test  
    eflag=test(r, rtest, NLAGS, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
