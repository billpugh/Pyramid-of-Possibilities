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

    float thickness = 0.2;

    float overlap = 0.6;
    EasingMode easingMode = EaseIn;
    CurveType curveType = CurveTypeCubic;

    RNGradient gradient = RNGradient(1, RNGradientWrap, 0x00ffff, 0xffffff);
};

class LiftOff : public RNAnimation {
public:
    LiftOff(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(LiftoffParameters), &parameters) {};
    virtual void paint(RNLights & lights);
    bool paintWave(RNLights & lights, float height);

    virtual const char * name();
    LiftoffParameters parameters;

};

#endif /* defined(__LiftOff__) */
