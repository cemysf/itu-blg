f=1000;
Fs=48000;
Ts=1/Fs;
t=0:Ts:0.01;
x=sin(2*pi*f*t)+sin(2*pi*15000*t);
%plot(x),grid on
plot(x)
F=fft(x); 
y1=abs(F)
y2=(y1(1:241))
z = linspace(0,24000,241)
%plot(z,y2);
%plot(abs(F))
