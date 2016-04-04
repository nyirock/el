#include <SPI.h>
#include <SD.h>

#include "Wire.h"
#include "Adafruit_BMP085.h"

Adafruit_BMP085 mySensor; // Create a pressure sensor called mySensor

float tempC;// variable to hold the temperature reading
float tempF;
float pressurePa; //variable to hold the barometric pressure in Pa
File myFile;

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 8;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  mySensor.begin();//initialize mySensor
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  //Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // The chipSelect pin you use should also be set to output
  pinMode(chipSelect, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  //Serial.println("card initialized.");
}

void loop()
{
  tempC = mySensor.readTemperature();//read temperature in C
  tempF = tempC*1.8 + 32.; //convert temp to F

  pressurePa = mySensor.readPressure();// read pressure
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  /*for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }*/
  dataString=String(tempC)+","+String(pressurePa)+","+String(millis());

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    //Serial.println("error opening datalog.txt");
  }

  delay(1000);
}
