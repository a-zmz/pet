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
    ser = serial.Serial('/dev/ttyUSB0', 9600)
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

            # find dominant frequency, i.e., the highest amplitude
            dom_frequency = freq_l[np.argmax(fft_l)]

            # this is the frequency you determined with the recorded audio file
            target_frequency = 500

            if dom_frequency > target_frequency:
                # Send intructions to the robot
                message = b'o' # turn on the LED               
                ser.write(message)

    except KeyboardInterrupt:
        # Close the stream and socket when interrupted
        stream.stop_stream()
        stream.close()
        ser.close()

if __name__ == '__main__':
    detect_whistling()
