//*****************************************************************************
//  Filename:	 dlms_t.c
//  Version:	 0.01
//  Description: test for dlms routine
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

short i;
short eflagr= PASS;
short eflagh= PASS;

void main()
{
    // clear
    for (i=0;i<NH;i++) h[i] =0;	// clear coeff buffer (optional)
    for (i=0;i<NX;i++) r[i] =0;	// clear output buffer (optional)
    dbuffer[0] = 0;             // clear index
    for (i=1; i<NH+2; i++) dbuffer[i] = 0; // clear delay buffer (a must)

    // compute
    dlms(x,h,r,des,dbuffer,STEP, NH, NX);

    // test
    eflagr = test(r, rtest, NX, MAXERROR);	// for r
    eflagh = test(h, htest, NH, MAXERROR);	// for h

    if( (eflagr != PASS) || (eflagh != PASS) )
    {
        exit(-1);
    }

    return;
}
