//
//  ChangingColor.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __ChangingColor__
#define __ChangingColor__

#include "RNAnimation.h"
#include "RNGradient.h"

struct ChangingColorParameters {
    uint8_t gpm = 10;
    RNGradient gradient = RNGradient(1,RNGradientWrap,
                                         0x00ffff, 0xffffff);
    uint8_t brightnessWithoutActivity = 64;
 

};

class ChangingColor : public RNAnimation {
public:
    ChangingColor(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(ChangingColorParameters), &parameters) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();
    
    ChangingColorParameters parameters;

};

#endif /* defined(__ChangingColor__) */
