#include <EEPROM.h>

const byte numChars = 32;
int addr;
byte data;
char receivedChars[numChars];  // an array to store the received data

boolean newData = false;

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  parse();
}

void eepr_read(int address){
  Serial.println(EEPROM.read(address), DEC);
  }
void eepr_write(int address, byte DATA){
  EEPROM.write(address,DATA);
  }
void error_msg(){
  Serial.println("Incorrect input...");  
  }
void parse(){
  while(Serial.available()){
    int flag;
    String text=Serial.readStringUntil(' ');
    if (text=="write")
      flag=1;
    else if (text=="read")
      flag=2;
    else
      flag=0;

    switch(flag){
      case 1:
          {String write_num1, write_num2;
          write_num1=Serial.readStringUntil(' ');
          write_num2=Serial.readStringUntil('\n');
          if (write_num2=="")
            {
              error_msg();
              break;
              }
          addr=write_num1.toInt();
          data=write_num2.toInt();
          //Serial.println(addr);
          //Serial.println(data);
          eepr_write(addr, data);}
          break;
      case 2:
          {String read_num;
          read_num=Serial.readStringUntil('\n');
          addr=read_num.toInt();
          //Serial.println(addr);
          eepr_read(addr);}
          break;
    //eepr_read(addr);
    //Serial.begin(9600);
    //data=write_num2.toInt();
      default:
          error_msg();
          break;     
    }  
  }
  }
