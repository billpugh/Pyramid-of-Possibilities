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
        for(int i = 0; i < info.numLEDs; i++) 
            info.printf("Led %3d at %f\n", i, info.getGlobalAngle(i));
            
      
       };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
\


};

#endif /* defined(__WWPAnimationTest__) */
