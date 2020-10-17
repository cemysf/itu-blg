%report2-3
num = [1];
denum=[1,2,1];
transfer_func = tf(num, denum);

Fs = 1000;        % sampling frequency
t=(0:Fs-1)/Fs;
f=10^-2;            % cos function frequency
y=1.6*cos(2*pi*f*t);

lsim(transfer_func,y,t);
