#include <DeviceBitTcpClient.h>

#include <Ethernet.h>


#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <EEPROM.h>

Adafruit_BMP085 bmp;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 20);
IPAddress mydns(8, 8, 8, 8);
IPAddress gw(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
#define LW_USERKEY "b4fbeddcf4c44fa7996a6ee1d15a39cc"
#define LW_GATEWAY "02"

DeviceBitTcpClient *client;

float temperature, pressure;
long starttime;
int postInterval = 1000;
void setup()
{
  Wire.begin();
  //Ethernet.begin(mac, ip, mydns, gw, subnet);
  Serial.begin(9600);
  if (bmp.begin())
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
  //client = new DeviceBitHttpClient(LW_USERKEY, LW_GATEWAY);
  //2.full setting for your network
  client = new DeviceBitTcpClient(LW_USERKEY, LW_GATEWAY, mac, ip, mydns, gw, subnet);


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

  client->keepOnline();

  //client->checkFreeMem();

  temperature = bmp.readTemperature();
   Serial.print("T1: ");
   Serial.print(temperature);

  //client->checkFreeMem();
  pressure = bmp.readPressure();

  // And output the data

 Serial.print(";P1: ");
 Serial.println(pressure);

  client->appendSensorValue("T1", temperature);
  client->appendSensorValue("P1", pressure);
  //client->sendBySn();

  delay(1000);

}
