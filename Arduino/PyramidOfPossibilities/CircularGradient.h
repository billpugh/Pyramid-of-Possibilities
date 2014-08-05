//
//  CircularGradient.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __CircularGradient__
#define __CircularGradient__

#include "RNAnimation.h"
#include "RNGradient.h"


struct CircularGradientParameters {

    uint8_t rpm = 30;
    uint8_t repeats = 2;
    uint8_t brightnessWithoutActivity = 64;
    bool global = 0;
    RNGradient gradient = RNGradient(0, RNGradientCapped, 0x00ffff, 0xffffff);
};

class CircularGradient : public RNAnimation {
public:
    CircularGradient(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(CircularGradientParameters), &parameters) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();
    CircularGradientParameters parameters;

};

#endif /* defined(__CircularGradient__) */
