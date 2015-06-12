//
//  RadialGradient.cpp
//  Cuberosity
//
//  Created by Bill on 6/11/15.
//  Copyright (c) 2015 Hall of Mirrors. All rights reserved.
//

#include "RadialGradient.h"
#include "Arduino.h"
#include "Constants.h"
#include "CuberosityMain.h"



void RadialGradient::prepare() {
    hsv.s = 255;
    hsv.v = 160;
    offset = millis()/1500.0;
}  

void RadialGradient::setPixel(int pos, int side, int height, int horizontalOffset) {
    float myOffset = side - horizontalOffset/2.0/(horizontalLength+1)
    + offset;
    int hue = ((int)(myOffset * 256 / 3.0)) & 0xff;
    hsv.h = hue;
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    int color = (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;

    leds.setPixel(pos, color);
};
