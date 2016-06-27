#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress staticIP(192, 168, 1, 20);
EthernetClient client;



void setup() {
  // Init serial port
  Serial.begin(9600);

  //Connect Arduino to internet
  connectToInternet();

}

void loop() {
  // Do nothing

}

void connectToInternet()
{
  //Attempt to connect to Ethernet with DHCP
  if (Ethernet.begin(mac)==0){
      Serial.print("[ERROR] Failed to Configure Ethernet with DHCP");
      //DHCP failed, attempt to connect to Ethernet with static IP
      Ethernet.begin(mac, staticIP);
    }  
  //Delay to let Ethernet shield initialize

  delay(1000);

  //connection successful
  Serial.println("[INFO] Connection Successful");
  Serial.print("");
  printConnectionInformation();
  Serial.println("-----------------------------------------------");
  Serial.println("");
}

void printConnectionInformation()
{
  //Print Connection Information
  Serial.print("[INFO] IP Address: ");  
  Serial.println(Ethernet.localIP());  
  Serial.print("[INFO] Subnet Mask: ");  
  Serial.println(Ethernet.subnetMask());  
  Serial.print("[INFO] Gateway: ");  
  Serial.println(Ethernet.gatewayIP());  
  Serial.print("[INFO] DNS: ");  
  Serial.println(Ethernet.dnsServerIP());  
}
