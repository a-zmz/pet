import time

import os

import wave
import pyaudio

from picamera2 import Picamera2
from picamera2.encoders import H264Encoder

from libcamera import Transform

# TODO audio & video are not in sync

# Audio settings
audio_format = pyaudio.paInt16
channels = 2
sample_rate = 44100
chunk = 1024
record_seconds = 5

# Video settings
video_resolution = (640, 480)
video_file = 'video.h264'

def record_audio():
    audio = pyaudio.PyAudio()
    stream = audio.open(format=audio_format,
                        channels=channels,
                        rate=sample_rate,
                        input=True,
                        frames_per_buffer=chunk)

    frames = []
    for _ in range(0, int(sample_rate / chunk * record_seconds)):
        data = stream.read(chunk)
        frames.append(data)

    stream.stop_stream()
    stream.close()
    audio.terminate()

    wave_file = wave.open('audio.wav', 'wb')
    wave_file.setnchannels(channels)
    wave_file.setsampwidth(audio.get_sample_size(audio_format))
    wave_file.setframerate(sample_rate)
    wave_file.writeframes(b''.join(frames))
    wave_file.close()


def record_video():
    picam2 = Picamera2()
    video_config = picam2.create_video_configuration(transform=Transform(vflip=1))
    picam2.configure(video_config)

    encoder = H264Encoder(10000000)

    picam2.start_recording(encoder, video_file)
    time.sleep(record_seconds)
    picam2.stop_recording()


def combine_audio_video():
    output_file = 'output.mp4'
    os.system(f'ffmpeg -i {video_file} -i audio.wav -c:v copy -c:a aac -strict experimental {output_file}')
    os.remove(video_file)
    os.remove('audio.wav')

if __name__ == '__main__':
    record_audio()
    record_video()
    combine_audio_video()

