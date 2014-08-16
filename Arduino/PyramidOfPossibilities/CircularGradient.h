//
//  CircularGradient.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __CircularGradient__
#define __CircularGradient__

#include "RNAnimation.h"
#include "RNGradient.h"


// Local LSD Rainbow
struct CircularGradientParameters {

    uint8_t repeats = 2;
    uint8_t brightnessWithoutActivity = 64;
    uint8_t chunkSize = 1;
    bool global = 0;
    RNGradient gradient = RNGradient(1, RNGradientWrap, 0x00ffff, 0xffffff);
};

// Global LSD Rainbow
//struct CircularGradientParameters {
//    uint8_t repeats = 2;
//    uint8_t brightnessWithoutActivity = 64;
//    uint8_t chunkSize = 1;
//    bool global = 1;
//    RNGradient gradient = RNGradient(1, RNGradientWrap, 0x00ffff, 0xffffff);
//};

// Chunky Global LSD Rainbow
//struct CircularGradientParameters {
//    uint8_t repeats = 1;
//    uint8_t brightnessWithoutActivity = 64;
//    uint8_t chunkSize = 220/5;
//    bool global = 1;
//    RNGradient gradient = RNGradient(1, RNGradientWrap, 0x00ffff, 0xffffff);
//};

// Radar
//struct CircularGradientParameters {
//    uint8_t repeats = 1;
//    uint8_t brightnessWithoutActivity = 64;
//    uint8_t chunkSize = 1;
//    bool global = 1;
//    RNGradient gradient = RNGradient(1, RNGradientWrap, 0x66ffff, 0x660000);
//};



class CircularGradient : public RNAnimation {
public:
    CircularGradient(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(CircularGradientParameters), &parameters) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();
    CircularGradientParameters parameters;

};

#endif /* defined(__CircularGradient__) */
