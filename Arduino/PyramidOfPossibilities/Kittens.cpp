//
//  Kittens.cpp
//  PlatformData
//
//  Created by Branden.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Kittens.h"


static float ease = 0.05;

void Kittens::paint(RNLights & lights) {
    int distance;
    int numLights = lights.getNumPixels();
    unsigned long ms = getAnimationMillis();

    lights.fade(ms);

    for (uint8_t i=0; i<3; ++i) {
        if (abs(kittens[i].pos - kittens[i].goal) < 1) {
            kittens[i].goal = random(numLights);
        }

        distance = kittens[i].goal - kittens[i].pos;

        if (distance > numLights/2) {
            distance -= numLights/-2;
        }

        kittens[i].pos += distance * ease;

        int pixel = round(kittens[i].pos);
        uint8_t red = lights.getPixelRed(pixel);
        uint8_t green = lights.getPixelGreen(pixel);
        uint8_t blue = lights.getPixelBlue(pixel);

        if (i == 0) {
            red = 255;
        } else if (i == 1) {
            green = 255;
        } else {
            blue = 255;
        }

        lights.setPixelColor(pixel, red, green, blue);
    }
}

const char * Kittens:: name() {
    return "Kittens";
}
