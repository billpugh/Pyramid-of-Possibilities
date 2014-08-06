// hsv2rgbTest

#include "hsv2rgb.h"

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

void setup() {
  delay(2000);
  Serial.begin(9600);
  Serial.println("Starting");

  CHSV hsv;
  CRGB rgb;
  hsv.s = 255;
  hsv.v = 255;
  for(int h = 0; h < 256; h++) {
    hsv.h = h;
    hsv2rgb_rainbow(hsv,rgb);
    p("%3d %3d %3d %3d\n", h, rgb.r, 
    rgb.g, rgb.b);
  }

}

void loop() {
}

