#include <Adafruit_NeoPixel.h>

const int ledsPerStrip = 240;
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledsPerStrip, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  delay(100);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


int i = 0;
int color = 0xff0000;

void loop() {
  strip.setPixelColor(i, color);
  i++;
  if (i >= ledsPerStrip) {
    i = 0;
    if (color)
      color = 0;
    else
      color =  0xff0000;
    delay(1000);
  }
  strip.show();
  delay(10);
}

