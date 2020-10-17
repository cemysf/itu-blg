//;***********************************************************
//; Version 2.30.00                                           
//;***********************************************************
//; Function:    acorr_bias
//; Processor:   C55xx
//; Description: calculates positive biased auto-correlation
//;
//; Usage:    short acorr_bias(DATA *x, DATA *r, ushort nx, ushort nr)
//;
//; Copyright Texas instruments Inc, 2004
//;****************************************************************


#include <tms320.h>

void acorr_c_bias(DATA *x, DATA *r, ushort nx, ushort nr){

	DATA *x_ptr,*xb_ptr,*r_ptr,*x2_save,*x_save,*cdp;
	
	short counter,odd,loop_count,exec,n_inverse,i,j,csr,t2,t3;
	long nxs;
	long ac0,ac3,ac1,ac2;
	
	//initialize some of the variables
	exec=0;
	loop_count=nr-1;
	odd=0;
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
	
	//prepare for scaling
	ac0=32767;
	nxs=((long)(nx))<<15;
	for(i=0;i<16;i++){
		if(ac0<nxs)
			ac0<<=1;
		else
			ac0=((ac0-nxs)<<1)+1;
	}
	n_inverse=(short)(ac0+1);
	
	if(nr!=1){
		//test if nr is odd
		if(nr%2)
			odd=1;
		
		//generic pointer and loop setup
		cdp=x_save;
		x_ptr=x2_save;
		xb_ptr=x_ptr+1;
		loop_count>>=1;
		if(odd)
			loop_count-=1;
		counter=nx-3;
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
			//ac1=(long)((*x_ptr)*(long)(*cdp));
			ac1=(long)(*x_ptr)*(*cdp);
			ac0+=ac1<<1;
			t2=(short)(ac3>>16);
			ac3=(long)(n_inverse)*t2;
			ac3<<=1;
			ac3+=0x8000;
			ac3>>=16;
			//ac3<<=16;
			t3=(short)(ac0>>16);
			ac0=(long)(n_inverse)*t3;
			ac0<<=1;
			ac0+=0x8000;
			ac0>>=16;
			//ac0<<=16;
			x2_save+=2;
			*r_ptr++=(short)ac0;
			cdp=x_save;
			*r_ptr++=(short)ac3;
			x_ptr=x2_save;
			xb_ptr=x_ptr+1;
		}
		if(odd){
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*cdp);
			x_ptr++;cdp++;
			ac0=ac1<<1;
			x2_save++;
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*cdp);
			x_ptr++;cdp++;
			ac0+=ac1<<1;
			//ac1=(long)((*x_ptr)*(long)(*cdp));
			ac1=(long)(*x_ptr)*(*cdp);
			ac0+=ac1<<1;
			t3=(short)(ac0>>16);
			ac0=(long)(n_inverse)*t3;
			ac0<<=1;
			ac0+=0x8000;
			ac0>>=16;
			*r_ptr++=(short)ac0;
			cdp=x_save;
			x_ptr=x2_save;
		}
		//regular
		//ac1=(long)((*x_ptr++)*(long)(*cdp++));
		ac1=(long)(*x_ptr)*(*cdp);
		x_ptr++;cdp++;
		ac0=ac1<<1;
		//ac1=(long)((*x_ptr)*(long)(*cdp--));
		ac1=(long)(*x_ptr)*(*cdp);
		cdp--;
		ac0+=ac1<<1;
		t3=(short)(ac0>>16);
		ac0=(long)(n_inverse)*t3;
		ac0<<=1;
		ac0+=0x8000;
		ac0>>=16;
		*r_ptr++=(short)ac0;
		if(exec>=0){
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*cdp);
			//x_ptr++;cdp++;
			ac0=ac1<<1;
			t3=(short)(ac0>>16);
			ac0=(long)(n_inverse)*t3;
			ac0<<=1;
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
		t3=(short)(ac0>>16);
		ac0=(long)(n_inverse)*t3;
		ac0<<=1;
		ac0+=0x8000;
		ac0>>=16;
		*r_ptr++=(short)ac0;
		return;		
	}
}
