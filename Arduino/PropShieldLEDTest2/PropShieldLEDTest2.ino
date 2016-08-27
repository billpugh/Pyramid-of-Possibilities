#include "Adafruit_NeoPixel.h"
#define PIN            11
#define NUMPIXELS      512

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
 
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);  // enable access to LEDs
  pixels.begin();
}

void loop() {
  // Move a single white led 
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show();
    delay(8);
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

  }
}

