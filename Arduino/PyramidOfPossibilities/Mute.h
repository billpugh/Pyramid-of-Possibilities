//
//  Mute.h
//  PlatformCode
//
//  Created by Bill on 8/13/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Mute__
#define __Mute__

#include "RNAnimation.h"


class Mute : public RNAnimation {
public:
    Mute(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo) { };
    virtual void paint(RNLights & lights);



    virtual const char * name();

};

#endif /* defined(__Mute__) */
