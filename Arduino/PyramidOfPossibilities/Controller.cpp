//
//  Controller.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Controller.h"
#include "RNInfo.h"
#include "Arduino.h"
#include "Animations.h"


RNInfo info(0,0,0,0,0,0);

RNAnimation * currentAnimation = 0;
unsigned long animationExpires = 0;
AnimationEnum currentAnimationEnum = (AnimationEnum) 0;

void nextAnimation() {
    if (currentAnimation) {
        Serial.println("Deleting old animation");
        delete currentAnimation;
    }
    currentAnimationEnum = (AnimationEnum) (1+((int)currentAnimationEnum));
    if (currentAnimationEnum == e_AnimationCount)
        currentAnimationEnum = (AnimationEnum) 0;
    Serial.println("Switching to animation");
    Serial.println(currentAnimationEnum);
    unsigned long start = millis();
    currentAnimation = getAnimation(currentAnimationEnum, info, start);
    animationExpires = start + 10000;
    Serial.println("Animation created");
}


void controllerPaint(RNLights & lights) {
    if (millis() > animationExpires || !currentAnimation) {
        nextAnimation();
    }
    if (currentAnimation)
        currentAnimation->paint(lights);
    
}




