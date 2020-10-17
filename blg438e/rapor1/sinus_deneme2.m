Fs = 2;                   % örnekleme frekansı (Hz)
Ts = 1/Fs;                      % örnekleme periyodu (s)
tlen = 10;                       % sinyal uzunluğu (s)
A = 2;                          % sinyal genliği
f0 = 1;                     % sinyalin frekansı (Hz)
theta = pi/6;                   % sinyalin faz farkı (rad)
X0 =  0;                        % sinyalin offset'i

t = (0:round(tlen*Fs)-1)/Fs;  
y2 = X0 + A*cos(2*t);
y = X0 + A*sin(2*pi*f0*t + theta);
y1 = 2*sin(t/2 + pi/6);


td1 = 0;                       % görüntüleme başlangıcı
td2 = 10;%10^-3;                   % görüntüleme bitişi
ix = find(t>=td1&t<td2);     % görüntüleme indeksi
plot(t(ix),y2(ix),'-b')       % grafik çizimi