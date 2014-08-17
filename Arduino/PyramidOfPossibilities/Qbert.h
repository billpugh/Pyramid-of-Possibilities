//
//  Qbert.h
//  PlatformData
//
//  Created by Danny
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __QBERT__
#define __QBERT__

#include "RNAnimation.h"

// Classic
struct QbertParameters {
    uint8_t colors[15] = {0xFF,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0,0,0,0,0,0};		// 3 bytes per color
    uint8_t numColors = 3;
};

// On/Off
//struct QbertParameters {
//    uint8_t colors[15] = {200,200,200,0,20,20,0,0,0,0,0,0,0,0,0};
//    uint8_t numColors = 2;
//};


class Qbert : public RNAnimation {
public:
    Qbert(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(QbertParameters), &parameters) {
        // initalize class properties
        i = 0;
    };
    virtual void paint(RNLights & lights);
    virtual const char * name();

    uint8_t i;

    QbertParameters parameters;

};

#endif /* defined(__QBERT__) */
