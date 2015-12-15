
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include "Adafruit_NeoPixel.h"
#include "RNLightsNeoPixel.h"


#define PIN            2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      240

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights(pixels);

void setup() {
  for(int i = 0; i < NUMPIXELS;) { 
    lights.setPixelColor(i++, 0, 255, 0);
    lights.setPixelColor(i++, 0, 0, 255);
    lights.setPixelColor(i++, 0, 0, 255);
    lights.setPixelColor(i++, 0, 0, 255);
  }
    
  lights.show();
}

void loop() {
  lights.rotate(true);
  lights.show();
  delay(100);
}
