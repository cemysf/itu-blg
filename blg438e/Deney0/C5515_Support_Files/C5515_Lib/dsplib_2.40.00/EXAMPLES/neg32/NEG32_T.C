//*****************************************************************************
//  Filename:	 neg32_t.c
//  Version:	 0.01
//  Description: test for neg routine
//*****************************************************************************/

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
//#include "t8.h"		
#include "test.h"

// generic variables
short i;

short eflag = PASS;		 // error flag or index of r vector where error


void main()
{
ushort of;
    // clear
    for (i=0;i<NX;i++) r[i] =0;	// clear output buffer (optional)

    // compute
    of = neg32(x, r, NX);

    // test
    eflag = ltest (r, rtest, NX, (LDATA)MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
