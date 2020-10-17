f = 10000;
dt = 1/f;
t = 0:dt:40*dt;

for n = 1 : 1 : 4
    y(n) = sin((2*pi*(n-1))/40);
end

A = y(3) / y(2);

B = (y(4) -(A*y(3))) / y(2);

for n = 2 : 1 : 40 

    y(n+1) = A*y(n) + B*y(n-1); 
end

plot(t,y);

