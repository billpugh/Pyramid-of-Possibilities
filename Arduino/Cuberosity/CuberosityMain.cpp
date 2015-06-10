//
//  CuberosityMain.cpp
//  Cuberosity
//
//  Created by Bill on 6/4/15.
//
//

#include "CuberosityMain.h"
#include <stdio.h>
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include "easingSelect.h"

uint32_t colors[] = {0x400000, 0x004000, 0x000040};
const int colorCount = 3;

DMAMEM int displayMemory[LEDsPerStrip * 6];
int drawingMemory[LEDsPerStrip * 6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(LEDsPerStrip, displayMemory, drawingMemory, config);

AHEasingFunction easingFunction = getEasingFunction(EaseIn, CurveTypeBounce);

void setupMain() {
  Serial.begin(9600);
  leds.begin();
  leds.show();
  delay(5000);

}



int getColor() {
 
    CHSV hsv;
    hsv.h = (millis()/40)&0xff;
    hsv.s = 255;
    hsv.v = 50;
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    return (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;
    
}



float effectSize;


   

void setPixel(int pos, int side, int height, int horizontalOffset) {
    int distance = abs(height) + abs(horizontalOffset);
    int size = effectSize * verticalLength * 1.1;
    CHSV hsv;
    hsv.h = side*80;
    hsv.s = 255;
    if (distance < size)
            hsv.v = 50;
    else
        hsv.v = 10;
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    int color = (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;
    leds.setPixel(pos, color);
    
}

void iterateAll() {
    for(int side = 0; side < 3; side++) {
        int stripStart =side*2*LEDsPerStrip;
        for(int i = 0; i < horizontalLength; i++)
            setPixel(stripStart + i, side, 0, -1-i);
        stripStart += horizontalLength + horizontalGap;
        for(int i = 0; i < horizontalLength; i++)
            setPixel(stripStart + i, (side+1)%3, 0, horizontalLength-i);
        stripStart += horizontalLength;
        for(int i = 0; i < verticalLength; i++)
            setPixel(stripStart + i, (side+1)%3, i+1, 0);
        
        // do down size
        stripStart = side*2*LEDsPerStrip + LEDsPerStrip;
        for(int i = 0; i < verticalLength; i++)
            setPixel(stripStart + i, side, -1-i, 0);
       
    }
}
  

void doit(int offset) {
    int c = getColor();
    for(int i = 0; i < 6; i++) for(int j = 0; j < LEDsPerStrip; j++)
        leds.setPixel(i*LEDsPerStrip+j, c);
    leds.show();
}

void loopMain() {
  int size = millis() % 2000;
  size = abs(size - 1000);
  effectSize = easingFunction(size/1000.0);
 
       delay(100);
//    for(int i = 0; i < verticalLength; i++)
//    leds.setPixel(LEDsPerStrip+i, 0x40);
//      for(int i = 0; i < horizontalLength; i++) {
//    leds.setPixel( i, 0x4000);
//      leds.setPixel( i+horizontalLength+horizontalGap, 0x400000);
//      }
//  for(int i = 0; i < verticalLength; i++)
//    leds.setPixel(horizontalLength*2+horizontalGap+i, 0x202020);
//   
    int offset = millis() / 200;
    // doit(offset);
    iterateAll();
    leds.show();
    
}
