//
//  AnimationInfo.h
//
//  Created by Bill on 8/15/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __AnimationInfo__
#define __AnimationInfo__

#include "Animations.h"
#include <stdint.h>



const int MAX_PARAMETER_SIZE = 32;

struct AnimationInfo {
    
    AnimationInfo(AnimationEnum program, uint32_t startTime) : program(program),startTime(startTime), lastTweakAt(startTime) {};
    AnimationInfo(uint32_t startTime) : program(e_WWPAnimationTest),startTime(startTime), lastTweakAt(startTime) {};
    AnimationEnum program;
    uint8_t seqId = 0;
    uint32_t startTime;
    uint32_t lastTweakAt;
    float cyclesAtLastTweak = 0.0;
    int8_t tweakValue = 30;
    uint8_t parameterLength = 0;
    uint8_t parameters[MAX_PARAMETER_SIZE];
};

#endif /* defined(__AnimationInfo__) */
