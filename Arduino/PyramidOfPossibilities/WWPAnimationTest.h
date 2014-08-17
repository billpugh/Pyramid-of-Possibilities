//
//  WWPAnimationTest.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __WWPAnimationTest__
#define __WWPAnimationTest__

#include "RNAnimation.h"
#include "RNGradient.h"


struct WWPAnimationTestParameters {

    float updateFraction = 0.5;
    float updateOnTapFraction = 1.0;
    RNGradient gradient = RNGradient(1, RNGradientWrap, 0x00ff80, 0x40ffff);
};
class WWPAnimationTest : public RNAnimation {
public:
    WWPAnimationTest(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(WWPAnimationTestParameters), &parameters), myLights(info.numLEDs) {
       };

    virtual void paint(RNLights & lights);
    
    virtual const char * name();

private:
    WWPAnimationTestParameters parameters;
    RNLights myLights;
    uint32_t updated = 0;

};

#endif /* defined(__WWPAnimationTest__) */
