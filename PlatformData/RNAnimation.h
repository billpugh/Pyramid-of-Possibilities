//
//  RNAnimation.h
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__RNAnimation__
#define __PlatformData__RNAnimation__


#include "RNLights.h"
#include "RNInfo.h"

class Animation {
    // Constructor that initializes the info field
    Animation(RNInfo & info);
    // Local reference to the info object
    RNInfo & info;
    // Called before calling setup, to give the global time when this animated started
    
    // Gives the time in milliseconds since this animation starter
    unsigned long getAnimationMillis();
    
    // Called if there are any parameters from central
    void setParameters(int size, char * data);
    // Request that the animation set the lights appropriately.
    // For a base animation, the lights will be entirely black before the call
    void paint(RNLights & lights);
    
    
};

#endif /* defined(__PlatformData__RNAnimation__) */
