"""
This script plots audio waves.
"""

import wave
import numpy as np
import matplotlib.pyplot as plt

# create audio wave object
wav_obj = wave.open('/home/amz/Music/first_sound_for_pet.wav', 'rb')

# get sampling rate
samp_freq = wav_obj.getframerate()

# get number of frames
n_samples = wav_obj.getnframes()

# get length in time
t_wav = n_samples / samp_freq

# get number of channels
n_chan = wav_obj.getnchannels()

# signal waves
sig_wav = wav_obj.readframes(n_samples)

# get signal waves in np array
sig_arr = np.frombuffer(sig_wav, dtype=np.int32)

# get left channel, i.e. from 0, get data with step size of 2
l_chan = sig_arr[0::2]
# get right channel, i.e. from 1, get data with step size of 2
r_chan = sig_arr[1::2]

# get timestamps
times = np.linspace(0, n_samples/samp_freq, num=n_samples)

# plot left channel in time space
plt.figure(figsize=(15, 5))
plt.plot(times, l_chan)
plt.title('Left Channel')
plt.ylabel('Signal Value')
plt.xlabel('Time (s)')
plt.xlim(0, t_wav)

# plot left channel in frequency space
plt.figure(figsize=(15, 5))
plt.specgram(l_chan, Fs=samp_freq, vmin=-20, vmax=10)
plt.title('Left Channel')
plt.ylabel('Frequency (Hz)')
plt.xlabel('Time (s)')
plt.xlim(0, t_wav)
plt.colorbar()
plt.show()
assert 0
