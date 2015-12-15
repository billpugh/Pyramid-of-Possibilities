
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include "Adafruit_NeoPixel.h"
// #include "OctoWS2811.h"
#include "RNLightsNeoPixel.h"


#define PIN            12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights(pixels);

const int numSpots = 6;
const int period = 19000;

long spotStartTime[numSpots];
uint8_t spotHue[numSpots];
uint16_t spotPixel[numSpots];

unsigned int whichCycle = -1;
int led = 13;

void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  lights.show();
  delay(2000);
  digitalWrite(led, LOW);
  lights.setBrightness(180);
}

void resetSpot(int spot, unsigned long when) {
  spotStartTime[spot] = millis() + when;
  spotPixel[spot] = random(lights.getNumPixels());
  spotHue[spot] = random(256);
}

void loop() {
  unsigned long offset = millis() % period;
  unsigned int cycle = millis() / period;
  if (cycle != whichCycle) {
    whichCycle = cycle;
    for (int i = 0; i < numSpots; i++)
      resetSpot(i, 2000 + i * 10000 / numSpots + random(1000));

  }
  if (offset < 500)
    lights.setAllPixelColors(255, 255, 255);
  else if (offset < 500 + 255) {
    int b = 500 + 255 - offset;
    lights.setAllPixelColors(b, b, b);

  }  else if (offset < 2000) {
    lights.setAllPixelColors(0, 0, 0);
  } else  {
    lights.setAllPixelColors(0, 0, 0);
    for (int i = 0; i < numSpots; i++) {
      long myOffset =  millis() - spotStartTime[i];
      if (myOffset < 0) continue;
      if (myOffset > 1500) {
        resetSpot(i, 250 + random(3000));
      } else if (myOffset < 1300) {
        int brightness = 100;
        if (myOffset < 200)
          brightness = myOffset / 2;
        else if (myOffset < 1300)
          brightness = 100 - (myOffset - 800) / 5;
        lights.setPixelHSV(spotPixel[i], spotHue[i], 255, brightness);
      }
    }
  }


  lights.show();

  delay(50);
}
