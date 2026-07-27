%% Part 1 - Read WAV file and plot F.T. of the file signal
%read audio
[x_t,fs] = audioread(['output.wav']);

%create time variables
N = length(x_t);    %number of samples
T = 1/fs;           %sample period
t = (0:N-1)*T;      %time vector in intervals of T

%frequency variables
fbase = fs/N;        %base frequency - smallest interval of frequency
f = (0:N/2-1)*fbase; %frequency vector in intervals of f-base
w = 2*pi*f;          %radial frequency vector

%compute fourier transform
X_jw = fft(x_t,N)/N;         %FT and normalization
X_jw_mag = abs(X_jw);        %2-sided magnitude

if mod(N,2) == 0 %1-sided magnitude (take half of magnitude)
    X_jw_mag1 = X_jw_mag(1:N/2);     %even number of samples
else
    X_jw_mag1 = X_jw_mag(1:(N-1)/2); %odd number of samples
end

[x_t1,fs1] = audioread(['output_denoised.wav']);

%create time variables
N1 = length(x_t1);    %number of samples
T1 = 1/fs1;           %sample period
t1 = (0:N1-1)*T1;      %time vector in intervals of T

%frequency variables
fbase1 = fs1/N1;        %base frequency - smallest interval of frequency
f1 = (0:N1/2-1)*fbase1; %frequency vector in intervals of f-base
w1 = 2*pi*f1;          %radial frequency vector

%compute fourier transform
X_jw1 = fft(x_t1,N1)/N1;         %FT and normalization
X_jw_mag2 = abs(X_jw1);        %2-sided magnitude

if mod(N1,2) == 0 %1-sided magnitude (take half of magnitude)
    X_jw_mag3 = X_jw_mag2(1:N1/2);     %even number of samples
else
    X_jw_mag3 = X_jw_mag2(1:(N1-1)/2); %odd number of samples
end

%plot time
figure(1);
subplot(2,2,1);
plot(t,x_t);
title('Time-analysis of original signal');
xlabel('t (s)');
ylabel('signal x(t) (V)');

%plot magnitude of frequency
subplot(2,2,3);
plot(f(1:100000),X_jw_mag1(1:100000));
title('Frequency-analysis of original signal');
xlabel('f (1/s)');
ylabel('|X(jw)| (V)');

subplot(2,2,2);
plot(t1,x_t1);
title('Time-analysis of denoised signal');
xlabel('t (s)');
ylabel('signal x(t) (V)');

%plot magnitude of frequency
subplot(2,2,4);
plot(f1(1:100000),X_jw_mag3(1:100000));
title('Frequency-analysis of denoised signal');
xlabel('f (1/s)');
ylabel('|X(jw)| (V)');
