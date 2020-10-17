//=============================================================================
//  Filename:	 cfir_t.c
//  Version:     1.0				       
//  Description: test for complex block finite impulse response filter (raw)
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
//#include "t8.h"	
#include "test.h"

#define NR    NX

#pragma DATA_SECTION(x,".input");

short i;
short nx = NX;
short eflag1=-1; 	       // error flag (-1: no error; else error)
short eflag2=-1;	       //

DATA r[2*NR];

DATA *dbptr = &db[0];


void main()
{
    // clear
    for (i=0;i<2*NR;i++) r[i] =0;
    for (i=0;i<2*NH + 2;i++) db[i]=0;

    // compute
    cfir(x, h, r, dbptr, NX, NH);

    // test  
    eflag1 = test(r, rtest, NH, MAXERROR);

    // If NX > = 4 try to use db to point to correct location in buffer
    dbptr = &db[0];

    // clear
    for (i=0;i<2*NR;i++) r[i] =0;
    for (i=0;i<2*NH + 2;i++) db[i]=0;

    // compute
    if (NX >= 4)
    {
        cfir(x, h, r, dbptr, NX/4, NH);
        cfir(&x[NX/2], h, &r[NX/2], dbptr, NX/4, NH);
        cfir(&x[2*NX/2], h, &r[2*NX/2], dbptr, NX/4, NH);
        cfir(&x[3*NX/2], h, &r[3*NX/2], dbptr, NX/4, NH);
    }

    // test  
    eflag2 = test(r, rtest, NH, MAXERROR);

    if( (eflag1 != PASS) || (eflag2 != PASS))
    {
        exit(-1);
    }

    return;
}
