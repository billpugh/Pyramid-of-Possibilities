//
//  SideEffects.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__SideEffects__
#define __PlatformData__SideEffects__

#include "RNAnimation.h"

class SideEffects : public RNAnimation {
public:
    SideEffects(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis), lastPhaseChange(animationStartMillis) {};
    virtual void paint(RNLights & lights);
    
    virtual char * name();
    
    unsigned long lastPhaseChange;

};

#endif /* defined(__PlatformData__SideEffects__) */
