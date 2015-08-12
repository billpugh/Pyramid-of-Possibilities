//
//  TimeGradient.cpp
//  Cuberosity
//
//  Created by Bill on 8/8/15.
//  Copyright (c) 2015 Hall of Mirrors. All rights reserved.
//

#include "TimeGradient.h"
#include "Arduino.h"

#include "CuberosityMain.h"

void TimeGradient::prepare() {
    
    AHFloat easePosition = 2.0 * ((AHFloat)millis()) / period / 1000;
    int easeBase = (int)easePosition;
    easePosition = easePosition - 2*(easeBase/2);
    if (easePosition < 1.0)
        easePosition = easeUp(easePosition);
    else
        easePosition = easeDown(2-easePosition);
    color = gradient.getColor(256*easePosition);
};

void TimeGradient::setPixel(int pos, int side, int height, int horizontalOffset) {
    leds.setPixel(pos, color);
};
