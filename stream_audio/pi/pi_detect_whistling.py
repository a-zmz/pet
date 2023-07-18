import pyaudio
import numpy as np
from scipy.fft import rfft, rfftfreq
import serial


CHUNK_SIZE = 4096           # Buffer size
FORMAT = pyaudio.paInt16    # Data type
CHANNELS = 2                # Number of channels
RATE = 22050                # Sample rate (Hz)


def detect_whistling():
    # Initialize PyAudio
    audio = pyaudio.PyAudio()

    # Open the audio stream
    stream = audio.open(format=FORMAT,
                        channels=CHANNELS,
                        rate=RATE,
                        input=True,
                        frames_per_buffer=CHUNK_SIZE)

    # Open serial connection to send instructions to the arduino
    ser = serial.Serial('/dev/ttyUSB0', 19200)
    try:
        ser.open()
    except:
        ser.close()
        ser.open()

    try:
        while True:
            # Read audio data from the stream
            raw_data = stream.read(CHUNK_SIZE)

            # Convert raw_data to left and right channel
            interleaved_data = np.frombuffer(raw_data, dtype=np.int16)
            left = interleaved_data[::2] 
            right = interleaved_data[1::2]  

            # calculate Fourier transform
            fft_l = np.fft.rfft(left)
            freq_l = np.fft.rfftfreq(left.size, 1/RATE)
            fft_r = np.fft.rfft(right)
            freq_r = np.fft.rfftfreq(right.size, 1/RATE)

            # filter frequency
            """
            filtered_fft_l = fft_l
            for i, freq in enumerate(freq_l):
                if abs(freq) < 500:
                    filtered_fft_l[i] = 0
            #filtered_l = np.fft.irfft(filtered_fft_l).real
            fil_dom_freq = freq_l[np.argmax(filtered_fft_l)]
            #print(fil_dom_freq)
            """

            # find dominant frequency, i.e., the highest amplitude
            dom_freq = freq_l[np.argmax(fft_l)]
            max_amp = np.max(fft_l)
            print(dom_freq)

            # this is the frequency you determined with the recorded audio file
            freq_thre_lower = 1000
            freq_thre_upper = 5000

            if dom_freq > freq_thre_lower:
                # Send intructions to the robot
                print("> Dominant frequency bigger than threshold")
                ser.write(b'o') # turn on the LED
                ser.write(b'f') # turn on the LED
            else:
                # Send intructions to the robot
                ser.write(b'd') # turn off the LED
                ser.write(b'x') # stop

    except KeyboardInterrupt:
        # Close the stream and socket when interrupted
        ser.write(b'x') # stop
        ser.write(b'd') # turn off the LED
        stream.stop_stream()
        stream.close()
        ser.close()

if __name__ == '__main__':
    detect_whistling()
