/*
  Sensor Networks Example Arduino Hosted Sensor Node

  This sensor node uses a DHT22 sensor to read temperature and humidity
  printing the results in the serial monitor.

*/
#include <SPI.h>
#include <Ethernet.h>
#include <sha1.h>
#include "mysql.h"
#include <DHT22.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server_addr(54,215,148,52); //obtained from ping of sql3.freemysqlhosting.net
char user[] = "sql3126451";
char password[] = "thBnly1cdc";

Connector my_conn;        // The Connector/Arduino reference

#define DHT22_PIN 7       // DHT2 data is on pin 7
#define DHT22_PIN2 8

#define read_delay 5000   // 5 seconds 

char q[128];

DHT22 myDHT22(DHT22_PIN); // DHT22 instance
DHT22 myDHT22_second(DHT22_PIN2);

String data1, data2;

String read_data(DHT22 sensor, int Flag) {
  DHT22_ERROR_t errorCode;
  String data="";
  
  errorCode = sensor.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      char buf[20];
      
      int h;
      //manual adjustment of humidity values: empirical
      h = sensor.getHumidityInt();
      if (Flag == 1)
        h = h + 17; //empirically adjusted for both 
        //lowering addition term from 18 to 16/15/14
      if (Flag == 2)
        h = h - 18;//empirically adjusted lowered to 17
        
      sprintf(buf, "%hi.%01hi, %i.%01i",
              sensor.getTemperatureCInt()/10,
              abs(sensor.getTemperatureCInt()%10),
              h/10,
              h%10);
      data = String(buf);

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
  return data;
}

void setup() {  
  Ethernet.begin(mac_addr);
  Serial.begin(115200);  // Set the serial port speed
  delay(1000);
  Serial.println("Connecting...");
  if (my_conn.mysql_connect(server_addr , 3306, user, password))
    delay(500);
  else
    Serial.println("Connection failed.");
}

void loop() {  
  delay(read_delay);
  data1 = read_data(myDHT22,1);
  data2 = read_data(myDHT22_second,2);
  String query = "INSERT INTO sql3126451.temp_humid_2sensors_timestamp_TST VALUES (NULL, now(),"+data1+","+data2+")";
  query.toCharArray(q, 128);
  my_conn.cmd_query(q);
  Serial.println("Data read and recorded.");
  Serial.println("[Sensor1]: "+data1);
  Serial.println("[Sensor2]: "+data2);
}

