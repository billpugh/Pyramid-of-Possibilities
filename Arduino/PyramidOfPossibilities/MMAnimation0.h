//
//  DRAnimation0.h
//  PlatformData
//
//  Created by Danny
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__MMAnimation0__
#define __PlatformData__MMAnimation0__

#include "RNAnimation.h"

class MMAnimation0 : public RNAnimation {
public:
    MMAnimation0(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual char * name();

};

#endif /* defined(__PlatformData__DRAnimation0__) */
