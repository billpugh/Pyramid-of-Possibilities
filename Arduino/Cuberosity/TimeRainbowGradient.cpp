//
//  TimeRainbowGradient.cpp
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#include "TimeRainbowGradient.h"
#include "led_sysdefs.h"
#include "hsv2rgb.h"

#include "CuberosityMain.h"

virtual void TimeRainbowGradient::prepare() {
    CHSV hsv;
    hsv.h = (millis()/4) & 0xff;
    hsv.s = 255;
    hsv.v = 50;
    
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    color = (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;
};



virtual void setPixel(int pos, int side, int height, int horizontalOffset) {
    leds.setPixel(pos, color);
};
