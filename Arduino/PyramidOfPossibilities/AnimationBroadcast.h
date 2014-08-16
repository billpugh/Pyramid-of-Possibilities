//
//  AnimationBroadcast.h
//  PlatformCode
//
//  Created by Bill on 8/15/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __AnimationBroadcast__
#define __AnimationBroadcast__

#include <stdint.h>


const int MAX_PARAMETER_SIZE = 32;

struct AnimationBroadcast {
    
    AnimationBroadcast(uint32_t startTime) : startTime(startTime), lastTweakAt(startTime) {};
    uint8_t program;
    uint8_t seqId;
    uint32_t startTime;
    uint32_t lastTweakAt;
    float cyclesAtLastTweak = 0.0;
    int8_t tweakValue = 30;
    uint8_t parameterLength = 0;
    uint8_t parameters[MAX_PARAMETER_SIZE];
};

#endif /* defined(__AnimationBroadcast__) */
