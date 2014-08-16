//
//  RNAnimation.h
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __RNAnimation__
#define __RNAnimation__


#include "RNLights.h"
#include "RNInfo.h"
#include "AnimationInfo.h"

class RNAnimation {
public:
    // Constructor
    RNAnimation(RNInfo & info, AnimationInfo animationInfo);
    RNAnimation(RNInfo & info, AnimationInfo animationInfo,  unsigned int parametersSize, void *parametersPointer);
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

    // Gives the time in milliseconds since this animation starter
    float getAnimationMinutes();
    
    // Gives the cycles since this animation started.
    float getAnimationCycles();
    
    int8_t getTweakValue();
    uint8_t getUnsignedTweakValue();
    bool hasBeenTweaked();
    uint32_t timeSinceTweak();
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
    AnimationInfo animationInfo;
    

    // Start time of the animation in local time
    const unsigned long animationStartMillis;
    unsigned long tweakLastChecked = animationStartMillis;
    

    friend class RNController;
};


RNAnimation * getAnimation(RNInfo & info, AnimationInfo animationInfo );

#endif /* defined(__RNAnimation__) */
