#include <Arduino_LSM6DS3.h>
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

  while (!Serial)
    ;

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1)
      ;
  }
  //Serialprint setup Gyroscope
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");

  //Serialprint setup Accelerometer
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
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
  // float sensorValue = analogRead(A0);
  // Serial.println(map(sensorValue, 0, 1023, 0.0, 1.00));
  // delay(1);

  float xg, yg, zg;
  float xa, ya, za;

  if (IMU.gyroscopeAvailable() && IMU.accelerationAvailable()) {
    IMU.readAcceleration(xa, ya, za);
    IMU.readGyroscope(xg, yg, zg);
    Serial.print(xg);
   
    Serial.print(",");
    Serial.print(yg);
   
    Serial.print(",");
    Serial.print(zg);
    
    Serial.print(",");
    Serial.print(xa);
   
    Serial.print(",");
    Serial.print(ya);
   
    Serial.print(",");
    Serial.println(za);
  }
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