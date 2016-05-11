import socket
import sys
import os

UDP_IP = "HappyHatch.byod.gmu.edu" 
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP,UDP_PORT))

while(1):
	data, addr = sock.recvfrom(1024)
	print "Sent Command: ", data
	os.system("python SendWheel.py " + data )