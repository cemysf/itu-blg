//;***********************************************************
//; Version 2.30.00                                           
//;***********************************************************
//; Function:    acorr_unbias
//; Processor:   C55xx
//; Description: calculates positive unbiased auto-correlation
//; Usage:    short acorr_c_unbias(DATA *x, DATA *r, ushort nx, ushort nr)
//; Copyright Texas instruments Inc, 2004
//;****************************************************************

#include <tms320.h>

void acorr_c_unbias(DATA *x, DATA *r, ushort nx, ushort nr){

	DATA *x_ptr,*xb_ptr,*r_ptr,*x2_save,*x_save,*cdp;
	
	short counter,odd,loop_count,exec,i,j,k,csr,t2,t3;
	short temp,temp1;
	long ac0,ac3,ac1,ac2,c;
	
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
	
	//divisor value setup
	temp=nx;
	temp1=nx-1;
	
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
			x_ptr++;cdp++;
			
			t2=(short)(ac3>>16);
			t3=(short)(ac0>>16);
			//c=t2;
			//ac3=t3;
			//ac0=t3;
			cdp=x_save;
			ac3=ABSVAL(t3);
			c=ABSVAL(t2);
			x2_save+=2;
			for(k=0;k<=15;k++){
				if (ac3>=((long)temp<<15)){
					ac3-=(long)temp<<15;
					ac3=(ac3<<1)+1;
				}
				else
					ac3<<=1;
				if (c>=((long)temp1<<15)){
					c-=(long)temp1<<15;
					c=(c<<1)+1;
				}
				else
					c<<=1;
			}
			if(t3<0)
				ac3=-ac3;
			if(t2<0)
				c=-c;

			*r_ptr++=(short)ac3;
			*r_ptr++=(short)c;
			x_ptr=x2_save;
			xb_ptr=x_ptr+1;
			temp-=2;
			temp1-=2;
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
			x_ptr++;cdp++;
			ac0+=ac1<<1;
			
			t3=(short)(ac0>>16);
			cdp=x_save;
			ac3=ABSVAL(t3);
			for(k=0;k<=15;k++){
				if (ac3>=((long)temp<<15)){
					ac3-=(long)temp<<15;
					ac3=(ac3<<1)+1;
				}
				else
					ac3<<=1;
			}
			if(t2<0)
				ac3=-ac3;
			*r_ptr++=(short)ac3;

			x_ptr=x2_save;
		}
		//regular
		//ac1=(long)((*x_ptr++)*(long)(*cdp++));
		if(exec==0)
			return;
			
		ac1=(long)(*x_ptr)*(*cdp);
		x_ptr++;cdp++;
		ac0=ac1<<1;
		//ac1=(long)((*x_ptr)*(long)(*cdp--));
		ac1=(long)(*x_ptr)*(*cdp);
		cdp--;
		ac0+=ac1<<1;
		ac0+=0x8000;
		ac0>>=17;
		*r_ptr++=(short)ac0;
		if(exec>=0){
			//ac1=(long)((*x_ptr++)*(long)(*cdp++));
			ac1=(long)(*x_ptr)*(*cdp);
			//x_ptr++;cdp++;
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
		temp=nx;
		cdp=x_save;
		x_ptr=x2_save;
		csr=nx-2;
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
		ac3=ABSVAL(t3);
		for(k=0;k<=15;k++){
			if (ac3>=((long)temp<<15)){
				ac3-=(long)temp<<15;
				ac3=(ac3<<1)+1;
			}
			else
				ac3<<=1;
		}
		if(t3<0)
			ac3=-ac3;
		*r_ptr++=(short)ac3;
		return;		
	}
}
