import i2comm
import time

# This is the address we setup in the Arduino Program
address = 4

def writeNumber(value):
	i2comm.i2csend(0x0A, [1, 2])
	return -1

while True:
	var = input("Enter number (long): ")
	if not var:
		continue

	writeNumber(var)
	print "RPI: Hi Arduino, I sent you ", var

	# number = i2comm.i2crecv()
	# print "Arduino: Hey RPI, I received a digit ", number
