//
//  VerticalGradient.cpp
//  Cuberosity
//
//  Created by Bill on 6/11/15.
//  Copyright (c) 2015 Hall of Mirrors. All rights reserved.
//

#include "VerticalGradient.h"
#include "Arduino.h"
#include "Constants.h"
#include "CuberosityMain.h"



VerticalGradient::VerticalGradient() : gradient(1, RNGradientBounce, 0x90ff80, 0xffff80) {};

void VerticalGradient::prepare() {
    offset = millis() / 2000.0;
}

void VerticalGradient::setPixel(int pos, int side, int height, int horizontalOffset) {
    int gradientPosition = (offset + height * 1.0 / verticalLength) *256;
    
    int color =  gradient.getColor(gradientPosition);
    
    leds.setPixel(pos, color);
};
