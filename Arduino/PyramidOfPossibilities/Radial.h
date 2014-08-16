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
enum RadialCompressionType {
    RadialCompressNone = 0x00,
    RadialCompressInner = 0x01,
    RadialCompressShell = 0x02,
    RadialCompressOuter = 0x04,
    RadialCompressAll = 0xFF
};


// Heart Beat
struct RadialParameters {
    float thickness = 0.05; // portion of entire radius
    RNGradient gradientInside = RNGradient(0, RNGradientCapped, 0x000000, 0xff0000);
    RNGradient gradientShell = RNGradient(0, RNGradientCapped, 0xFF0000, 0xFF0000);
    RNGradient gradientOutside = RNGradient(0, RNGradientCapped, 0x040000, 0x040000);
    EasingMode easingMode = EaseIn;
    CurveType curveType = CurveTypeBounce;
    uint8_t compress = RadialCompressInner | RadialCompressOuter;
};

// Chaos!
//struct RadialParameters {
//    float thickness = 0.3; // portion of entire radius
//    RNGradient gradientInside = RNGradient(1, RNGradientBounce, 0x00FFFF, 0xFFFFFF);
//    RNGradient gradientShell = RNGradient(1, RNGradientBounce, 0xFFFF00, 0xFFFF00);
//    RNGradient gradientOutside = RNGradient(1, RNGradientBounce, 0x00FFFF, 0xFFFFFF);
//    EasingMode easingMode = EaseOut;
//    CurveType curveType = CurveTypeLinear;
//    uint8_t compress = RadialCompressInner | RadialCompressOuter;
//};

// Rainbow Heart
//struct RadialParameters {
//    float thickness = 0.00; // portion of entire radius
//    RNGradient gradientInside = RNGradient(1, RNGradientBounce, 0x00FFFF, 0xFFFF00);
//    RNGradient gradientShell = RNGradient(1, RNGradientBounce, 0x00FFFF, 0xFFFFFF);
//    RNGradient gradientOutside = RNGradient(1, RNGradientBounce, 0x00FFFF, 0xFFFFFF);
//    EasingMode easingMode = EaseOut;
//    CurveType curveType = CurveTypeExpo;
//    uint8_t compress = 0;
//};

// Blue Sparkle
//struct RadialParameters {
//    float thickness = 0.2; // portion of entire radius
//    RNGradient gradientInside = RNGradient(0, RNGradientBounce, 0x0088FF, 0x0088FF);
//    RNGradient gradientShell = RNGradient(0, RNGradientBounce, 0x0088FF, 0x000080);
//    RNGradient gradientOutside = RNGradient(0, RNGradientBounce, 0x000080, 0x000080);
//    EasingMode easingMode = EaseOut;
//    CurveType curveType = CurveTypeBounce;
//    uint8_t compress = RadialCompressOuter;
//};


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
