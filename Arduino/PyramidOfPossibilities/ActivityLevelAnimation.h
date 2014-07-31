//
//  ActivityLevelAnimation.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __ActivityLevelAnimation__
#define __ActivityLevelAnimation__

#include "RNAnimation.h"

class ActivityLevelAnimation : public RNAnimation {

public:
    ActivityLevelAnimation(RNInfo & info, unsigned long animationStartMillis);
    virtual void paint(RNLights & lights);
    virtual char * name();
    uint16_t level;
    uint8_t direction;

};

#endif /* defined(__ActivityLevelAnimation__) */
