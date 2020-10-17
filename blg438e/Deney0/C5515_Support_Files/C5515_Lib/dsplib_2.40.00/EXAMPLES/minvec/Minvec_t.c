//*****************************************************************************
//  Filename:	 minvec_t.c
//  Version:	 0.01
//  Description: test for minvec routine
//*****************************************************************************

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

short i;
short eflagv = PASS;		// error flag for value into r vector where error
short eflagi = PASS;		// error flag for index into r vector where error


void main()
{

    r_val = 0;                     // clear output index (optional)
    r_idx = 0;    
    
    // compute
    minvec(x, NX, &r_val, &r_idx);

    // test  
    eflagv = test(&r_val, &r_testval, 1, MAXERROR);
    eflagi = test(&r_idx, &r_testidx, 1, MAXERROR);

    if( (eflagv != PASS) || (eflagi != PASS) )
    {
        exit(-1);
    }

    return;
}

