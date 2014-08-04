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

class WWPAnimationTest : public RNAnimation {
public:
    WWPAnimationTest(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {
            
      
       };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
\


};

#endif /* defined(__WWPAnimationTest__) */
