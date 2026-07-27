import sounddevice as sd
from scipy.io.wavfile import write
import numpy as np
from scipy.io import wavfile
import os

def fft(cd, IsInverse):
    N = len(cd)
    if N <= 1:
        return cd
    even = fft(cd[0::2], IsInverse)
    odd = fft(cd[1::2], IsInverse)

    if IsInverse:
        T = [np.exp(-2j * np.pi * k / N) * odd[k] for k in range(N // 2)]
        res = [even[k] + T[k] for k in range(N // 2)] + \
            [even[k] - T[k] for k in range(N // 2)]
        return [x / 2 for x in res]
    else:
        # Forward FFT
        T = [np.exp(2j * np.pi * k / N) * odd[k] for k in range(N // 2)]
        return [even[k] + T[k] for k in range(N // 2)] + \
            [even[k] - T[k] for k in range(N // 2)]

def denoise(input_file, output_file):
    # Read audio file
    fs, data = wavfile.read(input_file)
    data = data.astype(np.float32)



    n = len(data)
    next_power_of_2 = 1 << (n - 1).bit_length()  # Find next power of 2
    if n < next_power_of_2:
        # Pad data with zeros to the next power of 2
        data = np.pad(data, (0, next_power_of_2 - n), mode='constant')

    # Perform FFT
    fft_data = fft(data, False)

    data_clone = np.asarray(fft_data)
    magnitude = np.abs(data_clone)
    noise_floor = np.percentile(magnitude, 90)  
    noise_floor *= 1.5
    # Apply noise threshold
    fft_data = [0.0 if np.abs(val) <= noise_floor else val for val in fft_data]

    # Inverse FFT to get denoised audio
    denoised_data = fft(fft_data, True)
    denoised_data = np.real(denoised_data[:n])
    denoised_data = np.clip(denoised_data, -32768, 32767)
    denoised_data = np.int16(denoised_data)

    wavfile.write(output_file, fs, denoised_data)  
    

def record_audio(filename="output.wav", duration=10, fs=44100):
    audio = sd.rec(int(duration * fs), samplerate=fs, channels=1, dtype='int16')
    sd.wait()
    write(filename, fs, audio)

if __name__ == "__main__":
    print("Recording audio for 10 seconds...")
    record_audio()
    print("Signal recorded. Denoising...")
    denoise("output.wav", "output_denoised.wav")
    print("Denoising complete. Opening denoised audio file...")
    os.startfile("output_denoised.wav")
