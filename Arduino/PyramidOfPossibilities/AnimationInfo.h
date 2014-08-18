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
    
    AnimationInfo(AnimationEnum program, uint32_t globalStartTime) : program(program), seqId(0), globalStartTime(globalStartTime) {};
    
    AnimationInfo(AnimationEnum program, uint8_t seqId, uint32_t globalStartTime) : program(program), seqId(seqId), globalStartTime(globalStartTime) {};
    
    AnimationInfo(uint32_t startTime) : program(e_WWPAnimationTest),seqId(0), globalStartTime(startTime) {};
    
    const AnimationEnum program;
    const uint8_t seqId;
    // global time at which this animation started
    const uint32_t globalStartTime;
    
    // relative to startTime for an animation, global time for a broadcast
    uint32_t lastTweakAt = 0;
    float cyclesAtLastTweak = 0.0;
    int8_t tweakValue = 30;
    
    uint8_t parameterLength = 0;
    uint8_t parameters[MAX_PARAMETER_SIZE];
};

#endif /* defined(__AnimationInfo__) */
