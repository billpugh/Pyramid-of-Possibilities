//
//  MMAnimation1.h
//  PlatformData
//
//  Created by Meelow based on Bills and Dannys work
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__MMAnimation1__
#define __PlatformData__MMAnimation1__

#include "RNAnimation.h"
#include "RNGradient.h"
#include "easingSelect.h"

struct MMAnimation1Parameters {

    uint32_t halfLifeMillis = 10000;
    float increaseOnTap = 0.1;
    float pulseWidth = 250;

    RNGradient gradient =
    RNGradient(1, RNGradientCapped, 0x00ff60, 0x90ffff);
    EasingMode easingMode = EaseIn;
    CurveType curveType = CurveTypeLinear;
    bool activityChangesGradientPosition = true;
    uint8_t minimumBrightness = 2;
    uint16_t maxBrightness = 256;


};

class MMAnimation1 : public RNAnimation {
private:

public:
    MMAnimation1(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(MMAnimation1Parameters), &parameters) {};

    virtual void paint(RNLights & lights);
    virtual const char * name();
private:
    double brightness = 0.0;
    MMAnimation1Parameters parameters;
    uint32_t lastUpdate = 0;


};

#endif /* defined(__PlatformData__DRAnimation0__) */
