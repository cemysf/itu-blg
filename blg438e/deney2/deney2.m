%% d1.2-a
%%  R=1k, C=10^-6f i�in transfer fonk=1/(10^-3s + 1)
num = [1];
%denum=[10^-3, 1];  %%birinci derece filtre
denum=[10^-6, 2*10^-3, 1];

transfer_func = tf(num, denum);

%Fs = 10000;       %%�rnekleme frekans�
%t=(0:Fs-1)/Fs;
t=0:0.00001:0.01; %%1kHz,300Hz i�in
%t=0:0.001:1;    %%10Hz i�in
A=1.6;          %% sin�s fonk genlik
f=1000;           %% sin�s fonk frekans�
y=A*sin(2*pi*f*t);
%lsim(transfer_func,y,t);   %% grafikte mavi ��k��, gri giren sinyal
bode(transfer_func);        %%birinci derece trans fonk i�in bode -40db'e gidiyor,
                            %%ikinci derecede -80dB'e gidiyor
