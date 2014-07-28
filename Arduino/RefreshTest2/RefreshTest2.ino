#include "OctoWS2811.h"
#include "Adafruit_NeoPixel.h"

#include "RNLights.h"
#include "RNLightsOctoWS2811.h"

#include "hsv2rgb.h"

#define FULL_STRIP 1

#if FULL_STRIP
#define LEDs 221
#define FIRST_LED 10
#define LAST_LED 230
#else
#define LEDs 60 
#define FIRST_LED 0
#define LAST_LED 59
#endif


const int ledsPerStrip = LAST_LED+1;
DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLightsOctoWS2811 lights(leds, drawingMemory, FIRST_LED);

int count = 0;
unsigned long started;
void setup() {
  leds.begin();
  leds.show();
  delay(5000);

  Serial.begin(115200);
  Serial.println("Started");
  lights.setPixelColor(0,0,255,0);
  started = micros();
}


void loop() {
  lights.rotate(true);
  unsigned long s = micros();
  lights.show();
  unsigned long e = micros();
  count++;
  if (count % 100 == 0) {
    unsigned long avg = (micros() - started)/count;
    Serial.print(e-s);
    Serial.print("  ");
    Serial.println(avg);
  }
  delay(10);
}

