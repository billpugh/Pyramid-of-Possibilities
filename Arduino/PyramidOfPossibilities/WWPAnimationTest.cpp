//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"
#include <math.h>

void WWPAnimationTest::paint(RNLights & lights) {
    
    int firstLED = 1000;
    int lastLED = -1;
    
    float angle = getAnimationMillis()/2000.0;
    
    for(int i = 0; i < lights.getNumPixels(); i++) {
        float a = info.getGlobalAngle(i) - angle;
        if (a < 0) a = -a;
        a = a - floor(a);
        if (a > 0.5) a = 1.0-a;
        if (a < 0.05) {

        lights.setPixelColor( i, 255, 0, 0);
            if (firstLED > i)
                firstLED =i;
            if (lastLED < i)
                lastLED = i;
                
        }
        
    }
    if (firstLED <= lastLED)
        info.printf("Angle %f, LEDs %d ... %d\n", angle, firstLED, lastLED);
    else
        info.printf("Angle %f, no LEDs\n", angle);
    
    
    
}

const char * WWPAnimationTest:: name() {
    return "WWPAnimationTest";
}

