dt= 1/48000;
t = 0:dt:0.06;
f = 100; % 100 Hz
f1 = 1000; % 1 kHz
y = sin(2*pi*f*t) % low frequency
x = sin(2*pi*f1*t) % high frequency
m = y .* x

z= m.*x

%plot(t,y,'-',t,x,'--',t,m,':')

%plot(t,z)

s =zeros(1,2881); % 0 larý ile gösteriyor arrayi
 for n = 1 : 1 : 2881
     for k = 1 : 1 : 76 % 76 order sayýsý
         if (n>k)
             s(n) = s(n) + Num(k)*z(n-k); % sn filtre fonksiyonu
         end
        
     end
 end
%plot(t,y)

 plot(t,y, t,s) % low pass filtre ile orjinal fonksiyon

