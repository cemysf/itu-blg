
fs = 48000;
dt = 1 / fs;
t = 0:dt:0.01;

s1 = sin(2 * pi * 1000 * t);
s2 = sin(2 * pi * 10000 * t);

y = zeros(1,481);

x = s1 + s2;

%Aþaðýdaki formül IIR filtre için standard fark denklemidir. b payý a ise paydayý temsil etmektedir. 
%y[n] = 1/a0(b0x[n] + b1x[n-1] + … + bpx[n-p] - a1x[n-1] - a2x[n-2] - … - aqx[n-q]

for a = 1 : 1 : 4
    for n = 1 : 1 : 481
        if n == 1 
            y(n) = (SOS(a,1)*x(n))/SOS(a,4); 
        elseif n == 2
            y(n) = (x(n) + SOS(a, 2) * x(n - 1) - SOS(a, 5) * y(n - 1))/SOS(a,4);
        else
            y(n) = (x(n) + SOS(a, 2) * x(n - 1) + SOS(a, 3) * x(n - 2) - SOS(a, 5) * y(n - 1) - SOS(a, 6) * y (n - 2))/SOS(a,4);
        end
    end
    for i = 1 : 1 : 481
    x(i) = y(i);
    end
end

plot(t, s1, t, (G(1)*G(2)*G(3)*y));