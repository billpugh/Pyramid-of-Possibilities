//
//  GradientSwirl.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __GradientSwirl__
#define __GradientSwirl__

#include "RNAnimation.h"
#include "RNGradient.h"

class GradientSwirl : public RNAnimation {
public:
    GradientSwirl(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis), gradient(1, RNGradientBounce, 
         0x90ffff, 0xffffff), repeats(6), rpm(10), global(1) {
      
       };
    
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
    RNGradient gradient;
    
    uint8_t repeats;
    
    uint16_t rpm;
    
    bool global;


};

#endif /* defined(__GradientSwirl__) */
