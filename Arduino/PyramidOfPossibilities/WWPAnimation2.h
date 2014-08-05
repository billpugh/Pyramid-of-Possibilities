//
//  WWPAnimation2.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __WWPAnimation2__
#define __WWPAnimation2__

#include "RNAnimation.h"

class WWPAnimation2 : public RNAnimation {
public:
    WWPAnimation2(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();
    
};

#endif /* defined(__WWPAnimation2__) */
