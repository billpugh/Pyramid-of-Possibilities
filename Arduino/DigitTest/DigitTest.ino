// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library


#include "OctoWS2811.h"
#include "Adafruit_NeoPixel.h"
#include "RNLights.h"
#include "RNLightsOctoWS2811.h"
#include "hsv2rgb.h"

#define NUMPIXELS      41

DMAMEM uint8_t displayMemory[NUMPIXELS*24];
uint8_t drawingMemory[NUMPIXELS*24];

RNLights *lights;

int delayval = 500; // delay for half a second

int digitPixels[10][41] = {// 0
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
// 1
  {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 2
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
// 3
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
// 4
  {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 5
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 6
  {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
// 7
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 8
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
// 9
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}};
  
void setup() {
     delay(1000);
  Serial.begin(9600);
  Serial.println("Digit test");
   OctoWS2811 *leds = new OctoWS2811(NUMPIXELS, displayMemory, drawingMemory);

  RNLightsOctoWS2811 *oLights
    = new RNLightsOctoWS2811(*leds, drawingMemory, 0);

  leds->begin();
  leds->show();
  lights = oLights;

}


void drawDigit(int d) {
  for(int i = 0; i < 41; i++)
    if (digitPixels[d][i])
     lights->setPixelColor(i, 0, 50, 0);
    else
    lights->setPixelColor(i,0,0,0);
}


void drawDigit(int d1, int rgb1, int d2, int rgb2) {
  for(int i = 0; i < 41; i++) {
    int c1 = 0;
    if (d1 >= 0 && digitPixels[d1][i])
      c1 = 1;
    int c2 = 0;
    if (d2 >= 0 && digitPixels[d2][i])
      c2 = 1;
    lights->setPixelColor(i, c1*rgb1+c2*rgb2);
  }
}
   
    
void loop() {

  int d = ( millis()/1000) % 10;
  int pd = d-1;
  if (pd == -1) pd = 9;
  int t = (millis() % 1000);
  if (t < 0) t = -t;
  t = t;
  if (t > 255) t = 255;
  int c = 0x000001;
  drawDigit(d, c*t, pd,  c*(255-t));
  
  lights->show();
  delay(10);
 
}
