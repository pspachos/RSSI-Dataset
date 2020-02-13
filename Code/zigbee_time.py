import serial
import sys
import os
import datetime

ser = serial.Serial('COM29')

file = open(sys.argv[1], 'w')

while True:
    try:
        line = ser.readline()
        new = line.split('\r\n')
        new[0] = new[0] + ',' + str(datetime.datetime.now()) + '\n'
        file.write(new[0])
        print new[0]
    except Exception as e:
        print e
file.close()
ser.close()
