# Incremental encoder test

import RPi.GPIO

GPIO.setmode(GPIO.BCM)

pin_a = 17
pin_b = 27
pin_zero = 22

GPIO.setup(pin_a, GPIO.in, pull_up_down=GPIO.PUD_UP)
GPIO.setup(pin_b, GPIO.in, pull_up_down=GPIO.PUD_UP)
GPIO.setup(pin_zero, GPIO.in, pull_up_down=GPIO.PUD_UP)

a = False

def a_rising():
	print("A rising")
	a = True

def a_falling():
	print("A falling")
	a = False

def b_rising():
	print("B rising")
	b = True

def b_falling():
	print("B falling")
	b = False


GPIO.add_event_detect(pin_a, GPIO.RISING, callback=a_rising)
GPIO.add_event_detect(pin_a, GPIO.FALLING, callback=a_falling)
GPIO.add_event_detect(pin_b, GPIO.RISING, callback=b_rising)
GPIO.add_event_detect(pin_b, GPIO.FALLING, callback=b_falling)

# Wait for user input
input()
