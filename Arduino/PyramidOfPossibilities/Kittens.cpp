//
//  Kittens.cpp
//  PlatformData
//
//  Created by Branden.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Kittens.h"
#include <Arduino.h>
#include <math.h>


static float ease = 0.05;

void Kittens::paint(RNLights & lights) {
    int distance;
    int numLights = lights.getNumPixels();
    myLights.fade(getAnimationMillis());
    for (uint8_t i=0; i<NUM_KITTENS; ++i) {
        if (abs(kittens[i].position - kittens[i].goal) < 1) {
            kittens[i].goal = info.getRandomPixel();
        }

        distance = kittens[i].goal - kittens[i].position;
        if (distance > numLights/2) {
            distance -= numLights;
        } else if (distance < -numLights/2)
            distance += numLights;

        int p1 = kittens[i].position;

        int d2;
        if (distance > 0)
            d2 = ceil(distance*ease);
        else
            d2 = floor(distance*ease);

        kittens[i].position += d2;

        int p2 = kittens[i].position;
        if (p1 > p2) {
            int tmp = p1;
            p1 = p2;
            p2 = tmp;
        }
        if (p2 - p1 > numLights || p1 > p2) {
            info.printf("Huh: %d %d\n", p1, p2);
            p1 = p2;
        }

        int colorRGB = kittens[i].color;
        uint8_t r = colorRGB >> 16;
        uint8_t g = colorRGB >> 8;
        uint8_t b = colorRGB;

        for(int i = p1; i <= p2; i++)
          myLights.setPixelColorMax(i, r,g,b);

        kittens[i].position = lights.normalize(kittens[i].position);
       
    }
    lights.copyPixels(myLights);
    info.showActivityWithSparkles(lights);
}


const char * Kittens:: name() {
    return "Kittens";
}
