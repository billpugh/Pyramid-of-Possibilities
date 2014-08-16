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
    
    AnimationBroadcast(uint32_t startTime) : startTime(startTime), lastTweakAt(startTime), tweakValue(30), parameterLength(0) {};
    uint8_t program;
    uint8_t seqId;
    uint32_t startTime;
    float cyclesAtLastTweak;
    uint32_t lastTweakAt;
    int8_t tweakValue;
    uint8_t parameterLength;
    uint8_t parameters[MAX_PARAMETER_SIZE];
};

#endif /* defined(__AnimationBroadcast__) */
