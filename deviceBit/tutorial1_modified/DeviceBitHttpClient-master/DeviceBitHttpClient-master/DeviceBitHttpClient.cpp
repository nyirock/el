
#include <DeviceBitHttpClient.h>

DeviceBitHttpClient::DeviceBitHttpClient(const char *userKey,const char *gatewayNo):
	server(EthernetServer(80)),
	tcpServer("tcp.DeviceBit.com")
{
	_userKey = (char*)malloc( strlen(userKey)+1 );
	strcpy( _userKey,userKey );
	
	_gatewayNo = (char*)malloc( strlen(gatewayNo)+1 );
	strcpy( _gatewayNo,gatewayNo );
	
	setupDefaultValue();
	
	//Ethernet.begin(_mac);
	byte _mac[] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31};
	if (Ethernet.begin(_mac) == 0) {
    Serial.println("fail");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
	Serial.println(Ethernet.localIP());
	//Ethernet.begin(mac, ip);
	delay(1000);
	//keepOnline();
}

DeviceBitHttpClient::DeviceBitHttpClient( const char *userKey,const char *gatewayNo,byte mac[],IPAddress ip,IPAddress dns,IPAddress gw,IPAddress subnet):
	server(EthernetServer(80)),
	tcpServer("tcp.DeviceBit.com")
{
	_userKey = (char*)malloc( strlen(userKey)+1 );
	strcpy( _userKey,userKey );
	
	_gatewayNo = (char*)malloc( strlen(gatewayNo)+1 );
	strcpy( _gatewayNo,gatewayNo );
	
	setupDefaultValue();
	Ethernet.begin(mac,ip,dns,gw,subnet);
	Serial.println(Ethernet.localIP());
	delay(1000);
	//keepOnline();
}

void DeviceBitHttpClient::setupDefaultValue()
{
	//checkFreeMem();
	
	byte _mac[] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31};
	_postInterval = 30000;//server setting is 60000
	_starttime = millis();
	

	_bEasyMode = false;
	startCommPost = 75;
	currentPos = 0;

}
void DeviceBitHttpClient::keepOnline()
{
	
	if(_bEasyMode)
	{
		listenServer();
	}
}

void DeviceBitHttpClient::easySetupMode(boolean bEasyMode)
{
	_bEasyMode = bEasyMode;
	if(_bEasyMode)
	{
		readRom();
		
		server.begin();
	  //Serial.print("srv:");
	  //Serial.println(Ethernet.localIP());
	}
}

void DeviceBitHttpClient::writeRom(String value)
{
  for(int i =0;i<8;i++)
  {
     EEPROM.write(i, value.charAt(i));
  }
  softwareReset();
}

void DeviceBitHttpClient::softwareReset()
{
   asm volatile ("  jmp 0");
}



void DeviceBitHttpClient::readRom()
{
  byte value;
  String tmp = "";
  for(int address=0;address<8;address++)
  {
    value = EEPROM.read(address);
    
    if(value!=0x00)
    {
   		tmp +=char(value);
   	}
    //Serial.print(address);
    //Serial.println(char(value));
    
    if(address==7)
    {
    	if(tmp.length()==8)
    	{
	    	char * tmpc = strToChar(tmp);
	    	_sn = tmpc;
	    	//Serial.print("ky:");
	    	//Serial.println(_userKey);
	    	//free(tmpc);
	    	//tmpc = NULL;
	    }
    	tmp = "";
    }
  }
}


void DeviceBitHttpClient::listenServer()
{
  EthernetClient clientWeb = server.available();
  if (clientWeb) {
    //Serial.println("new clientWeb");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String clientStr = "";
    while (clientWeb.connected()) {
      if (clientWeb.available()) {
        char c = clientWeb.read();
        clientStr += c;
        //Serial.write(c);
        
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          clientWeb.println("<html><body><form method='get'>");
          clientWeb.print("SN<input type='text' name='s' value='");
          clientWeb.print(_sn);
          clientWeb.print("'><input type='submit'>");
          clientWeb.println("</form></body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          if(clientStr.indexOf(" /?s=")>0)
          {
          	Serial.print(clientStr);
          	String userInfoStr = clientStr.substring(clientStr.indexOf(" /?s=")+5,clientStr.indexOf(" HTTP/1.1"));
          	//userInfoStr += clientStr.substring(clientStr.indexOf("&s=")+3,clientStr.indexOf(" HTTP/1.1"));
            Serial.println(userInfoStr);
            clientWeb.println("OK!");
            if(userInfoStr.length()==8)writeRom(userInfoStr);
          }
          //Serial.println(clientStr);
          clientStr = "";
          //checkFreeMem();
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    clientWeb.stop();
    clientWeb= NULL;
    //Serial.println("clientWeb disonnected");
  }
  
}

char* DeviceBitHttpClient::strToChar(String str)
{
	char* c = (char*)malloc(str.length()+1);
	if(!c)
	{
		//Serial.print("strToChar::");
		//Serial.println(str);
		Serial.println("malloc:F");
		return NULL;
	}
	str.toCharArray(c,str.length()+1);
	return c;
}



char* DeviceBitHttpClient::getParaValue(String &orig,String paraName)
{
		//Serial.print("P:");
		//Serial.println(paraName);
		int functionNameStartPos = orig.indexOf("\""+paraName+"\":\"");
		if(functionNameStartPos<0)return NULL;
		int functionNameEndPos = orig.indexOf("\"",functionNameStartPos+4+paraName.length());
		String functionName = orig.substring(functionNameStartPos+4+paraName.length(),functionNameEndPos);
		
		char* c = strToChar(functionName);
		return c;
}

String DeviceBitHttpClient::getParaValueStr(String &orig,String paraName)
{
		int functionNameStartPos = orig.indexOf("\""+paraName+"\":\"");
		if(functionNameStartPos<0)return "";
		int functionNameEndPos = orig.indexOf("\"",functionNameStartPos+4+paraName.length());
		String functionName = orig.substring(functionNameStartPos+4+paraName.length(),functionNameEndPos);
		
		return functionName;
}
/*
void DeviceBitHttpClient::directResponse(String respStr)
{
	if(_clientRevCtrl.connected())
	{
		respStr +="&^!";
		char* c = (char*)malloc(respStr.length()+1);
		respStr.toCharArray(c,respStr.length()+1);
		_clientRevCtrl.print(c);
		Serial.println(c);
		free(c);
		c = NULL;
	}
}
*/


void DeviceBitHttpClient::appendSensorValue(String sensorName,String sensorValue)
{
	_sensorValueStr +="{\"Name\":\"";
	_sensorValueStr +=sensorName;
	_sensorValueStr +="\",\"Value\":\"";
	_sensorValueStr +=sensorValue;
	_sensorValueStr +="\"},";
}
void DeviceBitHttpClient::appendSensorValue(String sensorName,int sensorValue)
{
	appendSensorValue(sensorName,String(sensorValue));
}
void DeviceBitHttpClient::appendSensorValue(String sensorName,float sensorValue)
{
	char s[10];
	int val_len = snprintf(s, 10,"%d.%02u", (int)sensorValue, (int)(abs(sensorValue)*100+0.5) % 100);
	appendSensorValue(sensorName,(String)s);
}

void DeviceBitHttpClient::appendSensorValue(String sensorName,double sensorValue)
{
	char s[10];
	int val_len = snprintf(s, 10,"%d.%02u", (int)sensorValue, (int)(abs(sensorValue)*100+0.5) % 100);
	appendSensorValue(sensorName,(String)s);
}


void DeviceBitHttpClient::sendSensorValue(String sensorName,String sensorValue)
{
	//checkFreeMem();
	char server[] = "open.devicebit.com";
	//IPAddress server(192,168,2,10);
	if (_clientRevCtrl.connect(server, 80))
	{
		String tpl = "POST /api/V1/gateway/UpdateSensors/%GW% HTTP/1.1\r\nHost: open.devicebit.com\r\nConnection: Keep-Alive\r\nuserkey:";
		tpl.replace("%GW%",_gatewayNo);
    //Serial.print(tpl);
    _clientRevCtrl.print(tpl);
    //Serial.print(_userKey);
    _clientRevCtrl.print(_userKey);
    //Serial.print("\r\nContent-Length: ");
    _clientRevCtrl.print("\r\nContent-Length: ");
    //Serial.println(_sensorValueStr);
		//appendSensorValue(sensorName,sensorValue);
    //Serial.println(_sensorValueStr.length()+sensorName.length()+sensorValue.length()+24);
    //String tmp2 = _sensorValueStr.substring(0,_sensorValueStr.length()-1);
    //Serial.println(tmp2.length()+2);
    _clientRevCtrl.println(_sensorValueStr.length()+sensorName.length()+sensorValue.length()+24);
    //Serial.println();
    _clientRevCtrl.println();
    //Serial.print("[");
    _clientRevCtrl.print("[");
    //Serial.print(_sensorValueStr+"{\"Name\":\""+sensorName+"\",\"Value\":\""+sensorValue+"\"}");
    _clientRevCtrl.print(_sensorValueStr+"{\"Name\":\""+sensorName+"\",\"Value\":\""+sensorValue+"\"}");
    //Serial.print("]");
    _clientRevCtrl.println("]");
    //tmp2 = "";
    _sensorValueStr = "";
    _clientRevCtrl.stop();
	}
  else {
    // kf you didn't get a connection to the server:
    Serial.println("conn fail");
  }
  //checkFreeMem();
	
}

void DeviceBitHttpClient::sendBySn()
{
	//checkFreeMem();
	char server[] = "open.DeviceBit.com";
	//IPAddress server(192,168,2,10);
	if (_clientRevCtrl.connect(server, 80))
	{
		String tpl = "POST /api/V1/gateway/UpdateSensorsBySN/%SN% HTTP/1.1\r\nHost: open.DeviceBit.com\r\nConnection: Keep-Alive\r\nContent-Length: ";
		String tmp = tpl;
		if(strlen(_sn)==8)tmp.replace("%SN%",_sn);
    //Serial.print(tmp);
    _clientRevCtrl.print(tmp);
    String tmp2 = _sensorValueStr.substring(0,_sensorValueStr.length()-1);
    //Serial.println(tmp2.length()+2);
    _clientRevCtrl.println(tmp2.length()+2);
    //Serial.println();
    _clientRevCtrl.println();
    //Serial.print("[");
    _clientRevCtrl.print("[");
    //Serial.print(tmp2);
    _clientRevCtrl.print(tmp2);
    //Serial.print("]");
    _clientRevCtrl.println("]");
    tmp ="";
    tmp2 = "";
    _sensorValueStr = "";
    _clientRevCtrl.stop();
	}
  else {
    // kf you didn't get a connection to the server:
    Serial.println("conn fail");
  }
  //checkFreeMem();
}

void DeviceBitHttpClient::checkFreeMem()
{
	int startPos = 0;
		for(int i = 512;i>0;i--)
		{
			char* c = (char*)malloc(i+startPos);
			if(c)
			{
				free(c);
				c=NULL;
				Serial.print("M");
				Serial.println(i+startPos);
				break;
			}
		}
}

void DeviceBitHttpClient::sendSensorValue(String sensorName,int sensorValue)
{
	sendSensorValue(sensorName,String(sensorValue));
}


void DeviceBitHttpClient::sendSensorValue(String sensorName,float sensorValue)
{
	char s[10];
	int val_len = snprintf(s, 10,"%d.%02u", (int)sensorValue, (int)(abs(sensorValue)*100+0.5) % 100);
	sendSensorValue(sensorName,(String)s);
	
}

void DeviceBitHttpClient::sendSensorValue(String sensorName,double sensorValue)
{
	char s[10];
	int val_len = snprintf(s, 10,"%d.%02u", (int)sensorValue, (int)(abs(sensorValue)*100+0.5) % 100);
	sendSensorValue(sensorName,(String)s);
	
}

