/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/AnalogInput

 */
#include <Adafruit_BMP085.h>
#include <Wire.h>

int sensorPin = A0;    // select the input pin for the potentiometer
//int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
float sensorVoltage=0.0;
float pressure = 0.0; //pressure in kPa

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
    if (bmp.begin())
  {
    // The sensor is detected. Lets carry on!
    Serial.println("Device detected");
  }
    else
  {
    Serial.println("Device NOT detected");
  }
  // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  sensorVoltage = fmap(sensorValue, 0, 1023, 0.0091, 5);//adjusted 1140 to the readings of bmp
  pressure = 1000*(sensorValue/2.421 + 3.478);//pressure in Pa
  float pressureNew = 1000*((sensorVoltage*200)/2.421 + 3.478);
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);
  Serial.print("Sensor voltage: ");
  Serial.println(sensorVoltage);
  //Serial.print("Pressure (Pa): ");
  //Serial.println(pressure);
  Serial.print("Pressure (Pa): ");
  Serial.println(pressureNew);
  float pressureBMP = bmp.readPressure();
  Serial.print("Pressure atm (Pa): ");
  Serial.println(pressureBMP);
  Serial.println("******************");
  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(1000);
  
  // turn the ledPin off:
  //digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  //delay(sensorValue);
}


float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
