//
//  Kittens.h
//  PlatformData
//
//  Created by Branden
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Kittens__
#define __Kittens__

#include "RNAnimation.h"

const uint8_t NUM_KITTENS = 3;
struct KittenParameters {
    float minEase = 0.02;
    float maxEase = 0.08;
    uint16_t fade = 200;
    uint16_t tapWindow = 5000;
    bool pounce = true;
};

struct Kitten {
    float position = 0;
    int16_t goal = 0;
    uint32_t color;
};

class Kittens : public RNAnimation {

public:
    Kittens(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(KittenParameters), &parameters), myLights(info.numLEDs) {
        myLights.setFade(0, parameters.fade);
        for(int i = 0; i < NUM_KITTENS; i++) {
            kittens[i].position = info.getRandomPixel();
            kittens[i].goal = info.getRandomPixel();
        }
        kittens[0].color = 0xff0000;
        kittens[1].color = 0x00ff00;
        kittens[2].color = 0x0000ff;
    }
    virtual void paint(RNLights & lights);
    virtual const char * name();

private:
    Kitten kittens[NUM_KITTENS];
    RNLights myLights;

    KittenParameters parameters;
};

#endif /* defined(__Kittens__) */
