dt=1/100;
t=0:dt:1;
f=30;
x=sin(2*pi*f*t);
y=sin(2*pi*f*t+pi);
%plot(t,y)
%plot(t,x)
plot(t,y+x), grid on