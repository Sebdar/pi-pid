#!/usr/bin/python
# Incremental encoder test

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

pin_a = 17
pin_b = 27
pin_zero = 22

GPIO.setup(pin_a, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(pin_b, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(pin_zero, GPIO.IN, pull_up_down=GPIO.PUD_UP)

a = False

class Counter:
	def __init__(self, a, b):
		self.pin_a = a
		self.pin_b = b
		self.counter = 0
		self.state_a = GPIO.input(a)
		self.state_b = GPIO.input(b)
		self.state = 0
	
	def __call__(self, pin):
		old_a = self.state_a
		old_b = self.state_b
		if pin == self.pin_a:
			self.state_a = GPIO.input(pin)
		elif pin == self.pin_b:
			self.state_b = GPIO.input(pin)
		
		if self.state == 0:
			# A rising
			if old_a == GPIO.LOW and self.state_a == GPIO.HIGH:
				self.state = 1

			# B rising
			elif old_b == GPIO.LOW and self.state_b == GPIO.HIGH:
				self.state = 3
				self.counter -= 1
				print(self.counter)
		elif self.state == 1:
			# B rising
			if old_b == GPIO.LOW and self.state_b == GPIO.HIGH:
				self.state = 2
			
			# A falling
			elif old_a == GPIO.HIGH and self.state_a == GPIO.LOW:
				self.state = 0
		elif self.state == 2:
			# A falling
			if old_a == GPIO.HIGH and self.state_a == GPIO.LOW:
				self.state = 3
			
			# B falling
			elif old_b == GPIO.HIGH and self.state_b == GPIO.LOW:
				self.state = 1
		elif self.state == 3:
			# B falling
			if old_b == GPIO.HIGH and self.state_b == GPIO.LOW:
				self.state = 0
				self.counter += 1
				print(self.counter)
			
			# A rising
			elif old_a == GPIO.LOW and self.state_a == GPIO.HIGH:
				self.state = 2


counter = Counter(pin_a, pin_b)

GPIO.add_event_detect(pin_a, GPIO.BOTH, callback=counter)
GPIO.add_event_detect(pin_b, GPIO.BOTH, callback=counter)

# Wait for user input
input()
