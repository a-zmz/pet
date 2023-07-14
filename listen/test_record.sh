#! /bin/sh

# run this with sudo
arecord -D plughw:1 -c2 -r 48000 -f S32_LE -t wav -V stereo -v test_stero.wav
