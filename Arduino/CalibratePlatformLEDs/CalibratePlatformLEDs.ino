#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  for(int i = 0; i < 240; i++) {
    strip.setPixelColor(i, strip.Color(1, 0, 0));
  }
  strip.setPixelColor(10,  strip.Color(0, 255, 0));
  strip.setPixelColor(228,  strip.Color(0, 255, 0));
}

int next = 0;
void loop() {
  // Some example procedures showing how to display to the pixels:
  delay(5);
  strip.setPixelColor(next, strip.Color(1,0,0));
  next++;
  if (next == 10 || next == 228)
    next++;
  if (next == 240)
    next = 0;
  strip.setPixelColor(next, strip.Color(0,0,100));
  
  strip.show();
}

