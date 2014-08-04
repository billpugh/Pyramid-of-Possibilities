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
    // Constructor
    RNAnimation(RNInfo & info, unsigned long animationStartMillis,
                unsigned int parametersSize, void *parametersPointer
                );
    
    
    virtual ~RNAnimation() {};
    
    // Local reference to the info object
    RNInfo & info;
    
    // Gives the time in milliseconds since this animation starter
    unsigned long getAnimationMillis();
    
    // name of the animation
    virtual const char * name();
    
    // Request that the animation set the lights appropriately.
    // For a base animation, the lights will be entirely black before the call
    virtual void paint(RNLights & lights);
    
    
    // Parameters

    // Called if there are any parameters from central
    // return true if successful
    virtual bool setParameters(int size, char * data);
    
    // set the address of the parameters struct (from your animation subclass)
    void *parametersPointer;
    
    // set the size of the parameters struct (from your animation subclass)
    unsigned int parametersSize;
    
private:
    
    // Start time of the animation in local time
    const unsigned long animationStartMillis;
};

#endif /* defined(__PlatformData__RNAnimation__) */
