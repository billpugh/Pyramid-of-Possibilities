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
    : RNAnimation(info, animationStartMillis), gradient(1, RNGradientBounce, 0x8000ff, 0xc000ff) {
      
      for(int i = 0; i < 256; i++)
        info.printf("Gradient(%d) = %x\n", i, gradient.getColor(i));
    };
    virtual void paint(RNLights & lights);
    
    virtual char * name();
    
    RNGradient gradient;


};

#endif /* defined(__PlatformData__WWPAnimationTest__) */
