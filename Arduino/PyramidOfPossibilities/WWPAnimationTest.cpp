//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"
#include <math.h>

void WWPAnimationTest::paint(RNLights & lights) {

    uint32_t now = getAnimationMillis();
    myLights.fade(now);
    int shouldUpdate = now * myLights.getNumPixels() * parameters.updateFraction / 1000;

    int num = shouldUpdate  - updated;
    updated = shouldUpdate;

    if (info.getTaps())
        num += parameters.updateOnTapFraction
        * myLights.getNumPixels();

    for(int i = 0; i < num; i++) {
        int pixel = info.getRandomPixel();
        int gradientPosition = info.getRandom(255);
        myLights.setPixelColor(pixel,
                               parameters.gradient.getColor(gradientPosition));


    }
    lights.copyPixels(myLights);

    


}

const char * WWPAnimationTest:: name() {
    return "WWPAnimationTest";
}

