/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * Please see eeprom_iteration for a more in depth
 * look at how to traverse the EEPROM.
 *
 * This example code is in the public domain.
 */

#include <Wire.h>
#define ADDR 1;


void setup() {

  //Master writes to a slave
  // initialize the LED pin as an output.
  Wire.begin(); //initialize hardware on microcontroller
  // no arguments makes an arduino a master, doesn't need an addres
  Wire.beginTransmission(ADDR);
  Wire.write(2);
  Wire.write(3);
  Wire.endTransmission(stop); //actually sends the data, sends 2 bytes: 2 and 3

  //Master reads from a slave
  int sum=0;
  Wire.requestFrom(ADDR,2);
  while(Wire.available())
    sum+=(int)Wire.read();
  //Wire.requestFrom();
  //Wire.read();

  
}

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}

void loop() {
  /** Empty loop. **/
}
