#include "Wire.h"
#include "Adafruit_BMP085.h"
#include <LiquidCrystal.h>
#include <BH1750FVI.h>
#include <SparkFunTSL2561.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

BH1750FVI LightSensor;
SFE_TSL2561 light;

Adafruit_BMP085 mySensor; // Create a pressure sensor called mySensor

boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds

float tempC;// variable to hold the temperature reading
float tempF;
float pressurePa; //variable to hold the barometric pressure in Pa

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start the serial monitor

  mySensor.begin();//initialize mySensor
  LightSensor.begin();
  light.begin();
  gain = 0;
  unsigned char time = 2;
  light.setTiming(gain,time,ms);
  light.setPowerUp();
  

  lcd.begin(16, 2);

  LightSensor.SetAddress(Device_Address_H);

  LightSensor.SetMode(Continuous_H_resolution_Mode);
  
  Serial.println("Running...");
}

void loop() {
  double lux; 
  // put your main code here, to run repeatedly:
  String msg1="T:";
  String msg2="P:";
  String msg3="L1:";
  String msg4 = "L2:";
  tempC = mySensor.readTemperature();//read temperature in C
  //msg1 += tempC;
  //msg1+="C;";
  
  
  tempF = tempC*1.8 + 32.; //convert temp to F

  pressurePa = mySensor.readPressure();// read pressure
  msg2 += pressurePa;
  msg2+=" Pa";

  unsigned int data0, data1;
   if (light.getData(data0,data1))
  {
    // getData() returned true, communication was successful
    
    Serial.print("data0: ");
    Serial.print(data0);
    Serial.print(" data1: ");
    Serial.print(data1);
  
    // To calculate lux, pass all your settings and readings
    // to the getLux() function.
    
    // The getLux() function will return 1 if the calculation
    // was successful, or 0 if one or both of the sensors was
    // saturated (too much light). If this happens, you can
    // reduce the integration time and/or gain.
    // For more information see the hookup guide at: https://learn.sparkfun.com/tutorials/getting-started-with-the-tsl2561-luminosity-sensor
  
   // Resulting lux value
    boolean good;  // True if neither sensor is saturated
    
    // Perform lux calculation:

    good = light.getLux(gain,ms,data0,data1,lux);
    Serial.print(" lux: ");
    Serial.print(lux);
        if (good) Serial.println(" (good)"); else Serial.println(" (BAD)");
  }
  Serial.print(tempC);
  
  
  Serial.print(" , ");
  
  Serial.println(pressurePa);

  uint16_t lx = LightSensor.GetLightIntensity();// Get Lux value
  Serial.print("Light: ");
  Serial.print(lx);
  Serial.println("lux");

  msg3 +=lx;
  msg3+= "lux";
  
  msg4+="lux";

  lcd.setCursor(0, 0);
  lcd.print("1:");
  lcd.print(lux,0);
  if((lux)<10){
      lcd.setCursor(3,0);
      lcd.print("   ");
    }
  else if((lux/100)<1){
      lcd.setCursor(4,0);
      lcd.print("  ");
    }
  else if((lux/1000)<1){
      lcd.setCursor(5,0);
      lcd.print(" ");
    }



  lcd.setCursor(6, 0);
  lcd.print("lux");

  lcd.setCursor(10, 0);
  lcd.print("2:");
  lcd.print(lx);
  
  if((lux)<10){
      lcd.setCursor(13,0);
      lcd.print("   ");
    }
  else if((lux/100)<1){
      lcd.setCursor(14,0);
      lcd.print("  ");
    }
  else if((lux/1000)<1){
      lcd.setCursor(15,0);
      lcd.print(" ");
    }
  

  //lcd.print("l");
  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(pressurePa, 0);
  lcd.print("Pa");
    
  lcd.setCursor(10,1);
  lcd.print("T:");
  lcd.print(tempC,1);
  /*lcd.print("C");*/
  


  delay(1000);

  //lcd.clear();
  


}
