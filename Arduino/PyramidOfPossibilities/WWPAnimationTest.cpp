//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"

void WWPAnimationTest::paint(RNLights & lights) {
    
    float timeInMinutes =  getAnimationMillis()/60000.0;
    uint16_t count = 256*repeats ;
    
    float basePos =  timeInMinutes * rpm;
    //  info.printf("rotation %f -> %d\n", timeInMinutes, baseHue);
    //
    for(int i = 0; i < lights.getNumPixels(); i++) {
        float pos = basePos;
        if (global)
            pos += info.getGlobalAngle(i);
        else
            pos += info.getLocalAngle(i);
        lights.setPixelColor(i, gradient.getColor( pos * count));
    }
    
    info.showActivity(lights, false, 40);
    
}

const char * WWPAnimationTest:: name() {
    return "WWPAnimationTest";
}

