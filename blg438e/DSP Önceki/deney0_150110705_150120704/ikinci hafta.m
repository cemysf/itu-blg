dt= 1/48000;
t = 0:dt:0.01;
f = 1000; % 1 kHz
f1 = 15000; % 15 kHz
y = sin(2*pi*f*t) 
x = sin(2*pi*f1*t) 
z = y + x
 
%plot(t,y,'-',t,z,'--',t,x,':')
s =zeros(1,481); % 0 larý ile gösteriyor arrayi
 
 for n = 1 : 1 : 481 
     for k = 1 : 1 : 50 % 50 order sayýsý
         if (n-k <= 0)
             break;
         end
        s(n) = s(n) + Num(k)*z(n-k); % sn filtre fonksiyonu
     end
 end

 plot(t,y,t,s) % low pass filtre ile orjinal fonksiyon