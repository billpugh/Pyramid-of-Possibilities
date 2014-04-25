
#include "RNLightsNeoPixel.h"

RNLightsNeoPixel::RNLightsNeoPixel(Adafruit_NeoPixel & strip) : 
RNLights(strip.numPixels()), strip(strip), firstPixel(0) {
  strip.begin();
};

RNLightsNeoPixel::RNLightsNeoPixel(Adafruit_NeoPixel & strip, uint16_t firstPixel) : 
RNLights(strip.numPixels() - firstPixel), strip(strip), firstPixel(firstPixel) {
  strip.begin();
};

unsigned long RNLightsNeoPixel::show() {

  unsigned long ms_start = micros();
  uint16_t j = firstPixel;
  if (fullBrightness)
    for(uint16_t i = 0; i < getNumPixels(); i++) {
      uint8_t r,g,b;
      getPixelColor(i, r, g, b);
      strip.setPixelColor(j++, r, g, b);
    } 
  else {
    uint16_t br = brightness;
    for(uint16_t i = 0; i < getNumPixels(); i++) {
      uint8_t r,g,b;
      getPixelColor(i, r, g, b);
      r = ( br * r ) >> 8;
      g = ( br * g ) >> 8;
      b = ( br * b ) >> 8;
      strip.setPixelColor(j++, r, g, b);
    }
  }
  unsigned long ms_end = micros();

  strip.show();
  return ms_end - ms_start;
}

