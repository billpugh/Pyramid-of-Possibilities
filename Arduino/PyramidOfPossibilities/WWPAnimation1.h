//
//  WWPAnimation1.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__WWPAnimation1__
#define __PlatformData__WWPAnimation1__

#include "RNAnimation.h"

class WWPAnimation1 : public RNAnimation {
public:
    WWPAnimation1(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();

};

#endif /* defined(__PlatformData__WWPAnimation1__) */
