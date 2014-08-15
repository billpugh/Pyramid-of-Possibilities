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


RNAnimation::RNAnimation(RNInfo & info, unsigned long animationStartMillis) : info(info), animationStartMillis(animationStartMillis), lastUpdate(animationStartMillis)  {
    parametersPointer = 0;
    parametersSize = 0;
};

RNAnimation::RNAnimation(RNInfo & info, unsigned long animationStartMillis,
            unsigned int parametersSize, void *parametersPointer
            )  : info(info), animationStartMillis(animationStartMillis),lastUpdate(animationStartMillis), parametersSize(parametersSize), parametersPointer(parametersPointer) {
    
}


// Gives the time in milliseconds since this animation starter
unsigned long
RNAnimation::getAnimationMillis() {
    return millis() - animationStartMillis;
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
    return cycleCount;
}

uint8_t RNAnimation::getCyclesPerMinute() {
    return cyclesPerMinute;
}


void RNAnimation::updateCycleCount() {
    unsigned long now = millis();
    cycleCount += cyclesPerMinute*(now-lastUpdate)/60000.0;
    lastUpdate = now;
}

void RNAnimation::setCyclesPerMinute(int8_t cpm) {
    cyclesPerMinute = cpm;
    
    
}


