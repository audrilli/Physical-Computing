## Exercises
### Exercise 1
A Potentiometer controls an led and it's intensity.

<img width="500" alt="picture_potentiometer" src="https://user-images.githubusercontent.com/104060149/198291720-3eb9262e-c4c0-46a6-abbd-258b02a25d58.jpeg">

Scematic/ Cirquit

<img width="500" alt="Cirquit_Potentiometer" src="https://user-images.githubusercontent.com/104060149/198305102-42c4505f-858f-482f-ab4d-43b4d1b0c01d.png">
<img width="500" alt="Schematic_Potentiometer" src="https://user-images.githubusercontent.com/104060149/198306778-9c3c0ef8-85f8-48d1-9daa-7a6756d1befd.png">


Code
```C++
void loop() {
  valuePot = analogRead(map(potMeter, 0, 1023, 0, 255));
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
The value of the potentiometer is mapped to the brightness of the leds.
For certain values, seperate leds light up

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

### Exercise 7
An IMU sensor (Acceleration) Controls an led. The faster the acceleration is, the brighter the Led lights up. WHen the acceleration is too fast (27m/s) the Led switches off.

![500xIMG_1018](https://user-images.githubusercontent.com/104060149/199009247-621a7b2c-8ed5-45d5-87c8-249e4f2ad855.png)

Cirquit/ Schematic

<img width="500" alt="Cirquit" src="https://user-images.githubusercontent.com/104060149/199010728-0dce187c-bf5f-45f3-af9a-dee29387f48c.png">
<img width="500" alt="Scematic" src="https://user-images.githubusercontent.com/104060149/199010785-9fdabd14-3c7b-4bd8-86bc-fb56554e4e04.png">

Code
```C++
//
let brightness;

//ledLogic brightness, this code maps the sensor event to the brightness of the led
//When the accelometer is too high, the Led turns off

   brightness = map(accel.acceleration.x,18,27,0,255));
   analogWrite(led, brightness);

 if (brightness = 27) {
   analogwrite(led, LOW)
   }else{
      analogWrite(led, brightness);)
      delay(100);
        }
 }
  ```
with brightness as an variable, mapped to the acceleration value, the led brughtness gets controlled.
  
  
### Exercise 8
Every fourth Neopixel blinkes the same colour every 500ms

![IMG_0979](https://user-images.githubusercontent.com/104060149/199021897-f1ea6069-3a94-47fa-bfcc-39a18856c220.png)
Cirquit/ Schematic

<img width="500" alt="Cirquit" src="https://user-images.githubusercontent.com/104060149/199022017-8fede6fd-d548-4075-8389-91a8dc2bb366.png">
<img width="500" alt="Scematic" src="https://user-images.githubusercontent.com/104060149/199022055-8c5854f4-3bd8-4f06-963d-6b970f1b4a13.png">

Code
```C++
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
The pixels get called using the modulo function.

### Exercise 9
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




