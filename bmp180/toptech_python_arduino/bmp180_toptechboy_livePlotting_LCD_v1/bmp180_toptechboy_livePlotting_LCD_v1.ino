#include "Wire.h"
#include "Adafruit_BMP085.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Adafruit_BMP085 mySensor; // Create a pressure sensor called mySensor

float tempC;// variable to hold the temperature reading
float tempF;
float pressurePa; //variable to hold the barometric pressure in Pa

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start the serial monitor

  mySensor.begin();//initialize mySensor

  lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:
  String msg1="Temp: ";
  String msg2="Pressure: ";
  tempC = mySensor.readTemperature();//read temperature in C
  msg1 += tempC;
  
  
  tempF = tempC*1.8 + 32.; //convert temp to F

  pressurePa = mySensor.readPressure();// read pressure
  msg2 += pressurePa;
 

  Serial.print(tempC);
  
  
  Serial.print(" , ");
  
  Serial.println(pressurePa);

  lcd.setCursor(0, 0);
  lcd.print(msg1);
  lcd.setCursor(0,1);
  lcd.print(msg2);
  


  delay(1000);

  //lcd.clear();
  


}
