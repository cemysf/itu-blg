//*****************************************************************************
//  Filename:	 rfft_t.c
//  Version:	 0.01
//  Description: test for cfft routine
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
//#include "t9.h"
//#include "t10.h"
//#include "t11.h"
#include "t12.h"		
//#include "test.h"

short eflagf= PASS;


void main()
{
	// compute
   rfft(x,NX,SCALE);
//	cfft(x,NX/2,SCALE); 
//	cbrev(x,x,NX/2);
//	unpack(x,NX);

	eflagf  = test(x, rtest, NX, MAXERROR);	// for r

    if(eflagf != PASS)
    {
        exit(-1);
    }

	return;
}

