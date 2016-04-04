import serial # import Serial Library
import numpy # Import numpy
import matplotlib.pyplot as plt # import matplot library
from drawnow import *
plt.ion() #matplotlib  interactive mode of plotting data

tempC = []
pressure = []
cnt = 0
avgWindowTemp=20
avgWindowPressure=90000


arduinoData = serial.Serial('com3', 115200)

def makeFig():
    plt.ylim(avgWindowTemp-avgWindowTemp*0.01, avgWindowTemp+avgWindowTemp*0.01)# prevent y axis from re-scaling
    plt.title('My Live Streaming Sensor Data')
    #plt.grid(True) #now grid corresponds to pressure
    plt.ylabel('TempC')
    plt.plot(tempC, 'ro-', label='Degrees C')
    plt.legend(loc='upper left')
    #Second y axis
    plt2=plt.twinx()
    plt.ylim(avgWindowPressure-avgWindowPressure*0.001, avgWindowPressure+avgWindowPressure*0.0005)
    #lets do one fixed pressure scale
    #plt.ylim(88490, 88502)
    plt2.plot(pressure, 'b^-', label='Pressure (Pa)')
    plt.grid(True)
    plt.ylabel('Pressure (Pa)') # naming the other axis
    plt2.legend(loc='upper right')
    plt2.ticklabel_format(useOffset=False) #removing exponential formatting of the axis data (was already normal for me)


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
    avgWindowTemp=sum(tempC)/len(tempC)
    avgWindowPressure=sum(pressure)/len(pressure)
