//=============================================================================
//  Filename:	 ldiv16_t.c
//  Version:     0.001				       
//  Description: test 32 bit by 16 bit divide (Q31/Q15 format assumed)
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

#define NR    NX

short i;
short eflag=-1; 	       // error flag (-1: no error; else error)
float elevel;		       // error level detected

LDATA rem;
DATA exponent;
DATA explevel;

float rfloat[NR];


void main(void)
{ 
    // clear
    for(i=0; i <= NR - 1; i++)
    {
        r[i] = 0;
        rexp[i] = 0;
        rfloat[i] = 0;
    }

    ldiv16(x, y, r, rexp, NX);

    // test 
    q15tofl(r, rfloat, NR);

    for (i = 0; i <= NR-1; i++)
    {
        rfloat[i] = rfloat[i] * (float) rexp[i];
    }

    eflag = ftest(rfloat, rtest, NR, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }
    
    return;
}
