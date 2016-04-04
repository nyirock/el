#include <SD.h>
#include "Wire.h"
#include "Adafruit_BMP085.h"

Adafruit_BMP085 mySensor; // Create a pressure sensor called mySensor

float tempC;// variable to hold the temperature reading
float tempF;
float pressurePa; //variable to hold the barometric pressure in Pa
File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Start the serial monitor

  mySensor.begin();//initialize mySensor

  Serial.println("Initializing the SD card...");
  if(!SD.begin(10))
    {
      Serial.println("Initialization failed!!!");
      return;
    }
    Serial.println("Initialization complete");

}

void loop() {

  
  // put your main code here, to run repeatedly:
  tempC = mySensor.readTemperature();//read temperature in C
  tempF = tempC*1.8 + 32.; //convert temp to F

  pressurePa = mySensor.readPressure();// read pressure

  myFile = SD.open("test.csv", FILE_WRITE);

  if(myFile)
  {
    myFile.print(tempC);  
    Serial.print(tempC);

    myFile.print(",");
    Serial.print(",");

    myFile.print(pressurePa);
    Serial.print(pressurePa);

    myFile.print(",");
    Serial.print(",");

    myFile.println(millis());
    Serial.println(millis());

    myFile.close();
  }

  else
  {
    Serial.print("Serial output only: ");
    Serial.print(tempC);
    Serial.print(" , ");
    Serial.println(pressurePa);
  }
  



  delay(1000);

}
