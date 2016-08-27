#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H

#include <FastLED.h>
#include "BlinkyTape.h"

class ColorWheel : public Pattern {
    
  public:
    ColorWheel(int x);
    void reset() {};
    void draw(CRGB * leds);
};

#endif
