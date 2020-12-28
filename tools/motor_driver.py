#!/usr/bin/python
# ESC Motor test script

import RPi.GPIO as GPIO
import time
import numpy as np


GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

p = GPIO.PWM(18, 50)
p.start(5)
try:
    while True:
        i = float(input())
        print(i)
        p.ChangeDutyCycle(i)
except KeyboardInterrupt:
    pass

p.stop()
GPIO.cleanup()


