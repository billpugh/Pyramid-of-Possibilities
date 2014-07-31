//
//  DRAnimation1.h
//  PlatformData
//
//  Created by Danny
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__DRAnimation1__
#define __PlatformData__DRAnimation1__

#include "RNAnimation.h"

class DRAnimation1 : public RNAnimation {
public:
    DRAnimation1(RNInfo & info, unsigned long animationStartMillis) : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual char * name();

    uint32_t base_color;

};

#endif /* defined(__PlatformData__DRAnimation1__) */
