#include <Servo.h>

Servo myServo;

int const potPin=A0;
int potVal;
int angle;


void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal=analogRead(potPin);
  Serial.print("potVal: ");
  Serial.print(potVal);

  angle=map(potVal,0, 1023, 0, 179);
  Serial.print(", angle: ");
  Serial.println(angle);

  //at maximum angle servo seems don't like it
  //removing the max value
  if(angle==179)
    angle=179-1;//seem to work better at 178
  myServo.write(angle);
  delay(15);
}
