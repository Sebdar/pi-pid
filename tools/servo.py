#!/usr/bin/python
# Servo / PWM test script

import RPi.GPIO as GPIO
import time
import numpy as np

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

p = GPIO.PWM(18, 50)

p.start(0.05)
while True:
    for i in np.linspace(5, 10, 50):
        print(i)
        p.ChangeDutyCycle(i)
        time.sleep(0.2)

    time.sleep(0.4)


