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

RNAnimation * currentAnimation = NULL;
unsigned long animationExpires = 0;
AnimationEnum currentAnimationEnum = (AnimationEnum) 0;

void nextAnimation() {
    if (currentAnimation != NULL)
        delete currentAnimation;
    currentAnimationEnum = (AnimationEnum) (1+((int)currentAnimationEnum));
    if (currentAnimationEnum == e_AnimationCount)
        currentAnimationEnum = (AnimationEnum) 0;
    currentAnimation = getAnimation(currentAnimationEnum);
    animationExpires = millis() + 5000;
}


void controllerLoop(RNLights & lights) {
    if (millis() > animationExpires || currentAnimation == NULL) {
        nextAnimation();
    }
    if (currentAnimation != NULL)
        currentAnimation->paint(lights);
    
}




