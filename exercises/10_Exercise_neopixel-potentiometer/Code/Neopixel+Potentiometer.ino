//neopixel define
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
//defined Pin
#define PIN 6
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500
//PinColors define
#define R 255
#define G 255
#define B 255


void setup() {

//Neopixel Setup
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();

  Serial.begin(9600);
}

void loop() {
  int sensVal = analogRead(A2);
  sensVal = constrain(sensVal, 0, 255);
  Serial.println(sensVal);
  delay(1);
  //sensVal = constrain(sensVal,0,255);

  //Loop Neopixel
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(R-sensVal, G-sensVal, B));
    pixels.show();
    //delay(DELAYVAL);
  }
}