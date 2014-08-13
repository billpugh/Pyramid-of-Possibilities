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

struct MuteParameters {
    uint8_t brightness = 40;
};

class Mute : public RNAnimation {
public:
    Mute(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis,
                  sizeof(MuteParameters), &parameters) { };
    virtual void paint(RNLights & lights);



    virtual const char * name();
private:
    MuteParameters parameters;
};

#endif /* defined(__Mute__) */
