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


class RNController {
    
    
public:
    RNController(RNInfo & info) : info(info) {
        
    }
    
    void paint(RNLights & lights);
private:
    RNInfo & info;
    RNAnimation * currentAnimation = 0;
    unsigned long animationExpires = 0;
    AnimationEnum currentAnimationEnum = e_AnimationCount;
    void nextAnimation();
    void switchToAnimation(AnimationEnum nextAnimation);

};


#endif /* defined(__Controller__) */
