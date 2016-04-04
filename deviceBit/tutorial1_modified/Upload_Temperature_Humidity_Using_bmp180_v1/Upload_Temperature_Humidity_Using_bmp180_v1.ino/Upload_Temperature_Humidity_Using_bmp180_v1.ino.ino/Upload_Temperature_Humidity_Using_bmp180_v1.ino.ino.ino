/*
   Devicebit open platform sensor client
   This code is in the public domain.
  */
 
#include <DeviceBitHttpClient.h>
//#include <SPI.h>
#include <Ethernet.h>
//#include <SHT1x.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Specify data and clock connections and instantiate SHT1x object
 
//put your api key here,find it in devicebit.com->my account->account setting
#define DB_USERKEY "8b27536c84e148fd8d6bc89aa3d3cf25"
//put your gateway number here,01 as default
#define DB_GATEWAY "01"

Adafruit_BMP085 bmp;

//delay between updates
#define POST_INTERVAL (30*1000)
 
DeviceBitHttpClient *dbc;
 
 
void setup() {
   // start serial port:
   Serial.begin(9600);
   // hope no exception here
   dbc = new DeviceBitHttpClient(DB_USERKEY, DB_GATEWAY);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
 }
 
void loop() {
   // read the analog sensor:
   //int sensorReading = analogRead(A0);  
 
  // if there's incoming data from the net connection.
   // send it out the serial port.  This is for debugging
   // purposes only:
 
  if (dbc) {
    Serial.println("read data ");
    
    float temp_c;
    
    float pressure;
    
    // Read values from the sensor
    temp_c = bmp.readTemperature();
    //temp_f = sht1x.readTemperatureF();
    pressure = bmp.readPressure();
    //t1,t2.. must using the same name setting on web server.
    //Serial.print("*** data send ***");
    dbc->appendSensorValue("tem", temp_c);
    dbc->sendSensorValue("pres", pressure);
    Serial.println("*** send completed ***");
 
   delay(POST_INTERVAL);
   }
 }
