	  .org $0
	   lds  #$5f00 ;set stack pointer
	   ldaa #$07   ;calculate fifth element of fibonacci series
	   psha
	   jsr  fbnc
       pula
	   staa $0100  ;store result at $0100
       bra  finish

fbnc   tsx
	   ldaa 2,x   ;argument is taken
	   cmpa #$02  ;if n is less than 2, return
	   blt  term   
	   ldaa 2,x   ;take argument
       deca       ;n-1
	   staa 2,x   ;store (n-1)
       psha       ;send (n-1) to fib
	   jsr  fbnc  ;run fib(n-1)
	   pulb       ;pull return value
       tsx         
       ldaa 2,x   ;now Acca has n-1
       deca       ;n-2
       stab 2,x   ;store (fib(n-1)) 
       psha       ;send n-2 to fib
       jsr fbnc   ;run fib(n-2)
       pulb       ;take return value
       tsx     
       ldaa 2,x   ;load acca with fib(n-1) that was stored before
       aba        ;result = fib(n-1)+fib(n-2)
       staa 2,x   ;store this stack location to return value
term   rts        ;return

finish .end
