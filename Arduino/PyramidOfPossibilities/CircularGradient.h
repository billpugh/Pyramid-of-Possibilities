//
//  CircularGradient.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __CircularGradient__
#define __CircularGradient__

#include "RNAnimation.h"

class CircularGradient : public RNAnimation {
public:
    CircularGradient(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();
    
};

#endif /* defined(__CircularGradient__) */
