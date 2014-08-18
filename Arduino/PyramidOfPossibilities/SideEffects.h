//
//  SideEffects.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __SideEffects__
#define __SideEffects__

#include "RNAnimation.h"

struct SideEffectsParameters {
    uint16_t switchTime = 5000;
    uint32_t colors[6] = {
        0xff0000, 0x555555, 0x0000ff, 0xff0000, 0x555555, 0x0000ff};

};


class SideEffects : public RNAnimation {
public:
    SideEffects(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo,
                  sizeof(SideEffectsParameters), &parameters) {};
    
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
   
    SideEffectsParameters parameters;
    uint32_t lastPhaseChange = 0;
    uint8_t phase = 0;
    

};

#endif /* defined(__SideEffects__) */
