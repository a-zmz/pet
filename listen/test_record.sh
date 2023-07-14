#! /bin/sh

# run this with sudo
# record audio with device (-D) plugin hardware card 1 (plughw:1), 2 channels (-c2),
# at 48000 sampling rate (-r 48000), in format 32 bit signed integer audio format in little-endian
# byte order (-f S32_LE), file type being .wav (-t wav), volume unit meter type is
# stereo (-V stereo), and run this command verbosely (-v); file saved at
# '~/Sounds/test_stereo.wav'
arecord -D plughw:1 -c2 -r 48000 -f S32_LE -t wav -V stereo -v /home/amz/Sounds/test.wav
