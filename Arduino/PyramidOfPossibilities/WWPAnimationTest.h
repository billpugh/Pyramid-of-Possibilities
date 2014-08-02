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
    : RNAnimation(info, animationStartMillis), gradient(1, RNGradientBounce, 
         0x90ffff, 0xffffff), repeats(6), rpm(10), global(1) {
      
      for(int i = 0; i < 256; i++)
        info.printf("Gradient(%d) = %x\n", i, gradient.getColor(i));
    };
    virtual void paint(RNLights & lights);
    
    virtual char * name();
    
    RNGradient gradient;
    
    uint8_t repeats;
    
    uint16_t rpm;
    
    bool global;


};

#endif /* defined(__PlatformData__WWPAnimationTest__) */
