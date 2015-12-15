#include "FastLED.h"
#include "hsv2rgb.h"

void analyze(int h) {
  CHSV hsv;
  hsv.h = h;
  hsv.s = 255;
  hsv.v = 255;
  CRGB rgb;
  hsv2rgb_rainbow(hsv, rgb);
  Serial.printf("%3d   %2x %2x %2x\n", h, rgb.r, rgb.g, rgb.b);
}
void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(9600);
  for (int h = 0; h < 255; h ++)
    analyze(h);
  analyze(255);
}

// r = 0
// y = 64
// g = 96
// cyan = 136
// b = 160
// Magenta = 208


void loop() {
  // put your main code here, to run repeatedly:

}
