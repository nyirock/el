#define CDS_INPUT 0 //here it is, A0 :)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int value=analogRead(CDS_INPUT);//CDS_INPUT probably has something to do with A0
  //Serial.print("Light value is: ");
  Serial.println(value);

  delay(1000);
  

}
