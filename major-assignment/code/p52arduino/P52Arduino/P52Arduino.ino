const int MAX_VALUES = 5;  //maximum amount of values received
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];  // temporary array for use when parsing



// variables to hold the parsed data
boolean newData = false;

//============

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
 
}

//============

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    newData = false;
  }
   int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(1);
}

//============
// Code from https://forum.arduino.cc/t/serial-input-basics-updated/382007

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char endMarker = '>';
  char startMarker = '<';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } else {
        receivedChars[ndx] = '\0';  // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

//============

void parseData() {  // split the data into its parts
  char* strtokIndx;

  strtokIndx = strtok(tempChars, ",");
  int q = atoi(strtokIndx);

  if (q == 0 || q == 1) {
    digitalWrite(LED_BUILTIN, q);
  }

  strtokIndx = strtok(NULL, ",");
  int w = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  int e = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  int r = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  int t = atoi(strtokIndx);


  Serial.println(q);
  Serial.println(w);
  Serial.println(e);
  Serial.println(r);
  Serial.println(t);
}

