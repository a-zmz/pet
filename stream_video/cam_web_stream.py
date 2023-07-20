#! /usr/bin/python3

# Mostly copied from https://picamera.readthedocs.io/en/release-1.13/recipes2.html
# Run this script, then point a web browser at http:<this-ip-address>:8000
# Note: needs simplejpeg to be installed (pip3 install simplejpeg).

import time
import io
import logging
import socketserver
from http import server
from threading import Condition
import cv2
import numpy as np

from picamera2 import Picamera2
from picamera2.encoders import JpegEncoder
from picamera2.outputs import FileOutput

import serial

PAGE = """\
<html>
<head>
<title>pet video streaming demo</title>
</head>
<body>
<h1>Pet Video Streaming Demo</h1>
<img src="stream.mjpg" width="960" height="720" />
</body>
</html>
"""

# Configure serial port
ser = serial.Serial()
ser.baudrate = 19200
ser.port = '/dev/ttyUSB0'

# Open serial port
try:
    ser.open()
except:
    ser.close()
    ser.open()

time.sleep(2.00) # Wait for connection before sending any data


class StreamingOutput(io.BufferedIOBase):
    def __init__(self):
        self.frame = None
        self.condition = Condition()

    def write(self, buf):
        with self.condition:
            self.frame = buf
            self.condition.notify_all()


class StreamingHandler(server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(301)
            self.send_header('Location', '/index.html')
            self.end_headers()
        elif self.path == '/index.html':
            content = PAGE.encode('utf-8')
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.send_header('Content-Length', len(content))
            self.end_headers()
            self.wfile.write(content)
        elif self.path == '/stream.mjpg':
            self.send_response(200)
            self.send_header('Age', 0)
            self.send_header('Cache-Control', 'no-cache, private')
            self.send_header('Pragma', 'no-cache')
            self.send_header('Content-Type', 'multipart/x-mixed-replace; boundary=FRAME')
            self.end_headers()
            try:
                while True:
                    with output.condition:
                        output.condition.wait()
                        frame = output.frame

                        ### The image is encoded in bytes,
                        ### needs to be converted to e.g. numpy array
                        frame = cv2.imdecode(np.frombuffer(frame, dtype=np.uint8),
                                             cv2.IMREAD_COLOR)
                        
                        ################
                        # HERE GOES ALL IMAGE PROCESSING
                        ################

                        # vertical flip
                        frame = frame[::-1].copy()
                        # load this frame into cv2 as grayscale
                        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

                        # initiate cascade classifier
                        det = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
                        # get face rectangle
                        rects = det.detectMultiScale(
                            gray,
                            scaleFactor=1.1,
                            minNeighbors=5,
                            minSize=(80, 80), # min size of face
                            flags=cv2.CASCADE_SCALE_IMAGE,
                         )

                        if len(rects) > 0:
                            # buzz
                            ser.write(b'buzz\n')
                            # green light, got face
                            ser.write(b'green_blink\n')
                            # go forward
                            ser.write(b'forward\n')

                            for (x, y, w, h) in rects:
                                # draw rectangle on the frame
                                cv2.rectangle(
                                    frame,
                                    (x, y),
                                    (x + w, y + h),
                                    (0, 255, 0), # green
                                    20, # line thickness
                                )
                        else:
                            # go forward
                            ser.write(b'stop\n')

                    # and now we convert it back to JPEG to stream it
                    _, frame = cv2.imencode('.JPEG', frame) 

                    self.wfile.write(b'--FRAME\r\n')
                    self.send_header('Content-Type', 'image/jpeg')
                    self.send_header('Content-Length', len(frame))
                    self.end_headers()
                    self.wfile.write(frame)
                    self.wfile.write(b'\r\n')
            except Exception as e:
                logging.warning(
                    'Removed streaming client %s: %s',
                    self.client_address, str(e))
        else:
            self.send_error(404)
            self.end_headers()


class StreamingServer(socketserver.ThreadingMixIn, server.HTTPServer):
    allow_reuse_address = True
    daemon_threads = True


picam2 = Picamera2()
picam2.configure(picam2.create_video_configuration(main={"size": (960, 720)}))
output = StreamingOutput()
picam2.start_recording(JpegEncoder(), FileOutput(output))

# turn on red light, on air
ser.write(b'red_on\n')

try:
    address = ('', 8000)
    server = StreamingServer(address, StreamingHandler)
    server.serve_forever()
except KeyboardInterrupt:
    # turn off red light
    ser.write(b'red_off\n')
    # stop
    ser.write(b'stop\n')
    ser.close()

finally:
    picam2.stop_recording()

ser.close()
