Fs = 1000000                      % �rnekleme frekans� (Hz)
Ts = 1/Fs;                      % �rnekleme periyodu (s)
tlen = 10;                       % sinyal uzunlu�u (s)
A = 2;                          % sinyal genli�i
f0 = 10000;                    % sinyalin frekans� (Hz)
theta = pi/6;                   % sinyalin faz fark� (rad)
X0 =  0;                        % sinyalin offset'i
 
t = (0:round(tlen*Fs)-1)/Fs;  
y = X0 + A*sin(2*pi*f0*t + theta);

td1 = 0;                       % g�r�nt�leme ba�lang�c�
td2 = 10^-3;                   % g�r�nt�leme biti�i
ix = find(t>=td1&t<td2);       % g�r�nt�leme indeksi
plot(t(ix),y(ix),'-b')         % grafik �izimi
