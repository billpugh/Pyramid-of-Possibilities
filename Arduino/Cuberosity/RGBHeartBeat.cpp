//
//  RGBHeartBeat.cpp
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#include <stdlib.h>
#include "RGBHeartBeat.h"
#include "Arduino.h"
#include "Constants.h"
#include "hsv2rgb.h"
#include "CuberosityMain.h"



 void RGBHeartBeat::prepare() {
    int size = millis() % 2000;
    size = abs(size - 1000);
    effectSize = easingFunction(size/1000.0);
};

 void RGBHeartBeat::setPixel(int pos, int side, int height, int horizontalOffset) {
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
    
};