from socket import timeout
from time import sleep
import serial
import csv
import _thread
from datetime import datetime


def save_to_csv(tab):
    file = open("pomiary.csv", 'a')
    for i in range (0, len(tab)):
        file.write(str(tab[i]))
        if i == len(tab)-1:
            pass
        else:
            file.write(',')
    file.write('\n')
    file.close()

pomiary = []

port = "COM3"
ser = serial.Serial(port="COM3",baudrate=115200,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=10)
while True:
        data = ser.readline()
        data_sensor = data.decode('utf8')
        data_sensor = data_sensor.strip()
        data_sensor = data_sensor.strip('\n')
        if data_sensor != "git":
            # data_sensor = data_sensor[:-1]
            print(data_sensor)
            pomiary.append(data_sensor)
        elif data_sensor == "git":
            save_to_csv(pomiary)
            print(pomiary)
            pomiary.clear()

        # print(data_sensor)
        # writer = csv.writer(f)
        # writer.writerow(data_sensor)
            
            

