//
//  DRAnimation2.h
//  PlatformData
//
//  Created by Danny
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__DRAnimation2__
#define __PlatformData__DRAnimation2__

#include "RNAnimation.h"

class DRAnimation2 : public RNAnimation {
public:
    DRAnimation2(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);
    virtual char * name();
    void setup();
    uint32_t myBuffer;

    // Animation specific
    uint16_t head_position;
    // uint16_t tail_position;
    uint16_t pattern_length;
    uint16_t speed;

};

#endif /* defined(__PlatformData__DRAnimation2__) */
