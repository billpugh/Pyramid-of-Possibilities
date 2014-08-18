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

RNAnimation::RNAnimation(RNInfo & info, AnimationInfo broadcast) : info(info), animationStartMillis(info.toLocalTime(broadcast.globalStartTime)), animationInfo(broadcast), parametersPointer(0), parametersSize(0)  {
};

RNAnimation::RNAnimation(RNInfo & info, AnimationInfo broadcast,  unsigned int parametersSize, void *parametersPointer) : info(info), animationStartMillis(info.toLocalTime(broadcast.globalStartTime)), animationInfo(broadcast), parametersSize(parametersSize), parametersPointer(parametersPointer){
};




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
    float f = animationInfo.tweakValue;
    return animationInfo.cyclesAtLastTweak + f * (timeSinceTweak() / 120000.0f);
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
    uint32_t now = getAnimationMillis();
    bool result = animationInfo.lastTweakAt > haveTweaksAsOf;
    if (result)
        haveTweaksAsOf = now;
    return result;
}

uint32_t RNAnimation::timeSinceTweak() {
    uint32_t now = getAnimationMillis();
    int32_t result = (uint32_t)(now - animationInfo.lastTweakAt);
    if (result < 0) return 0;
    return result;
}



