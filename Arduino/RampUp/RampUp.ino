#include <Adafruit_NeoPixel.h>

const int numLEDs = 220;
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs+10, 2, NEO_GRB + NEO_KHZ800);

const int ONBOARD_LED_PIN = 13;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(ONBOARD_LED_PIN, OUTPUT); 
  for(int i = 0; i < 10; i++) {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(350);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(150);
  }
}

int count = 0;
const int value = 255;
void loop() {
  count++;
  if (count >= numLEDs) {
    count = 0;
    delay(5000);
  }
  for(int i = 0; i < numLEDs; i++) 
    if (i <= count || i+count > numLEDs)
      strip.setPixelColor(i+15, value, value, value);
    else
      strip.setPixelColor(i+15, 0);
  strip.show();

}


