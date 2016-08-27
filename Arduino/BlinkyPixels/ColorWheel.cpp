#include "ColorWheel.h"
#include "BlinkyTape.h"

#include <Arduino.h>

ColorWheel::ColorWheel(int x)  {
  }

void ColorWheel::draw(CRGB* leds) {  
for (uint8_t i = 0; i < LED_COUNT; i++) {
    uint8_t hue = 0xff & ((millis() / 40 + i) / 4);
    leds[i].setHue(hue);
  }
}
