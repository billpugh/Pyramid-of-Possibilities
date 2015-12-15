
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
int led = 13;



const int num0 = 29;
const int num1 = 12;
const int num2 = 12;
const int numPixels = num0 + num1 + num2;

RNLightsOctoWS2811 lights(leds, drawingMemory);



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
