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
    ActivityLevelAnimation(RNInfo & info, AnimationInfo animationInfo);
    virtual void paint(RNLights & lights);
    virtual const char * name();
    float level;

};

#endif /* defined(__ActivityLevelAnimation__) */
