## Exercises
### Exercise 1
A Potentiometer controls an led and it's intensity.

<img width="300" alt="picture_potentiometer" src="https://user-images.githubusercontent.com/104060149/198291720-3eb9262e-c4c0-46a6-abbd-258b02a25d58.jpeg">

Scematic/ Cirquit

<img width="300" alt="Cirquit_Potentiometer" src="https://user-images.githubusercontent.com/104060149/198305102-42c4505f-858f-482f-ab4d-43b4d1b0c01d.png">

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




