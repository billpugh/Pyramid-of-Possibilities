//
//  DRAnimation0.h
//  PlatformData
//
//  Created by Danny
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__DRAnimation0__
#define __PlatformData__DRAnimation0__

#include "RNAnimation.h"

class DRAnimation0 : public RNAnimation {
public:
    DRAnimation0(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();

};

#endif /* defined(__PlatformData__DRAnimation0__) */
