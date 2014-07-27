//
//  WWPAnimation3.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__WWPAnimation3__
#define __PlatformData__WWPAnimation3__

#include "RNAnimation.h"

class WWPAnimation3 : public RNAnimation {
public:
    WWPAnimation3(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual char * name();
};


#endif /* defined(__PlatformData__WWPAnimation3__) */
