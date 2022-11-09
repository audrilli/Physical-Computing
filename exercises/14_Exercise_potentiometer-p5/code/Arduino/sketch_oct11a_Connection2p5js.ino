#define sensorPin A0
#define led 11
void setup() {
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  
  // put your setup code here, to run once:
}

void loop() {
  int sensorValue = analogRead(sensorPin);
 sensorValue = constrain(sensorValue,0,255);
  Serial.println(sensorValue);
  delay(50);
  int brightness = sensorValue;
  analogWrite(led,brightness);

  //Serial.write(brightness);

 

  /*if (sensorValue > 90) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  */
  delay(20);
}





// put your main code here, to run repeatedly: