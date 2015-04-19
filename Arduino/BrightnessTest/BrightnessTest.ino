#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 2, NEO_GRB + NEO_KHZ800);

int firstLight = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
   for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 0);
   }
   uint32_t color = strip.Color(255, 255, 255);
   for(uint16_t i=0; i<5; i++) {
        uint16_t j = (i + firstLight) % strip.numPixels();
        strip.setPixelColor(j, color);
   }
   strip.show();
   firstLight = (firstLight+1) % strip.numPixels();
   delay(20);
}
