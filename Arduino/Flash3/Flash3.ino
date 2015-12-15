
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include <Adafruit_NeoPixel.h>
#include <OctoWS2811.h>
#include "RNLightsOctoWS2811.h"



const int ledsPerStrip = 32;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);


const int num0 = 29;
const int num1 = 12;
const int num2 = 12;
const int numPixels = num0 + num1 + num2;

RNLightsOctoWS2811 lights(leds, drawingMemory);

const int numSpots = 6;
const int period = 19000;

long spotStartTime[numSpots];
uint8_t spotHue[numSpots];
uint16_t spotPixel[numSpots];

unsigned int whichCycle = -1;
int led = 13;

void show() {
  lights.show();
  
}
void setBrightness(int b) {
  lights.setBrightness(b);
  
}

void   setAllPixelsWhite(int w) {
  setAllPixelColors(w, w, w);
}
void   setAllPixelColors(int r, int g, int b) {
  lights.setAllPixelColors(r, g, b);
 
}

void setPixelHSV(int pixel, uint16_t h, uint8_t s, uint8_t v) {
  if (pixel < num0) {
    lights.setPixelHSV(pixel, h, s, v);
    return;
  }
  pixel -= num0;
  if (pixel < num1) {
    lights.setPixelHSV(pixel + ledsPerStrip, h, s, v);
    return;
  }
  pixel -= num1;

  lights.setPixelHSV(pixel + 2*ledsPerStrip, h, s, v);
}
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  show();
  setAllPixelsWhite(25);
  delay(500);
  show();
  setAllPixelsWhite(0);
  //setBrightness(50);
  delay(500);
  digitalWrite(led, LOW);
  //setBrightness(255);
}

void resetSpot(int spot, unsigned long when) {
  spotStartTime[spot] = millis() + when;
  spotPixel[spot] = random(numPixels);
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
  if (offset < 128) {
    setAllPixelsWhite(255 - offset);
    digitalWrite(led, HIGH);
  } else if (offset < 2000) {
    digitalWrite(led, LOW);
    int b = 128 - (offset - 128) / 2;
    if (b < 0)
      b = 0;
    setAllPixelsWhite(b);

  } else  {
    digitalWrite(led, LOW);
    setAllPixelsWhite(0);
    for (int i = 0; i < numSpots; i++) {
      long myOffset =  millis() - spotStartTime[i];
      if (myOffset < 0) continue;
      if (myOffset > 1500) {
        resetSpot(i, 250 + random(3000));
      } else if (myOffset < 1300) {
        int brightness = 100;
        if (myOffset < 200)
          brightness = myOffset / 2;
        else if (myOffset > 800)
          brightness = 100 - (myOffset - 800) / 5;
        setPixelHSV(spotPixel[i], spotHue[i], 255, brightness);
      }
    }
  }


  show();

  delay(20);
}
