//*****************************************************************************
//  Filename:	 decim_t.c
//  Version:	 0.01
//  Description: test for decimate routine
//*****************************************************************************/

#include <math.h>
#include <tms320.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
#include "t4.h"	
//#include "test.h"

short i;
short eflag= PASS;
DATA  *dbptr = &db[0];

main()
{
	/* clear */
	for (i=0;i<(NX/D);i++) r[i] =0;	/* clear output buffer (optional) */
	for (i=0; i<NH+1; i++) db[i] = 0; /* clear delay buffer (a must)  */

	/* compute */
	firdec(x,h,r,dbptr,NH,NX,D);
	eflag = test(r, rtest, NX/D, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

	return 1;
}
