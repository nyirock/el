#include <SPI.h>
#include <Ethernet.h>
#include <DeviceBitHttpClient.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Si7021.h>

Si7021 Si;

byte mac[] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31};

IPAddress ip(192, 168, 2, 115);
IPAddress mydns(8, 8, 8, 8);
IPAddress gw(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);
#define LW_USERKEY "###############################"
#define LW_GATEWAY "01"

DeviceBitHttpClient *client;

float temperature, humidity;
long starttime;
int postInterval = 30*1000;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  if (Si.detectSensor())
  {
    // The sensor is detected. Lets carry on!
    Serial.println("Device detected");
  }
  else
  {
    Serial.println("Device NOT detected");
    while (1)
    {
      ;; // The sensor is not detected. Let's just stay here forever.
    }
  }
  //you can use 2 ways to init your network
  //1.simplest
  client = new DeviceBitHttpClient(LW_USERKEY, LW_GATEWAY);
  //2.full setting for your network
  //client = new DeviceBitHttpClient(LW_USERKEY, LW_GATEWAY, mac, ip, mydns, gw, subnet);


  //test1 is the function you write below to handle your program
  //"testFunction" is the function name you set on website:http://www.DeviceBit50.com/
  //on "controll command manager" menu
  //we test transfer 1-5 para from website(you defined on it) to your arduino
  //enjoy it
  /*
  UserFunction uf1(test1,"testFunction");
  client->addUserFunction(uf1);
  UserFunction uf2 (test2,"testFunction2");
  client->addUserFunction(uf2);

  UserFunction uf3 (test3,"testFunction3");
  client->addUserFunction(uf3);
  UserFunction uf4 (test4,"testFunction4");
  client->addUserFunction(uf4);
  UserFunction uf5 (test5,"testFunction5");
  client->addUserFunction(uf5);
  UserFunction uf6 (test6,"testFunction6");
  client->addUserFunction(uf6);


  //3 para means changeFunction,function name defined on web,default state
  UserSwitch us1 (test7,"mySwitch",0);
  client->addUserSwitch(us1);


  enable easySetupMode will open the port 80 of this board,
  you can setup your apikey and gateway number via http://your_arduino_ip/
  the key and number will be burned into board's eeprom
  after set you need to restart your arduino.
  after setup,you can comment this line for fasten your board.
  this library will will use apikey and gateway number in eeprom if you enable easySetupMode .
  you can send empty value from the browser to wipe the data in eeprom.
  */
  client->easySetupMode(true);

}

void loop()
{

  //client->keepOnline();
    if ((millis()-starttime) > postInterval)
    {
      sendSi7021Value();
      starttime = millis();
    }
  //client->checkFreeMem();
/*
  temperature = Si.getTemperature();
  //client->checkFreeMem();
  humidity = Si.getHumidity();

  // And output the data
//  Serial.print("T:");
//  Serial.print(temperature);
//  Serial.print("H:");
//  Serial.print(humidity);
  //Serial.println("");
  client->appendSensorValue("T1", temperature);
  client->appendSensorValue("H1", humidity);
  client->sendBySn();

  delay(15000);
*/
}

void sendSi7021Value()
{
  temperature = Si.getTemperature();
  //client->checkFreeMem();
  humidity = Si.getHumidity();
  // And output the data
//  Serial.print("T:");
//  Serial.print(temperature);
//  Serial.print("H:");
//  Serial.print(humidity);
  //Serial.println("");
  client->appendSensorValue("T1", temperature);
  client->sendSensorValue("H1", humidity);
  //client->sendBySn();
  
}
