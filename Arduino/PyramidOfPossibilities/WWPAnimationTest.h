//
//  WWPAnimationTest.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__WWPAnimationTest__
#define __PlatformData__WWPAnimationTest__

#include "RNAnimation.h"
#include "RNGradient.h"

class WWPAnimationTest : public RNAnimation {
public:
    WWPAnimationTest(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis), headGradient(1, RNGradientBounce,
         0x90ffff, 0xffffff),
    tailGradient(1, RNGradientBounce,
                 0x90ff00, 0xffff00),
  rpm(30), gpm(10),  length(info.numLEDs*2/3) {
      
       };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
    RNGradient headGradient, tailGradient;
    
    uint8_t length;
    
    uint16_t rpm;
     uint16_t gpm;
    
    bool global;


};

#endif /* defined(__PlatformData__WWPAnimationTest__) */
