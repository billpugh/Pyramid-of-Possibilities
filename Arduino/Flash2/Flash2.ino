
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include "Adafruit_NeoPixel.h"
#include "OctoWS2811.h"
#include "RNLightsNeoPixel.h"


const int num0 = 29;
const int num1 = 12;
const int num2 = 12;
const int numPixels = num0 + num1 + num2;
Adafruit_NeoPixel pixels0 = Adafruit_NeoPixel(num0, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(num1, 14, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(num2, 7, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights0(pixels0);
RNLightsNeoPixel lights1(pixels1);
RNLightsNeoPixel lights2(pixels2);
const int numSpots = 12;
const int period = 19000;

long spotStartTime[numSpots];
uint8_t spotHue[numSpots];
uint16_t spotPixel[numSpots];

unsigned int whichCycle = -1;
int led = 13;

void show() {
  lights0.show();
  delay(5);
  lights1.show();
  delay(5);
  lights2.show();
  delay(5);
}
void setBrightness(int b) {
  lights0.setBrightness(b);
  lights1.setBrightness(b);
  lights2.setBrightness(b);
}

void   setAllPixelsWhite(int w) {
  setAllPixelColors(w, w, w);
}
void   setAllPixelColors(int r, int g, int b) {
  lights0.setAllPixelColors(r, g, b);
  lights1.setAllPixelColors(r, g, b);
  lights2.setAllPixelColors(r, g, b);
}

void setPixelHSV(int pixel, uint16_t h, uint8_t s, uint8_t v) {
  if (pixel < num0) {
    lights0.setPixelHSV(pixel, h, s, v);
    return;
  }
  pixel -= num0;
  if (pixel < num1) {
    lights1.setPixelHSV(pixel, h, s, v);
    return;
  }
  pixel -= num1;

  lights2.setPixelHSV(pixel, h, s, v);
}
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  show();
  delay(1000);
  setAllPixelsWhite(25);
  delay(100);
  show();
  setAllPixelsWhite(0);
  show();
  //setBrightness(50);
  delay(2000);
  digitalWrite(led, LOW);
  setBrightness(255);
}

void resetSpot(int spot, unsigned long when) {
  spotStartTime[spot] = millis() + when;
  spotPixel[spot] = random(numPixels);
  spotHue[spot] = random(256);
}

const int onHigh = 20;
void loop() {
  unsigned long offset = millis() % period;
  unsigned int cycle = millis() / period;
  if (cycle != whichCycle) {
    whichCycle = cycle;
    for (int i = 0; i < numSpots; i++)
      resetSpot(i, 2000 + i * 10000 / numSpots + random(1000));

  }
  if (offset < onHigh) {
    setAllPixelsWhite(255 );
    digitalWrite(led, HIGH);
  } else if (offset-onHigh < 128) {
    setAllPixelsWhite(255 - (offset-onHigh));
    digitalWrite(led, HIGH);
  } else if (offset < 2000) {
    digitalWrite(led, LOW);
    int b = 128 - (offset - 128-onHigh) / 2;
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
        setPixelHSV(spotPixel[i], spotHue[i], 255, 5*brightness/2);
      }
    }
  }


  show();

  delay(20);
}
