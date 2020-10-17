/*=============================================================================
  Filename:	 iir32_t.c
  Version:     0.001				       
  Description: test for cascaded infinite impulse response filter (raw)
=============================================================================*/
#include <math.h>
#include <stdio.h>
#include <tms320.h>
#include <dsplib.h>

//#include "t1.h"
//#include "t2.h"
//#include "t3.h"
//#include "t4.h"
#include "t5.h"		
//#include "test.h" 

/* #define NR	NX*/

short i;

short eflag=PASS; 	       /* error flag (-1: no error; else error)  */
DATA elevel=0;		       /* error level detected                   */
DATA emax=0;

/* FILE *fp; */


void main()
{
    /* clear   */
    for (i=0;i<NX;i++) r[i] =0;		/* output buffer (optional) */
    for (i=0;i<NX;i++) dbuffer[i]=0;	/* delay buffer (mandatory) */

    /* compute */

    iir32(x, h, r, dp, NBIQ, NX);

    /* test    */
    eflag = test(r, rtest, NX, MAXERROR);

    if(eflag != PASS)
    {
        exit(-1);
    }

    return;
}
