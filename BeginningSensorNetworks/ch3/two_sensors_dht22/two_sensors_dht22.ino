/*
  Sensor Networks Example Arduino Hosted Sensor Node

  This sensor node uses a DHT22 sensor to read temperature and humidity
  printing the results in the serial monitor.

*/
#include <SPI.h>
#include <DHT22.h>

#define DHT22_PIN 7       // DHT2 data is on pin 7
#define DHT22_PIN2 8

#define read_delay 5000   // 5 seconds 

DHT22 myDHT22(DHT22_PIN); // DHT22 instance
DHT22 myDHT22_second(DHT22_PIN2);

void read_data(DHT22 sensor, int Flag) {
  DHT22_ERROR_t errorCode;
  
  errorCode = sensor.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      char buf[128];
      int h;
      //manual adjustment of humidity values: empirical
      h = sensor.getHumidityInt();
      if (Flag == 1)
        h = h *1.023; //empirically adjusted 4.7 Ohm Resistor
      if (Flag == 2)
        h = h* 0.977;//empirically adjusted 4.7 Ohm Resistor
      sprintf(buf, "%hi.%01hi, %i.%01i",
              sensor.getTemperatureCInt()/10,
              abs(sensor.getTemperatureCInt()%10),
              h/10,
              h%10);
      Serial.print("Data read:");
      Serial.println(buf);
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.print("check sum error ");
      Serial.print(sensor.getTemperatureC());
      Serial.print("C ");
      Serial.print(sensor.getHumidity());
      Serial.println("%");
      break;
    case DHT_BUS_HUNG:
      Serial.println("BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
      Serial.println("Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      Serial.println("ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      Serial.println("Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      Serial.println("Data Timeout ");
      break;
    case DHT_ERROR_TOOQUICK:
      Serial.println("Polled too quick ");
      break;
  }
}

void setup() {  
  Serial.begin(115200);  // Set the serial port speed
}

void loop() {  
  delay(read_delay);
  read_data(myDHT22,1);
  read_data(myDHT22_second,2);
}

