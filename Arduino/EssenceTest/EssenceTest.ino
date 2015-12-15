
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
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(num1, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(num2, 14, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights0(pixels0);
RNLightsNeoPixel lights1(pixels1);
RNLightsNeoPixel lights2(pixels2);
int led = 13;

void show() {
  lights0.show();
  delay(10);
  lights1.show();
   delay(10);
   lights2.show();
    delay(10);
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
  delay(2000);
  digitalWrite(led, LOW);
  setBrightness(50);
}


int pixel = 0;
void loop() {
  setAllPixelsWhite(25);
  setPixelHSV(pixel, 0, 255, 255);
  pixel++;
  if (pixel >= numPixels)
    pixel = 0;
  show();

  delay(20);
}
