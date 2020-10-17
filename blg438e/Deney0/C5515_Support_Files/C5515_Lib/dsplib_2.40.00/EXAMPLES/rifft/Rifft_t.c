//*****************************************************************************
//  Filename:	 rifft_t.c
//  Version:	 0.01
//  Description: test for inverse rfft routine
//*****************************************************************************/

#include <math.h>
#include <tms320.h>
#include <dsplib.h>


//#include "t2.h"
//#include "t3.h"
//#include "t4.h"
//#include "t5.h"
//#include "t6.h"
//#include "t7.h"
//#include "t8.h"
//#include "t9.h"
//#include "t10.h"
//#include "t11.h"
#include "t12.h"	
//#include "test.h"

short eflag= PASS;
short scale = 1;
short noscale = 0;
void unpacki(DATA *x, ushort nx);

void main()
{

    // compute
//    unpacki(x, NX);
//    cifft(x,NX/2,SCALE);
//    cbrev(x,x,NX/2);
    rifft(x,NX,SCALE);
      
    // test
    eflag  = test(x, rtest, NX, MAXERROR);	// for r

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
