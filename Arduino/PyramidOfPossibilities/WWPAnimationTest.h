//
//  WWPAnimationTest.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__WWPAnimationTest__
#define __PlatformData__WWPAnimationTest__

#include "RNAnimation.h"

class WWPAnimationTest : public RNAnimation {
public:
    WWPAnimationTest(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis), hue(info.getRandom(256)) {};
    virtual void paint(RNLights & lights);
    
    virtual char * name();
    
    uint8_t hue;

};

#endif /* defined(__PlatformData__WWPAnimationTest__) */
