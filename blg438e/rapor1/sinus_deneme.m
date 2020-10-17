clear all

t=-10:0.01:1;  %%[0:1:100];      %%0:(10^-5):(10^-3);          %%[0:0.01:1];
a=2;            %%genlik
f=10000;            %%sinyal frekans
s=44100;            %% örnekleme frekans
%y=a*sin(2*pi*f/s*t);
%y=a*sin(2*pi*t);
y=2*sin(t/2 + pi/6);
plot(y);