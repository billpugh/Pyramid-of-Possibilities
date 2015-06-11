//
//  Scrapbook.cpp
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#include "Scrapbook.h"




int getColor() {
    
    CHSV hsv;
    hsv.h = (millis()/40)&0xff;
    hsv.s = 255;
    hsv.v = 50;
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    return (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;
    
}








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
