//
//  RNAnimation.cpp
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Arduino.h"

#include "RNAnimation.h"


RNAnimation::RNAnimation(RNInfo & info, unsigned long animationStartMillis) : info(info), animationStartMillis(animationStartMillis) {};


// Gives the time in milliseconds since this animation starter
unsigned long
RNAnimation::getAnimationMillis() {
    return millis() - animationStartMillis;
}

// Default is to ignore parameters
void RNAnimation::setParameters(int size, char * data) {
    
}

void RNAnimation::paint(RNLights &lights) {}
