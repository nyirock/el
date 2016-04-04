#ifndef __DEVICEBITHTTPCLIENT_H__
#define __DEVICEBITHTTPCLIENT_H__

#include <Ethernet.h>
#include <EEPROM.h>

/*
DeviceBitHttpClient.h Library for DeviceBit.com to upload data
Create by yangbo
gyangbo@gmail.com
2013.6.4
*/

class DeviceBitHttpClient
{
	
	public:
		char* tcpServer;
		DeviceBitHttpClient( const char *userKey,const char *gatewayNo);
		//DeviceBitHttpClient( const char *userKey,const char *gatewayNo,byte mac[]);
		DeviceBitHttpClient( const char *userKey,const char *gatewayNo,byte mac[],IPAddress ip,IPAddress dns,IPAddress gw,IPAddress subnet);
		void keepOnline();
		void appendSensorValue(String sensorName,String sensorValue);
		void appendSensorValue(String sensorName,int sensorValue);
		void appendSensorValue(String sensorName,float sensorValue);
		void appendSensorValue(String sensorName,double sensorValue);
		void sendSensorValue(String sensorName,String sensorValue);
		void sendSensorValue(String sensorName,int sensorValue);
		void sendSensorValue(String sensorName,float sensorValue);
		void sendSensorValue(String sensorName,double sensorValue);
		void sendBySn();

		//void directResponse(String respStr);
		
		
		
		char* strToChar(String str);
		
		void checkFreeMem();
		void easySetupMode(boolean bEasyMode);
		

	private:
		char *_userKey;
		char *_gatewayNo;
		char *_sn;
		byte _mac[];
		long _starttime;
		int _postInterval;
		String _sensorValueStr;
		EthernetClient _clientRevCtrl;//connect to tcp.DeviceBit50.com and keep alive
		
		void setupDefaultValue();
		char* getParaValue(String &orig,String paraName);
		String getParaValueStr(String &orig,String paraName);
		
		
		
		boolean _bEasyMode;
		void writeRom(String value);
		void readRom();
		void listenServer();
		void softwareReset();

		EthernetServer server;
		int startCommPost;
		int currentPos;
};

#endif
