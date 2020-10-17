/*********************************************************/
/*	Biased Autocorrelation								 */
/*	r[j] =  segma(0,nx-j-1)(x[j+k]*x[k])           */
/*********************************************************/

#include <tms320.h>

void acorr_c_raw(DATA *x, DATA *r, ushort nx, ushort nr){

	DATA *x_ptr,*xb_ptr,*r_ptr,*x2_save,*x_save,*cdp;
	
	short counter,loop_count,exec,i,j,csr;
	long ac0,ac3,ac1,ac2;
	
	//initialize some of the variables
	exec=0;
	loop_count=nr-1;
	x_save=x;
	x2_save=x;
	r_ptr=r;
		
	ac0=nx-nr;
	
	if(ac0==1){
		exec-=1;
		loop_count-=1;
	}
	else if(ac0==0){
		loop_count-=2;
		exec+=1;
	}
	
	
	
	if(nr!=1){
		
		//generic pointer and loop setup
		cdp=x_save;
		x_ptr=x2_save;
		xb_ptr=x_ptr+1;
		loop_count>>=1;
		counter=nx-4;
		csr=counter;
		for(i=0;i<=loop_count;i++){
			//ac1=(long)((*x_ptr++)*(long)(*cdp));
			ac1=(long)(*x_ptr)*(*cdp);
			x_ptr++;
			ac0=ac1<<1;
			//ac2=(long)((long)(*xb_ptr++)*(long)(*cdp++));
			ac2=(long)(*xb_ptr)*(*cdp);
			xb_ptr++;cdp++;
			ac3=ac2<<1;
			x2_save+=2;
			for(j=0;j<=csr;j++){
				//ac1=(long)((*x_ptr++)*(long)(*cdp));
				ac1=(long)(*x_ptr)*(*cdp);
				x_ptr++;
				ac0+=ac1<<1;
				//ac2=(long)((long)(*xb_ptr++)*(long)(*cdp++));
				ac2=(long)(*xb_ptr)*(*cdp);
				xb_ptr++;cdp++;
				ac3+=ac2<<1;
			}
			csr-=2;
			
			ac2=(long)(*xb_ptr)*(*cdp);
			ac3+=ac2<<1;
			ac3+=0x8000;
			ac3>>=16;
			
			ac1=(long)(*x_ptr)*(*cdp);
			x_ptr++;cdp++;
			ac0+=ac1<<1;
			ac1=(long)(*x_ptr)*(*cdp);
			ac0+=ac1<<1;
			ac0+=0x8000;
			ac0>>=16;
			
			x_ptr=x2_save;
			cdp=x_save;
						
			*r_ptr++=(short)ac0;
			*r_ptr++=(short)ac3;
			xb_ptr=x_ptr+1;
		}
		if(exec==0)
			return;

		//ac1=(long)((*x_ptr++)*(long)(*cdp++));
		ac1=(long)(*x_ptr)*(*cdp);
		x_ptr++;cdp++;
		ac0=ac1<<1;
		//ac1=(long)((*x_ptr)*(long)(*cdp--));
		ac1=(long)(*x_ptr)*(*cdp);
		cdp--;
		ac0+=ac1<<1;
		ac0+=0x8000;
		ac0>>=16;
		*r_ptr++=(short)ac0;
		if(exec>=0){
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*cdp);
			ac0=ac1<<1;
			ac0+=0x8000;
			ac0>>=16;
			*r_ptr++=(short)ac0;
		}
		//finish
		return;
	}
	else{
	//single mac
		cdp=x_save;
		x_ptr=x2_save;
		csr=nx-3;
		//ac1=(long)((*x_ptr++)*(long)(*cdp++));
		ac1=(long)(*x_ptr)*(*cdp);
		x_ptr++;cdp++;
		ac0=ac1<<1;
		for(j=0;j<=csr;j++){
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*cdp);
			x_ptr++;cdp++;
			ac0+=ac1<<1;
		}
		ac1=(long)(*x_ptr)*(*cdp);
		ac0+=ac1<<1;
		ac0+=0x8000;
		ac0>>=16;
		*r_ptr++=(short)ac0;
		return;		
	}
}
