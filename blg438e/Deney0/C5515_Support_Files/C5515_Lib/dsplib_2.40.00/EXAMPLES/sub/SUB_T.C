//*****************************************************************************
//  Filename:	 sub_t.c
//  Version:	 0.01
//  Description: test for sub routine with scaling option
//*****************************************************************************

#include <math.h>
#include <tms320.h>
#include <dsplib.h>

#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h"
//#include "t5.h"
//#include "t6.h"
//#include "t7.h"
//#include "t8.h"		
//#include "test.h"

// generic variables
short i;
ushort scale;

// test for h values
short eflag = PASS;		 // error flag or index of r vector where error


void main()
{
    // clear
    for (i=0;i<NX;i++) r[i] =0;         // clear output buffer (optional)

    scale = SUB_SCALE;
    
    // compute
    sub(x,y,r,NX, scale);

    // test  
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
