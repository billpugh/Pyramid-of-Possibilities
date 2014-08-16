//
//  GlowFade.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __GlowFade__
#define __GlowFade__

#include "RNAnimation.h"
#include "RNGradient.h"

struct GlowFadeParameters {
    uint8_t gradiantSkip = 69 ;
    uint8_t maxBrightness = 200;
    RNGradient gradient = RNGradient(1, RNGradientWrap,0x00ffff, 0xffffff);
    float fractionUp = 0.5;
};

// Quick Color Rise
//struct GlowFadeParameters {
//    uint8_t gradiantSkip = 83 ;
//    uint8_t maxBrightness = 200;
//    RNGradient gradient = RNGradient(0, RNGradientWrap,0x00FFFF, 0xFF00FF);
//    float fractionUp = 0.1;
//};

// Quick Color Fall
//struct GlowFadeParameters {
//    uint8_t gradiantSkip = 69 ;
//    uint8_t maxBrightness = 255;
//    RNGradient gradient = RNGradient(1, RNGradientWrap,0x00FFFF, 0xFFFFFF);
//    float fractionUp = 0.8;
//};


class GlowFade : public RNAnimation {

public:
    GlowFade(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(GlowFadeParameters), &parameters) {

    };
    virtual void paint(RNLights & lights);
    virtual const char * name();

    void getLinear(float pos, uint8_t &value);
    GlowFadeParameters parameters;

};

#endif /* defined(__GlowFade__) */
