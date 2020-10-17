%% d5

num=[0.038, 0.2, 0.0038];   %% A0, A1, A2
denum = [1];
transfer_func = filt(num, denum);

Fs = 1000;       %%sampling freq
t=(0:Fs-1)/Fs;
%%t=0:0.00001:0.01; %%1kHz,300Hz için
%t=0:0.001:1;    %%10Hz için
A=1;          %% sinüs fonk genlik
f=100;           %% sinüs fonk frekansý
y=A*sin(2*pi*f*t);
%lsim(transfer_func,y,t);   %% grafikte mavi çýkýþ, gri giren sinyal
bode(transfer_func);        %%birinci derece trans fonk için bode -40db'e gidiyor,
                            %%ikinci derecede -80dB'e gidiyor
