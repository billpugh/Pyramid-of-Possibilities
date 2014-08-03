//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"
#include <math.h>

void WWPAnimationTest::paint(RNLights & lights) {
    
    
    float angle = getAnimationMillis()/2000.0;
    
    for(int i = 0; i < lights.getNumPixels(); i++) {
        float a = info.getGlobalAngle(i) - angle;
        
        if (1) {
        a = a - roundf(a);
        if (a < 0) a = -a;
        if (a < 0.05) {
            lights.setPixelHSV(i, 0, 255, 255-a*5000);
        }
        } else {
            a = a - floorf(a);
            lights.setPixelHSV(i, a*256, 255, 128);
        }
        
    }
    info.showActivityWithSparkles(lights);
    
    
}

const char * WWPAnimationTest:: name() {
    return "WWPAnimationTest";
}

