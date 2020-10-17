#include <tms320.h>
#include <dsplib.h>
#include <math.h>
#include <stdio.h>


//#include "t2_SCALE.h"
//#include "t3_SCALE.h"
//#include "t4_SCALE.h"
//#include "t5_SCALE.h"
//#include "t6_SCALE.h"
#include "t7_SCALE.h"


//#include "t2_NOSCALE.h"
//#include "t3_NOSCALE.h"
//#include "t4_NOSCALE.h"
//#include "t5_NOSCALE.h"
//#include "t6_NOSCALE.h"	
//#include "t7_NOSCALE.h"

short eflagi= PASS;


void main()
{
		
    cifft32_SCALE(x,NX);
	//cifft32_NOSCALE(x,NX);
	cbrev32(x, x, NX);
	
	eflagi = ltest(x, rtest, NX, (LDATA)(MAXERROR));	// for r
	if(eflagi!=PASS){
        exit(-1);
	}

}
