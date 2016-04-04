import serial # import Serial Library
import numpy # Import numpy
import matplotlib.pyplot as plt # import matplot library
from drawnow import *
plt.ion() #matplotlib  interactive mode of plotting data

tempC = []
pressure = []
cnt = 0


arduinoData = serial.Serial('com3', 115200)

def makeFig():
    plt.ylim(20, 35)# prevent y axis from re-scaling
    plt.title('My Live Streaming Sensor Data')
    plt.grid(True)
    plt.ylabel('TempC')
    plt.plot(tempC, 'ro-', label='Degrees C')
    plt.legend(loc='upper left')
    #Second y axis
    plt2=plt.twinx()
    plt.ylim(85000, 95000)
    plt2.plot(pressure, 'b^-')


while True: #while loop that alwais loops
    while (arduinoData.inWaiting()==0):# doesn't do anything unless there's data
        pass #do nothing
    # Here is our data
    arduinoString = arduinoData.readline()
    #print arduinoString

    dataArray = arduinoString.split(',')

    temp = float(dataArray[0]) # temperature in C
    P    = float(dataArray[1]) # pressure in Pa
    #print temp, " , ", P
    tempC.append(temp)
    pressure.append(P)
    #print tempC
    drawnow(makeFig)
    plt.pause(.000001)# otherwise drawnow glitches
    cnt=cnt+1
    if(cnt > 50):
        tempC.pop(0) # pop out first elements
        pressure.pop(0)
