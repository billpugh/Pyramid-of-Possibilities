//
//  WWPAnimation1.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__WWPAnimation1__
#define __PlatformData__WWPAnimation1__

#include "RNAnimation.h"
#include "RNGradient.h"

struct WWPAnimation1Parameters {
    uint8_t gpm = 10;
    RNGradient gradient = RNGradient(1,RNGradientWrap,
                                         0x00ffff, 0xffffff);
    uint8_t brightnessWithoutActivity = 64;
 

};

class WWPAnimation1 : public RNAnimation {
public:
    WWPAnimation1(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(WWPAnimation1Parameters), &parameters) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();
    
    WWPAnimation1Parameters parameters;

};

#endif /* defined(__PlatformData__WWPAnimation1__) */
