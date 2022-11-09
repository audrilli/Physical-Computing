
int led = 11;           
int brightness = 0;      
#define Ls A0


void setup() {
  
  pinMode(led, OUTPUT);
  pinMode(Ls, INPUT);




void loop() {

  brightness = map(ls,0,1023,0,255);
  analogWrite(led, brightness);
  delay(30);
}
