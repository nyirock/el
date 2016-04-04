#include "Wire.h"
#include "Adafruit_BMP085.h"

Adafruit_BMP085 mySensor; // Create a pressure sensor called mySensor

float tempC;// variable to hold the temperature reading
float tempF;
float pressurePa; //variable to hold the barometric pressure in Pa

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start the serial monitor

  mySensor.begin();//initialize mySensor

}

void loop() {
  // put your main code here, to run repeatedly:
  tempC = mySensor.readTemperature();//read temperature in C
  tempF = tempC*1.8 + 32.; //convert temp to F

  pressurePa = mySensor.readPressure();// read pressure

  Serial.print(tempC);
  Serial.print(" , ");
  Serial.println(pressurePa);


  delay(250);

}
