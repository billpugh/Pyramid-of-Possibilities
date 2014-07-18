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

class RNAnimation {
public:
    // Constructor
    RNAnimation(RNInfo & info, unsigned long animationStartMillis);
    // Local reference to the info object
    RNInfo & info;
    
    // Gives the time in milliseconds since this animation starter
    unsigned long getAnimationMillis();
    
    // Called if there are any parameters from central
    virtual void setParameters(int size, char * data);
    
    // Request that the animation set the lights appropriately.
    // For a base animation, the lights will be entirely black before the call
    virtual void paint(RNLights & lights);
    
private:
    
    // Start time of the animation in local time
    const unsigned long animationStartMillis;
};

#endif /* defined(__PlatformData__RNAnimation__) */
