#include "OctoWS2811.h"
#include "Adafruit_NeoPixel.h"
#include "Accelerometer.h"
#include "RNLights.h"
#include "RNLightsOctoWS2811.h"
#include "RNInfo.h"
#include "hsv2rgb.h"
#include "Controller.h"

#define FULL_STRIP 0

#if FULL_STRIP
#define LEDs 221
#define FIRST_LED 10
#define LAST_LED 230
#else
#define LEDs 60 
#define FIRST_LED 0
#define LAST_LED 59
#endif


const int ledsPerStrip = LAST_LED;

RNInfo info(ledsPerStrip, 0,0,0,0,0,0);
DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLightsOctoWS2811 lights(leds, drawingMemory, FIRST_LED);

void setup() {
  leds.begin();
  leds.show();
  delay(5000);

  Serial.begin(115200);
  Serial.println("Started");
  Serial.println(leds.numPixels());
  Serial.println(lights.getNumPixels());
  initializeAccelerometer();

}

void loop() {
  updateAccelerometer();
  lights.reset();
  lights.setBrightness(50);
  controllerPaint(lights);
  lights.show();
  delay(10);
  // Serial.println(millis()/10);
}


