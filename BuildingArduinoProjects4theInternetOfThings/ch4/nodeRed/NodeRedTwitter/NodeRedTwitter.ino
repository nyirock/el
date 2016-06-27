#include <PubSubClient.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress staticIP(192, 168, 1, 20);
EthernetClient client;

int lightValue;

//Node-RED Flow Setup
char server[] = {"192.168.1.189"};
int port = 1880;
unsigned long lastConnectionTime=0;
const unsigned long postingInterval = 10L * 1000L;


void doHttpGet()
{
  //Read all incoming data
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);  
  }
  Serial.println();
  Serial.println("-----------------------------------------------");
  if (millis() - lastConnectionTime > postingInterval)
  {
    client.stop();
    readSensorData();

    //Prepare data or parameters that need to be posted to server
    String requestData = "requestVar="+String(lightValue);
    Serial.println("[INFO] Connecting to Server");

    //check if a connection to server:port was made
    if(client.connect(server,port))
    {
      Serial.println("[INFO] Server Connected - HTTP GET Started");
      //Make HTTP GET request
      client.println("GET /lightSensorTweet?" + requestData +" HTTP/1.1");
      client.println("Host: "+ String(server));
      client.println("Connection: close");
      client.println();

      lastConnectionTime = millis();

      Serial.println("[INFO] HTTP GET Completed");
    }
    else
    {
    //Connection to server:port failed
      Serial.println("[ERROR] Connection failed");  
    }
  }
}



void setup() {
  // Init serial port
  Serial.begin(9600);

  //Connect Arduino to internet
  connectToInternet();
}

void loop() {
  //Make HTTP Get request
  doHttpGet();

  delay(5000);
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
  Serial.println("-----------------------------------------------");
  Serial.println("");
}

void readSensorData()
{
  //Read Light Sensor Value
  lightValue = analogRead(A0);

  Serial.print("[INFO] Light Sensor Reading: ");
  Serial.println(lightValue);
}

