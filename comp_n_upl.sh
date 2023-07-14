#! /bin/sh

set -eu

# compile
arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old $1

# upload to arduino nano
arduino-cli upload -p /dev/ttyUSB0 -v --fqbn arduino:avr:nano:cpu=atmega328old $1

echo "> $1 compiled & uploaded."
