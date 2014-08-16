//
//  LiftOff.h
//
//  Created by Bill on 8/16/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __LiftOff__
#define __LiftOff__

#include "RNAnimation.h"
#include "RNGradient.h"
#include "easingSelect.h"

struct LiftoffParameters {

    float thickness = 0.3;
    float speed = 2.0;

    float overlap = 0.6;
    uint16_t brightness = 256;
    RNGradient backgroundGradient = RNGradient(0, RNGradientCapped, 0x000000, 0x000060);
    EasingMode easingMode = EaseIn;
    CurveType curveType = CurveTypeQuadratic;

    RNGradient gradient = RNGradient(0, RNGradientCapped, 0xff0000, 0x400000);
};

class LiftOff : public RNAnimation {
public:
    LiftOff(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(LiftoffParameters), &parameters) {};
    virtual void paint(RNLights & lights);
    bool paintWave(RNLights & lights, float height);

    virtual const char * name();
    LiftoffParameters parameters;

};

#endif /* defined(__LiftOff__) */
