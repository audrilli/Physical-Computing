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