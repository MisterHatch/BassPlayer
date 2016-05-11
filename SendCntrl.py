import serial
import sys

s = serial.Serial('/dev/ttyACM0',9600)

command = str(sys.argv[1])
print command
s.write(command)