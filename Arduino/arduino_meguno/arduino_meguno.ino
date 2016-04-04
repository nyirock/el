const byte TempSensorPin = A0;
int CurrentTemperature = 0;
unsigned long LastPlotTime = 0;


void setup() 
{
  Serial.begin(9600);

}

void loop() 
{
  if((millis()-LastPlotTime)>500)
  {
    LastPlotTime = millis(); //Save time for 1s logging

    //reads 0-1023V -> 0-40degC
    CurrentTemperature = analogRead(TempSensorPin); 

    PlotKitchenTemperature(CurrentTemperature); 
    MessageLogger_CSVData(CurrentTemperature, "Secret");   
  }
}

void PlotKitchenTemperature(int data)
{
  Serial.print("{TIMEPLOT:Temperatures|data|Kitchen|T|");
  Serial.print(data);
  Serial.println("}");
}

void MessageLogger_CSVData(int temperature, String channelName)
{
  Serial.print("{MESSAGE:");
  Serial.print(channelName);
  Serial.print("|data|");
  Serial.print(temperature);
  Serial.println("}");
}
