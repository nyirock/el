int sensorValue;
int sensorLow=1023;
int sensorHigh=0;

const int ledPin=13;//built-in LED

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  //Sensor calibration
  while(millis()<5000){
      sensorValue=analogRead(A0);
      if(sensorValue>sensorHigh){
          sensorHigh=sensorValue;
        }
      if(sensorValue<sensorLow){
          sensorLow=sensorValue;
        }
    }
  digitalWrite(ledPin, LOW);//calibration is done
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue=analogRead(A0);

  int pitch=map(sensorValue, sensorLow, sensorHigh, 4000, 50);//inverted the values compared to the manual, 10 makes lower noise

  if(sensorValue<0.97*sensorHigh)//removes background noise
    tone(8, pitch, 20);// 8th pin, pitch, 20 milliseconds

  delay(10);
}
