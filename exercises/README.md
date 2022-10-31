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
### Exercise 7
An IMU sensor (Acceleration) Controls an led. The faster the acceleration is, the brighter the Led lights up. WHen the acceleration is too fast (27m/s) the Led switches off.

![500xIMG_1018](https://user-images.githubusercontent.com/104060149/199009247-621a7b2c-8ed5-45d5-87c8-249e4f2ad855.png)

Cirquit/ Schematic

<img width="500" alt="Cirquit" src="https://user-images.githubusercontent.com/104060149/199010728-0dce187c-bf5f-45f3-af9a-dee29387f48c.png">
<img width="500" alt="Scematic" src="https://user-images.githubusercontent.com/104060149/199010785-9fdabd14-3c7b-4bd8-86bc-fb56554e4e04.png">

Code
```C++
// Basic demo for accelerometer & gyro readings from Adafruit
// LSM6DSO32 sensor

#include <Adafruit_LSM6DSO32.h>

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11

//Led code
#define led 4
#define brightness ;

Adafruit_LSM6DSO32 dso32;
void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit LSM6DSO32 test!");

  if (!dso32.begin_I2C()) {
    // if (!dso32.begin_SPI(LSM_CS)) {
    // if (!dso32.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    // Serial.println("Failed to find LSM6DSO32 chip");
    while (1) {
      delay(10);
    }
    //led pinmode
    pinMode(led, OUTPUT);
  }

  Serial.println("LSM6DSO32 Found!");

  dso32.setAccelRange(LSM6DSO32_ACCEL_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (dso32.getAccelRange()) {
    case LSM6DSO32_ACCEL_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case LSM6DSO32_ACCEL_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case LSM6DSO32_ACCEL_RANGE_16_G:
      Serial.println("+-16G");
      break;
    case LSM6DSO32_ACCEL_RANGE_32_G:
      Serial.println("+-32G");
      break;
  }


  // dso32.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Accelerometer data rate set to: ");
  switch (dso32.getAccelDataRate()) {
    case LSM6DS_RATE_SHUTDOWN:
      Serial.println("0 Hz");
      break;
    case LSM6DS_RATE_12_5_HZ:
      Serial.println("12.5 Hz");
      break;
    case LSM6DS_RATE_26_HZ:
      Serial.println("26 Hz");
      break;
    case LSM6DS_RATE_52_HZ:
      Serial.println("52 Hz");
      break;
    case LSM6DS_RATE_104_HZ:
      Serial.println("104 Hz");
      break;
    case LSM6DS_RATE_208_HZ:
      Serial.println("208 Hz");
      break;
    case LSM6DS_RATE_416_HZ:
      Serial.println("416 Hz");
      break;
    case LSM6DS_RATE_833_HZ:
      Serial.println("833 Hz");
      break;
    case LSM6DS_RATE_1_66K_HZ:
      Serial.println("1.66 KHz");
      break;
    case LSM6DS_RATE_3_33K_HZ:
      Serial.println("3.33 KHz");
      break;
    case LSM6DS_RATE_6_66K_HZ:
      Serial.println("6.66 KHz");
      break;
  }

  void loop() {

    //  /* Get a new normalized sensor event */
    sensors_event_t accel;

    dso32.getEvent(&accel);


    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("\t\tAccel X: ");
    Serial.print(accel.acceleration.x);
    Serial.print(" \tY: ");
    Serial.print(accel.acceleration.y);
    Serial.print(" \tZ: ");
    Serial.print(accel.acceleration.z);
    Serial.println(" m/s^2 ");

    //ledLogic brightness, this code maps the sensor event to the brightness of the led
    //When the accelometer is too high, the Led turns off

    brightness = map(accel.acceleration.x,18,27,0,255));
    analogWrite(led, brightness);

    if (brightness = 27) {
      analogwrite(led, LOW)
    } else (
      analogWrite(led, brightness);)



      delay(100);
  }
  ```
  
  ### Exercise 8
  Every fourth Neopixel blinkes the same colour every 500ms
  
  ![IMG_0979](https://user-images.githubusercontent.com/104060149/199021897-f1ea6069-3a94-47fa-bfcc-39a18856c220.png)
  
  Cirquit/ Schematic
  
  <img width="500" alt="Cirquit" src="https://user-images.githubusercontent.com/104060149/199022017-8fede6fd-d548-4075-8389-91a8dc2bb366.png">
<img width="500" alt="Scematic" src="https://user-images.githubusercontent.com/104060149/199022055-8c5854f4-3bd8-4f06-963d-6b970f1b4a13.png">

Code
```C++
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // set every fourth pixel to RED
    if (i%4 == 0) { // set first and fifth pixel to red
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    } else if (i%4 == 1) {  // set second and sixt pixel to green
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    } else if (i%4 == 2) { // set third and seventh pixel to blue
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    }else {// set fourth and eighth pixel to yellow
       pixels.setPixelColor(i, pixels.Color(255, 255, 0));
    }
   

    pixels.show();   
    delay(DELAYVAL); // Pause before next pass through loop
  }
}
```
## Exercise 9
Adafruit Neopixels get controlled by a temperature Sensor. The higher the temperature, the leds turn red.

![IMG_1023](https://user-images.githubusercontent.com/104060149/199033377-b0473c47-ee28-44e9-a6bd-df04dbf53dc1.png)

//Sensor is not visible on the picture

Circuit/ Schematic

<img width="500" alt="Cirquit" src="https://user-images.githubusercontent.com/104060149/199033621-7e528b71-72ea-49d4-b563-c4a5cc65f6d2.png">
<img width="500" alt="Schematic" src="https://user-images.githubusercontent.com/104060149/199033642-bc3da4bf-57ce-49fb-ae5d-c643953e99ce.png">

Code
```C++
float color = map(temp.temperature, 24.5, 26, 0, 255);

delay(100);

//void loop NEOPIXEL
for (int i=0; i<NUMPIXELS; i++){
  pixels.setPixelColor(i, pixels.Color(color , 0, 255-color));
}
```
Temperature is written in a float and mapped onto the color of the neopixel. The higher the temperature, more pixels light up.




