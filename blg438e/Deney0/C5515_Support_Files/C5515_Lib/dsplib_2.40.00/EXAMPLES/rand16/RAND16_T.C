//*****************************************************************************
//  Filename:	 rand_t.c
//  Version:	 0.01
//  Description: test for random number genrator routine
//*****************************************************************************

#include <math.h>
#include <tms320.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
#include "t4.h"		
//#include "test.h"

// generic variables
short i,j;

// test for h values
short eflag = PASS;		 // error flag or index of r vector where error
DATA elevel = 0;		 // error level at failing eflag index location
DATA emax = 0;			 // max error level detected across when NOERROR

void main()
{
    // clear
    for (i=0;i<NX;i++){
        r1[i] =0;     // clear output buffer (optional)
        r2[i] =0;
    }

    // compute

    rand16init();
    rand16(r1,NX);

    for (i=0; i<NX-2; i++)
    for(j=i+1; j<NX-1; j++)
    {
        if (r1[i] == r1[j])
            elevel = i;
        if (elevel)
        {
            eflag = 0x1;
            exit(0);
        }
    }

    rand16init();
    rand16(r2,NX);

    // test
    eflag = test (r1, r2, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
