//
//  SideEffects.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__SideEffects__
#define __PlatformData__SideEffects__

#include "RNAnimation.h"

struct SideEffectsParameters {
    uint32_t colors[6] = {
        0xff0000, 0x505050, 0x0000ff, 0xff0000, 0x505050, 0x0000ff};
    uint16_t switchTime = 5000;
};


class SideEffects : public RNAnimation {
public:
    SideEffects(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis,
                  sizeof(SideEffectsParameters), &parameters),
    lastPhaseChange(animationStartMillis) {};
    
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
   
    SideEffectsParameters parameters;
     unsigned long lastPhaseChange;
     uint8_t phase = 0;
    

};

#endif /* defined(__PlatformData__SideEffects__) */
