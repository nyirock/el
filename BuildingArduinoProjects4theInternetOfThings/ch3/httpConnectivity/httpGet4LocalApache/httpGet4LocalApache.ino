#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress staticIP(192, 168, 1, 20);
EthernetClient client;
char server[] = {"192.168.1.189"};
int port = 80;



void setup() {
  // Init serial port
  Serial.begin(9600);

  //Connect Arduino to internet
  connectToInternet();

  //Make http Post request
  doHttpGet();

}

void loop() {
  if (client.available()){
      Serial.println("[INFO] HTTP Response");
    }

  //Read available incoming bytes from the server and print
  while(client.available()){
      char c = client.read();
      Serial.write(c);
    }

  //If the server:port has disconnected, then stop the client
  if(!client.connected()){
      Serial.println();
      Serial.println("[INFO] Disconnecting From Server");
      client.stop();
    }
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

void doHttpGet()
{
    //Prepare data or parameters that need to be posted to server
    String requestData = "requestVar=test";
    //Check if a connection to server:port was made
    if (client.connect(server, port)){
        Serial.println("[INFO] Server Connected - HTTP Get Started");

        //Make HTTP GET request
        client.println("GET /cgi-bin/printenv.pl?"+ requestData +" HTTP/1.1");
        client.println("Host: "+ String(server));
        client.println("Connection: close");
        client.println();
        client.println(requestData);

        Serial.println("[INFO] HTTP GET Completed");
      }
      else{
          //Connection to server:port failed
          Serial.println("[ERROR] Connection Failed");
        }
      Serial.println("-------------------------------------------");
}

