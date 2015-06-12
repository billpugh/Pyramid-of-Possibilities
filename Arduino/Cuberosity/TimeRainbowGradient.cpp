//
//  TimeRainbowGradient.cpp
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#include "Arduino.h"
#include "TimeRainbowGradient.h"
#include "led_sysdefs.h"
#include "hsv2rgb.h"

#include "CuberosityMain.h"

 void TimeRainbowGradient::prepare() {
    CHSV hsv;
    hsv.h = (millis()/100) & 0xff;
    hsv.s = 255;
    hsv.v = 150;
    
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    color = (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;
};



 void TimeRainbowGradient::setPixel(int pos, int side, int height, int horizontalOffset) {
    leds.setPixel(pos, color);
};
