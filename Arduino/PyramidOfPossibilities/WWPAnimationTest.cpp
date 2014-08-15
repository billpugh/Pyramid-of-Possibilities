//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"
#include <math.h>

void WWPAnimationTest::paint(RNLights & lights) {
    

    RNGradient gradient =  RNGradient(true, RNGradientWrap, 0x00ffff, 0xffffff);
    

    for(int i = 0; i < lights.getNumPixels(); i++) {
        int gradientPosition = i * 256 /lights.getNumPixels();
      
        lights.setPixelColor(i,  gradient.getColor(gradientPosition));
    }
    
}

const char * WWPAnimationTest:: name() {
    return "WWPAnimationTest";
}

