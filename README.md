## Exercises
### Exercise 1
A Potentiometer controls an led and it's intensity.

<img width="500" alt="picture_potentiometer" src="https://user-images.githubusercontent.com/104060149/198291720-3eb9262e-c4c0-46a6-abbd-258b02a25d58.jpeg">

Scematic/ Cirquit

<img width="500" alt="Cirquit_Potentiometer" src="https://user-images.githubusercontent.com/104060149/198305102-42c4505f-858f-482f-ab4d-43b4d1b0c01d.png">
<img width="500" alt="Schematic_Potentiometer" src="https://user-images.githubusercontent.com/104060149/198306778-9c3c0ef8-85f8-48d1-9daa-7a6756d1befd.png">


Code
```C++
#define ledRed 7
#define ledGreen 8
#define ledBlue 9
#define potMeter A0
int valuePot = 0;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  valuePot = analogRead(map(potMeter, 0, 1023, 0, 255));
  Serial.println(valuePot);
  analogWrite(ledRed, valuePot);

  if (valuePot >= 0 || valuePot >= 85) {
    analogWrite(ledRed, HIGH);

  } else {
    analogWrite(ledRed, LOW);
    analogWrite(ledGreen, LOW);
    analogWrite(ledBlue, LOW);
  }
  if (valuePot >= 85 || valuePot >= 85 + 85) {
    analogWrite(ledGreen, HIGH);
  } else {
    analogWrite(ledRed, LOW);
    analogWrite(ledGreen, LOW);
    analogWrite(ledBlue, LOW);
  }
  if (valuePot >= 85+85 || valuePot >= 85 + 85+ 85) {
    analogWrite(ledGreen, HIGH);
  } else {
    analogWrite(ledRed, LOW);
    analogWrite(ledGreen, LOW);
    analogWrite(ledBlue, LOW);
}
}
```


### Exercise 2
Controlling an incandescent lightbulb with a transistor.

<img width="500" alt="Picture" src="https://user-images.githubusercontent.com/104060149/198530328-169aae94-19e7-4399-9a48-888547d30224.jpeg">

Scematic/ Cirquit

<img width="500" alt="Cirquit" src="https://user-images.githubusercontent.com/104060149/198529900-0968f1e9-a948-46b6-99be-bbe8421f256b.png">
<img width="500" alt="Schematic" src="https://user-images.githubusercontent.com/104060149/198529913-5e184bce-0d81-4b26-8971-9063b8891742.png">

Code
```C++
#define transistor 3

void setup() {
  pinMode(transistor, OUTPUT);
}

void loop() {
  digitalWrite(transistor, HIGH);
  delay(1000);
  digitalWrite(transistor, LOW);
  delay(1000); 
}
```
### Exercise 3
Controlling the speed of a motor with a potentiometer, using a transistor.

<img width="500" alt="Picture" src="https://user-images.githubusercontent.com/104060149/198532153-44a5747a-a380-4cd5-a97f-6c12398f82fc.jpeg">

Scematic/ Cirquit

<img width="500" alt="schematic" src="https://user-images.githubusercontent.com/104060149/198532281-4f6bb9dc-a38f-4a26-9e61-36f6ad803fd0.png">

Code
```C++
#define motorPin 3
#define meterPin A0

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(meterPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int currentMeterValue = analogRead(meterPin);
  Serial.println(currentMeterValue);

  int motorStrength = map(currentMeterValue, 0, 1023, 0, 255); 
  
  analogWrite(motorPin, motorStrength);

```
### Exercise 4
Controlling the speed of a motor with a potentiometer, using a transistor.
An LED playball for learning basic soldering First used for a workshop at the ZHdK Open Day in 2014

![Base_2](https://user-images.githubusercontent.com/104060149/198980710-7235e538-6c6a-4c4e-b90e-6bd8a1acbfbf.gif)
![IMG_1047](https://user-images.githubusercontent.com/104060149/198980759-1cd81184-dace-4b04-a7d7-a90804d94889.jpg)

### Exercise 5
Connect Arduino together and send button signal to control inbuilt
LEDs. Use the code found in Github to control the devices.

Scematic/ Cirquit

![Cirquit](https://user-images.githubusercontent.com/104060149/198982628-02a6124e-c57b-4579-9314-1d89d3b926e2.jpg)
![Schematic](https://user-images.githubusercontent.com/104060149/198982677-b2fb13b0-fe86-4abe-b4bb-410ed916fd40.jpg)

Code
(Example from Github : https://github.com/IAD-ZHDK/Physical-Computing/blob/main/UART%20Arduino%20Communication/uart_code/uart_code.ino
```C++
char recUART;

void setup() {
  pinMode(8, INPUT_PULLUP); // set push button pin as input
  pinMode(13, OUTPUT);      // set LED pin as output
  digitalWrite(13, LOW);    // switch off LED pin
  Serial.begin(9600);       // initialize UART with baud rate of 9600 bps
}

void loop() {
  if (Serial.available()) {
    recUART = Serial.read();    // read one byte from serial buffer and save to data_rcvd

    if (recUART == '1') {     // switch LED On
      digitalWrite(13, HIGH);
    } 
    
    if (recUART == '0') {     // switch LED Off
      digitalWrite(13, LOW);
    }

  if (digitalRead(8) == HIGH) { // send the char '0' to serial if button is not pressed. 
    Serial.write('0'); 
  }else {           // send the char '1' to serial if button is pressed.
    Serial.write('1'); 
  }
  }   
}
```
### Exercise 6
Connect Arduino together and send potentiometer signal to control
inbuilt LEDs. Use the code found in Github to control the devices.

Cirquit/ Schematic

<img width="500" alt="Cirquit" src="https://user-images.githubusercontent.com/104060149/198984520-b140b949-dfd2-4b1b-96cc-2f5553d311ff.png">
<img width="500" alt="Schematic" src="https://user-images.githubusercontent.com/104060149/198984543-1a42cd07-fa1f-4b5d-9f48-cd58df9b528e.png">

Code
(Example from Github: 

https://github.com/IAD-ZHDK/Physical-Computing/blob/main/I2C%20Arduino%20Communication/master_code/master_code.ino
https://github.com/IAD-ZHDK/Physical-Computing/blob/main/I2C%20Arduino%20Communication/slave_code/slave_code.ino)
```C++
 // Aruindo Master Sketch

#include <Wire.h>

byte recI2C;               // data received from I2C bus
unsigned long time_start;   // start time in milliseconds
int ledVal;               // status of LED: 1 = ON, 0 = OFF
byte potVal;             // potentiometer position

void setup(){
  Wire.begin(); // join I2C bus as the master
  
  // initialize global variables
  recI2C = 255;
  time_start = millis();
  ledVal = 0;
  
  pinMode(10, OUTPUT);    // set pin 13 as an output
  Serial.begin(9600);
}

void loop(){
  // read potentiometer position
  potVal = analogRead(A0);   // read the voltage at pin A0 (potentiometer voltage)

  // send potentiometer position to Slave device 0x08
  Wire.beginTransmission(0x08); // informs the bus that we will be sending data to slave device 8 (0x08)
  Wire.write(potVal);        // send value_pot
  Wire.endTransmission();       // informs the bus and the slave device that we have finished sending data

  Wire.requestFrom(0x08, 1);    // request potentiometer position from slave 0x08
  if(Wire.available()) {        // read response from slave 0x08
    recI2C = Wire.read();
  }
  
  // blink logic code
//  if((millis() - time_start) > (1000 * (float)(recI2C/255))) {
//    ledVal = !ledVal;
//    time_start = millis();
//  }
//  
  ledVal = (int)(recI2C/255); //normalizing the incoming data between 0 and 1
  digitalWrite(10, ledVal);
  Serial.println(ledVal);
}
```
```C++
// Arduino Slave Sketch

#include <Wire.h>

byte recI2C;            // data received from I2C bus
unsigned long time_start;   // start time in mSec
int ledVal;               // status of LED: 1 = ON, 0 = OFF
byte potVal;               // potentiometer position

void setup(){
  Wire.begin(0x08);           // join I2C bus as Slave with address 0x08
  // event handler initializations
  Wire.onReceive(dataRcv);    // register an event handler for received data
  Wire.onRequest(dataRqst);   // register an event handler for data requests
  
  // initialize global variables
  recI2C = 255;
  time_start = millis();
  ledVal = 0;
  pinMode(10, OUTPUT);        // set pin 13 mode to output
  Serial.begin(9600);
}

void loop(){

  potVal = analogRead(A0); // read analog value at pin A0 (potentiometer voltage)
  ledVal = (int)(recI2C/255);
  Serial.println(ledVal);
  // blink logic code
//        if((millis() - time_start) > (1000 * (float)(recI2C/255))) {
//    ledVal = !ledVal;
//    time_start = millis();
//  }
  digitalWrite(10, ledVal);
}

//received data handler function
void dataRcv(int numBytes){
  while(Wire.available()) { // read all bytes received
    recI2C = Wire.read();
  }
}

// requests data handler function
void dataRqst(){
  Wire.write(potVal); // send potentiometer position
}
```














