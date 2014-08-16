//
//  Kittens.cpp
//  PlatformData
//
//  Created by Branden.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Kittens.h"
#include "easing.h"
#include <Arduino.h>
#include <math.h>




void Kittens::paint(RNLights & lights) {

    int numLights = lights.getNumPixels();

    float sinceTap = min(info.timeSinceLastTap(), timeSinceTweak())/(float) parameters.tapWindow;
    if (sinceTap > 1.0)
        sinceTap = 1.0;
    else
        sinceTap = QuadraticEaseOut(sinceTap);

    float ease =
    parameters.maxEase
    - (parameters.maxEase -parameters.minEase) * sinceTap;
    bool tweaked = hasBeenTweaked();
    
    myLights.fade(getAnimationMillis());
    for (uint8_t i=0; i<NUM_KITTENS; ++i) {


        float distance = kittens[i].goal - kittens[i].position;
        if (distance > numLights/2) {
            distance -= numLights;
        } else if (distance < -numLights/2)
            distance += numLights;

        float p1 = kittens[i].position;
        kittens[i].position += distance * ease;
        float p2 = kittens[i].position;
        if (p1 > p2) {
            float tmp = p1;
            p1 = p2;
            p2 = tmp;
        }

        int colorRGB = kittens[i].color;
        uint8_t r = colorRGB >> 16;
        uint8_t g = colorRGB >> 8;
        uint8_t b = colorRGB;

        if (tweaked)
            kittens[i].goal = info.getRandomPixel();
        else if (fabs(distance) < 1) {
            kittens[i].goal = info.getRandomPixel();
            if (parameters.pounce) {
                // pounce
                p1 -= 2;
                p2 += 2;
                r = g = b = 255;
            }

        }

        for(int i = floor(p1); i <= ceil(p2); i++)
          myLights.setPixelColorMax(i, r,g,b);

        if (kittens[i].position < 0)
            kittens[i].position += info.numLEDs;
        else if (kittens[i].position >= info.numLEDs)
            kittens[i].position -= info.numLEDs;
       
    }
    lights.copyPixels(myLights);
}


const char * Kittens:: name() {
    return "Kittens";
}
