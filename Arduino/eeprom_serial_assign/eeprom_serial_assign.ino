const byte numChars = 32;
char receivedChars[numChars];  // an array to store the received data

boolean newData = false;

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  recvWithEndMarker();
  showNewData();
  parse();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  
  // if (Serial.available() > 0) {
           while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}



void showNewData() {
  if (newData == true) {
    Serial.print("This just in ... ");
    //if (substring(receivedChars[0]))
    Serial.println(receivedChars);
    newData = false;
  }
}
void parse(){
  char rd[]="read";
  char wt[]="write";
  char str[32]=receivedChars;
  if (str.substring(0,4)==rd)
  {
    Serial.println("hehe");
  }
  //for (i=0; i<numChars;i++){
        
    }
  
  }
