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