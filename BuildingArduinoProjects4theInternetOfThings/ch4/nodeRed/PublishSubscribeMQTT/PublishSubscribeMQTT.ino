#include <PubSubClient.h>
#include <SPI.h>
#include <Ethernet.h>


//https://github.com/knolleary/pubsubclient/releases/tag/v2.3
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress staticIP(192, 168, 1, 20);
EthernetClient client;

//MQTT Setup
//IP address of the MQTT broker
char server[] = {"iot.eclipse.org"};
//or
//char server[] = {"test.mosquitto.org"};

int port = 1883;
char topic[] = {"codifythings/testMessage"};


void callback( char* topic, byte* payload, unsigned int length){
  //Print payload
  String payloadContent =  String((char*)payload);
  Serial.println("[INFO] Payload: " + payloadContent);
}
PubSubClient pubSubClient(server, 1883, callback, client);



void setup() {
  // Init serial port
  Serial.begin(9600);

  //Connect Arduino to internet
  connectToInternet();

  //Connect MQTT Broker
  Serial.println("[INFO] Connecting to MQTT Broker");
  if (pubSubClient.connect("arduinoClient")){
      Serial.println("[INFO] Connection to MQTT Broker Successful");
      pubSubClient.subscribe(topic);
      Serial.println("[INFO] Successfully Subscribed to MQTT Topic ");
      Serial.println("[INFO] Publishing to MQTT Broker");
      pubSubClient.publish(topic, "Test Message");
    }
    else {
      Serial.println("[INFO] Connection to MQTT Broker Failed");  
    }
}

void loop() {
  pubSubClient.loop();
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



