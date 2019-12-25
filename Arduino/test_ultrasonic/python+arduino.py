import serial

global dat

ser = serial.Serial('/dev/ttyACM0', 9600)

ime_dat = 'data'
dat = open(ime_dat, 'w')

flag = 1

while(flag) :
    arduinoValue = ser.readline()
    t = arduinoValue.decode()
    # print(t)
    t = str(t)
    dat.write(t)
        
dat.close()

