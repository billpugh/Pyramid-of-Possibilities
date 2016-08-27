#include <FastLED.h>

#define NUM_LEDS 12
CRGB leds[NUM_LEDS];

void setup() {
  delay(2000);      // sanity check delay
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);  // enable access to LEDs
}

void loop() {
  // Move a single white led 
  for(int n = 0; n < NUM_LEDS; n++) {
    leds[n] = CRGB::White;
    FastLED.show();
    delay(8);
    leds[n] = CRGB::Black;
  }
}

