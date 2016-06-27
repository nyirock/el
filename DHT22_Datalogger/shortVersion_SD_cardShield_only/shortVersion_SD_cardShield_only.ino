#include "RTClib.h"

//#include "DHT.h"
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

RTC_DS1307 rtc;
DateTime now;
int ID = 1;
int h = 3, m = 37, s = 0;
/*DHT sensor(2, DHT22);

int ID = 1;
int h = 19, m = 00, s = 0; // set the start time in 24-hr clock
float temp, Rh;
*/
const int chipSelect = 10;


void setup()
{
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  delay(500);
  SD.begin(chipSelect);
  PrintHeader();
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

}

void PrintHeader() // prints header to SD card
{
   File datafile = SD.open("berg.csv", FILE_WRITE);
   if (datafile)
   {
      String header = "ID, Date, Time, Temperature (C), Humidity (%)";
      datafile.println(header);
      datafile.close();
   }
}



void loop()
{
    now = rtc.now();
    /*Serial.print(",");
          Serial.print(now.hour());
          Serial.print(":");
          Serial.print(now.minute());
          Serial.print(":");
          Serial.println(now.second());*/
    if(s>=60)
    {
      s = s-60;  //reset s (seconds) to 0 after one minute or more has passed
      m++;  // add one minute after 60 seconds have passed
    }
    if(m>=60)
    {
      m = m-60;  //reset m (minutes) to 0 after one hour or more has passed
    }
    if(h>=24)
    {
      h = h-24;  //if time interval is greater than one hour
    }
    if(now.hour()==h+1 || now.hour()==0)
    {
      h = now.hour();  //change value of h to actual hour after one hour or one day
    }
    
    if(now.hour()==h && now.minute()==m && now.second()==s)
    {
      //GetData();
      //ConvertToF();
      PrintToSD();
      Serial.print(ID);
          Serial.print(",");
          Serial.print(now.month());
          Serial.print("/");
          Serial.print(now.day());
          Serial.print("/");
          Serial.print(now.year());
          Serial.print(",");
          Serial.print(h);
          Serial.print(":");
          Serial.print(m);
          Serial.print(":");
          Serial.print(s);
          Serial.print(",");
          Serial.print(now.hour());
          Serial.print("/");
          Serial.print(now.minute());
          Serial.print("/");
          Serial.print(now.second());
          /*
          datafile.print(",");
          datafile.print(temp, 3); // printing temperature up to 3 decimal places
          datafile.print(",");
          datafile.print(Rh, 3); // printing Rh up to 3 decimal places
          */
          Serial.println();
      s = s + 10; // for 10 seconds intervals
      //m++; // for one min intervals
      //m = m+5; //for 5 min intervals
      //h = h++;
      ID++;
    }
}

/*
void GetData() // this function will get the sensor data with an Onset HOBO U12
{
  temp = sensor.readTemperature();
  Rh = sensor.readHumidity();
  //temp = 1.0073 * temp; // sensor calibration with HOBO U12
  //Rh = 0.8218 * Rh;
  //temp = 1.0078 * temp; // sensor calibration with HOBO U12
  //Rh = 0.9356 * Rh;
}

void ConvertToF() // this function will convert temp values from degree Celsius to degree Fahrenheit
{
  float temp_f = (1.8 * temp) + 32;
  temp = temp_f;
}
*/

void PrintToSD()  // this function saves the data to the SD card
{   
        File datafile = SD.open("berg.csv", FILE_WRITE);
        if(datafile)
        {
          datafile.print(ID);
          datafile.print(",");
          datafile.print(now.month());
          datafile.print("/");
          datafile.print(now.day());
          datafile.print("/");
          datafile.print(now.year());
          datafile.print(",");
          datafile.print(h);
          datafile.print(":");
          datafile.print(m);
          datafile.print(":");
          datafile.print(s);
          datafile.print(",");
          datafile.print(now.hour());
          datafile.print("/");
          datafile.print(now.minute());
          datafile.print("/");
          datafile.print(now.second());
          /*
          datafile.print(",");
          datafile.print(temp, 3); // printing temperature up to 3 decimal places
          datafile.print(",");
          datafile.print(Rh, 3); // printing Rh up to 3 decimal places
          */
          datafile.println();
          datafile.close();
        }
        else
          Serial.println("SD card error.");
}
