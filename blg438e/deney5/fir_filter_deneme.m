N   = 2;        % FIR filter order
Fp  = 20e3;       % 20 kHz passband-edge frequency
Fs  = 96e3;       % 96 kHz sampling frequency
Rp  = 0.00057565; % Corresponds to 0.01 dB peak-to-peak ripple
Rst = 1e-4;       % Corresponds to 80 dB stopband attenuation

NUM = firceqrip(N,Fp/(Fs/2),[Rp Rst],'passedge'); % NUM = vector of coeffs
fvtool(NUM,'Fs',Fs,'Color','White') % Visualize filter