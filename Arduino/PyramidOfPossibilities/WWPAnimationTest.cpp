//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"
#include <math.h>

void WWPAnimationTest::paint(RNLights & lights) {
    

    int pos = (int) getAnimationMillis()/10;
    for(int i = 0; i < 10; i++)
        lights.setPixelColor(lights.normalize(i+pos), 255, 0, 0);

    for(int i = 0; i < 6; i++)
        lights.setPixelColor(1<<i, 0, 255, 0);
    
    info.showActivityWithSparkles(lights);

    
}

const char * WWPAnimationTest:: name() {
    return "WWPAnimationTest";
}

