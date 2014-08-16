//
//  Controller.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Controller__
#define __Controller__

#include "RNLights.h"
#include "RNInfo.h"

#include "RNAnimation.h"
#include "Animations.h"
#include "Accelerometer.h"

#include "Arduino.h"
#ifdef POP_SIMULATOR
class PlatformController;
#endif


class RNController {
    
    
public:
    RNController(RNInfo & info) : info(info) {
        
    }
    
    void paint(RNLights & lights);
    void animationUpdate(AnimationBroadcast broadcast);
private:
    RNInfo & info;
    RNAnimation * currentAnimation = 0;
    unsigned long animationExpires = 0;
    AnimationEnum currentAnimationEnum = e_AnimationCount;
    void nextAnimation();
    void switchToAnimation(AnimationEnum nextAnimation);


#ifdef POP_SIMULATOR
    friend PlatformController;
#endif
    
};


#endif /* defined(__Controller__) */
