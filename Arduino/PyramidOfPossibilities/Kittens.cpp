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
    unsigned long ms = getAnimationMillis();

    lights.fade(ms);

    info.printf("Kittens: ");
    for (uint8_t i=0; i<NUM_KITTENS; ++i) {
        if (abs(kittens[i].position - kittens[i].goal) < 1) {
            kittens[i].goal = info.getRandomPixel();
        }

        distance = kittens[i].goal - kittens[i].position;
        int d = distance;
        if (distance > numLights/2) {
            distance -= numLights/-2;
        }

        int p1 = kittens[i].position;

        int d2;
        if (distance > 0)
            d2 = ceil(distance*ease);
        else
            d2 = floor(distance*ease);

        kittens[i].position += d2;

        info.printf("%3d %3d %3d %3d %3d ", kittens[i].position, kittens[i].goal, d, distance, d2);


        int p2 = kittens[i].position;
        if (p1 > p2) {
            int tmp = p1;
            p1 = p2;
            p2 = tmp;
        }

        int c0 = lights.getPixelColor(p1);

        int colorRGB = kittens[i].color;
        uint8_t r =colorRGB >> 16;
        uint8_t g =colorRGB >> 8;
        uint8_t b = colorRGB;

        for(int i = p1; i <= p2; i++)
        lights.setPixelColorMax(i, r,g,b);
        int c1 = lights.getPixelColor(p1);
        info.printf("%6x %6x %6x\n", c0, kittens[i].color, c1);
        kittens[i].position = lights.normalize(kittens[i].position);
       
    }
    info.println("");
}

const char * Kittens:: name() {
    return "Kittens";
}
