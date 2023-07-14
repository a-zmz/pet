#! /bin/sh

set -eu

# notify if more than one argument is passed
if [ "$#" -ne 1 ]; then
  echo "> Usage: $0 DIRECTORY, do not pass more than one directory." >&2
  exit 1
else
    echo "> Start compiling & uploading $1"
fi

# check if direcory exists
if ! [ -e "$1" ]; then
  echo "> $1 not found" >&2
  exit 1
fi

# check if argument is a directory
if ! [ -d "$1" ]; then
  echo "> $1 not a directory" >&2
  exit 1
fi

# compile
arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old $1

# upload to arduino nano
arduino-cli upload -p /dev/ttyUSB0 -v --fqbn arduino:avr:nano:cpu=atmega328old $1

echo "> $1 compiled & uploaded."
