//*****************************************************************************
//  Filename:	 add_t.c
//  Version:	 1.00
//  Description: test for add routine with scaling option
//*****************************************************************************

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
ushort scale;

// test for h values
short eflag = PASS;		 // error flag or index of r vector where error


void main()
{
    scale = ADD_SCALE;
    
    // clear
    for (i=0;i<NX;i++) r[i] =0;	// clear output buffer (optional)

    // compute
    add(x,y,r,NX, scale);

    // test  
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
