/***********************************************************/
/* Version 2.30.00                                         */
/***********************************************************/
#ifndef _DSPLIBC
#define _DSPLIBC

#include <tms320.h>


/* correlations */

void acorr_c_raw(DATA *x, DATA *r, ushort nx, ushort nr);
void acorr_c_bias(DATA *x, DATA *r, ushort nx, ushort nr);
void acorr_c_unbias(DATA *x, DATA *r, ushort nx, ushort nr);

/* filtering and convolution */


void fir_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);
void fir2_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);
void firs_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh2);
void cfir_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);

void iircas4_c(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);
void iircas5_c(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);
void iircas51_c(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);


/* adaptive filtering */

void dlms_c(DATA *x, DATA *h, DATA *r, DATA *des, DATA *dbuffer, DATA step, ushort nh,  ushort nx);


/* macro definition */


#define acorr_c(n1, n2, n3, n4, type) acorr_c_##type(n1, n2, n3, n4)

#endif
