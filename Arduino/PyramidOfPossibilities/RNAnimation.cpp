//
//  RNAnimation.cpp
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Arduino.h"
#include "string.h"
#include "RNAnimation.h"
#include "AnimationInfo.h"
#include <math.h>

RNAnimation::RNAnimation(RNInfo & info, AnimationInfo broadcast) : info(info), animationStartMillis(broadcast.startTime), animationInfo(broadcast), parametersPointer(0), parametersSize(0)  {
};

RNAnimation::RNAnimation(RNInfo & info, AnimationInfo broadcast,  unsigned int parametersSize, void *parametersPointer) : info(info), animationStartMillis(broadcast.startTime), animationInfo(broadcast), parametersSize(parametersSize), parametersPointer(parametersPointer){
};


RNAnimation::RNAnimation(RNInfo & info, unsigned long animationStartMillis) : info(info), animationStartMillis(animationStartMillis), animationInfo((uint32_t)animationStartMillis), parametersPointer(0),  parametersSize(0) {
};

RNAnimation::RNAnimation(RNInfo & info, unsigned long animationStartMillis,
            unsigned int parametersSize, void *parametersPointer
            )  : info(info), animationStartMillis(animationStartMillis), animationInfo((uint32_t)animationStartMillis), parametersSize(parametersSize), parametersPointer(parametersPointer) {
    
}


// Gives the time in milliseconds since this animation starter
uint32_t
RNAnimation::getAnimationMillis() {
    return (uint32_t)(millis() - animationStartMillis);
}

float RNAnimation::getAnimationMinutes() {
    return (millis() - animationStartMillis)/60000.0;
}
// Default is to ignore parameters
bool RNAnimation::setParameters(int size, char * data) {
    
    // Validate that we can set parameters
    if ( parametersSize <= 0 || parametersPointer == 0 ) {
        // animation class did not setup it's parameters info properly.
        info.printf("Error: Failed to set parameters for %s, no setup\n", name());
        return false;
    }
    if ( size != parametersSize ) {
        info.printf("Error: Failed to set parameters for %s. bad size %d/%d\n", name(), size, parametersSize);
        return false;
    }
    
    memcpy(parametersPointer, data, size);
    info.printf("Copied new parameters for %s\n", name());
    return true;
}

const char * RNAnimation:: name() {
    return "Unknown";
}



void RNAnimation::paint(RNLights &lights) {}

// Gives the cycles since this animation started.
float RNAnimation::getAnimationCycles() {
    return animationInfo.cyclesAtLastTweak + animationInfo.tweakValue * (millis() - animationInfo.lastTweakAt) / 120000.0f;
}

float RNAnimation::getAnimationCyclesFraction() {
    float result = getAnimationCycles();
    return result - floor(result);
}


int8_t RNAnimation::getTweakValue() {
    return animationInfo.tweakValue;
}
uint8_t RNAnimation::getUnsignedTweakValue() {
    return (uint8_t) (0xff & animationInfo.tweakValue);
}


bool RNAnimation::hasBeenTweaked() {
    unsigned long now = getAnimationMillis();
    bool result = animationInfo.lastTweakAt > tweakLastChecked;
    tweakLastChecked = now;
    return result;
}

uint32_t RNAnimation::timeSinceTweak() {
    unsigned long now = getAnimationMillis();
    int32_t result = (uint32_t)(now - animationInfo.lastTweakAt);
    if (result < 0) return 0;
    return result;
}



