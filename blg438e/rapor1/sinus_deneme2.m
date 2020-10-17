Fs = 2;                   % �rnekleme frekans� (Hz)
Ts = 1/Fs;                      % �rnekleme periyodu (s)
tlen = 10;                       % sinyal uzunlu�u (s)
A = 2;                          % sinyal genli�i
f0 = 1;                     % sinyalin frekans� (Hz)
theta = pi/6;                   % sinyalin faz fark� (rad)
X0 =  0;                        % sinyalin offset'i

t = (0:round(tlen*Fs)-1)/Fs;  
y2 = X0 + A*cos(2*t);
y = X0 + A*sin(2*pi*f0*t + theta);
y1 = 2*sin(t/2 + pi/6);


td1 = 0;                       % g�r�nt�leme ba�lang�c�
td2 = 10;%10^-3;                   % g�r�nt�leme biti�i
ix = find(t>=td1&t<td2);     % g�r�nt�leme indeksi
plot(t(ix),y2(ix),'-b')       % grafik �izimi