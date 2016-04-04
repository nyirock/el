#include "Wire.h"
#include "Adafruit_BMP085.h"
#include <LiquidCrystal.h>
#include <BH1750FVI.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

BH1750FVI LightSensor;

Adafruit_BMP085 mySensor; // Create a pressure sensor called mySensor

float tempC;// variable to hold the temperature reading
float tempF;
float pressurePa; //variable to hold the barometric pressure in Pa

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start the serial monitor

  mySensor.begin();//initialize mySensor
  LightSensor.begin();

  lcd.begin(16, 2);

  LightSensor.SetAddress(Device_Address_H);

  LightSensor.SetMode(Continuous_H_resolution_Mode);
  
  Serial.println("Running...");
}

void loop() {
  // put your main code here, to run repeatedly:
  String msg1="T:";
  String msg2="P:";
  String msg3="L:";
  tempC = mySensor.readTemperature();//read temperature in C
  //msg1 += tempC;
  //msg1+="C;";
  
  
  tempF = tempC*1.8 + 32.; //convert temp to F

  pressurePa = mySensor.readPressure();// read pressure
  msg2 += pressurePa;
  msg2+=" Pa";
 

  Serial.print(tempC);
  
  
  Serial.print(" , ");
  
  Serial.println(pressurePa);

  uint16_t lux = LightSensor.GetLightIntensity();// Get Lux value
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println("lux");

  msg3 +=lux;
  msg3+= "lux";

  lcd.setCursor(0, 0);
  lcd.print(msg1);
  lcd.print(tempC,1);
  lcd.print("C");
  lcd.setCursor(8, 0);
  lcd.print(msg3);
  lcd.setCursor(1,1);
  lcd.print(msg2);
  


  delay(1000);

  //lcd.clear();
  


}
