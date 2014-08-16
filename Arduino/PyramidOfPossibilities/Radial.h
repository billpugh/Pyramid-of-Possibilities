//
//  Radial.h
//
//  Created by Danny on 8/7/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Radial__
#define __Radial__

#include "RNAnimation.h"
#include "RNGradient.h"
#include "easingSelect.h"
#include <stdint.h>


/*
TODO:

`thickness` can be a uint16_t if we want to save bytes in parameters
`period` can be made into something smaller too, but that may break code where it is used. check first!

*/

struct RadialParameters {
    float thickness = 0.05; // portion of entire radius
    RNGradient gradientInside = RNGradient(0, RNGradientCapped, 0x000000, 0xff0000);
    RNGradient gradientShell = RNGradient(0, RNGradientCapped, 0xFF0000, 0xFF8080);
    RNGradient gradientOutside = RNGradient(0, RNGradientCapped, 0x000002, 0x000002);
    EasingMode easingMode = EaseInOut;
    CurveType curveType = CurveTypeQuadratic;
};


class Radial : public RNAnimation {
public:
    Radial(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(RadialParameters), &parameters) {
    };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
    RadialParameters parameters;
};

#endif /* defined(__Radial__) */
