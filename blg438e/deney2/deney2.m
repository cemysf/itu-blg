%% d1.2-a
%%  R=1k, C=10^-6f için transfer fonk=1/(10^-3s + 1)
num = [1];
%denum=[10^-3, 1];  %%birinci derece filtre
denum=[10^-6, 2*10^-3, 1];

transfer_func = tf(num, denum);

%Fs = 10000;       %%örnekleme frekansý
%t=(0:Fs-1)/Fs;
t=0:0.00001:0.01; %%1kHz,300Hz için
%t=0:0.001:1;    %%10Hz için
A=1.6;          %% sinüs fonk genlik
f=1000;           %% sinüs fonk frekansý
y=A*sin(2*pi*f*t);
%lsim(transfer_func,y,t);   %% grafikte mavi çýkýþ, gri giren sinyal
bode(transfer_func);        %%birinci derece trans fonk için bode -40db'e gidiyor,
                            %%ikinci derecede -80dB'e gidiyor
