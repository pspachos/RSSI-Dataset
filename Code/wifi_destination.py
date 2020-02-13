# Echo server program
import socket
import os
import subprocess
import time
import time
import re
import sys
import datetime

file = open(sys.argv[1], 'w')

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 2000              # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
conn, addr = s.accept()
#print 'Connected by', addr
while 1:
    data = conn.recv(1024)
    new = data.split('\r\n')
    new[0] = new[0] + ',' + str(datetime.datetime.now()) + '\n'
    file.write(new[0])
    print new[0]
conn.close()
file.close()
