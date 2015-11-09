
#if defined(__MK20DX128__) || defined(__MK20DX256__) // Teensy 3.0 & 3.1

#include "RNLightsOctoWS2811.h"

RNLightsOctoWS2811::RNLightsOctoWS2811(OctoWS2811 & strip,  void *frameBuffer,  uint16_t firstPixel) :
RNLights(strip.numPixels()/8 - firstPixel),
strip(strip), frameBuffer((uint8_t *)frameBuffer), firstPixel(firstPixel) {
strip.begin();
}

unsigned long RNLightsOctoWS2811::show() {

  unsigned long ms_start = micros();
  uint8_t *p = frameBuffer + 24*firstPixel;
  uint16_t br = brightness;
  uint16_t num = getNumPixels();
  for(uint16_t i = 0; i < num; i++) {
    uint8_t r,g,b;
    getPixelColor(i, r, g, b);
    if (!fullBrightness) {
      r = ( br * r ) >> 8;
      g = ( br * g ) >> 8;
      b = ( br * b ) >> 8;
    }

    uint32_t color =  (g << 16) | (r << 8) | b;
    uint32_t mask;
    for (mask = (1<<23) ; mask ; mask >>= 1) {
      if (color & mask) {
        *p++ = 1;
      } 
      else {
        *p++ = 0;
      }
    }


  }
  unsigned long ms_end = micros();

  strip.show();
  return ms_end - ms_start;
}



#endif

