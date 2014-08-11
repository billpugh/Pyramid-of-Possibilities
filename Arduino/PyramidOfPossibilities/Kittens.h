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
};

struct Kitten {
    uint16_t position = 0;
    uint16_t goal = 0;
};

class Kittens : public RNAnimation {
public:
    Kittens(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(KittenParameters), &parameters) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();

private:
    Kitten kittens[NUM_KITTENS];


    KittenParameters parameters;

};

#endif /* defined(__Kittens__) */
