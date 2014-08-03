//
//  DRAnimation1.h
//  PlatformData
//
//  Created by Danny
//  Copyright (c) 2014 RN. All rights reserved.
//

#include <stdint.h>

#ifndef __PlatformData__DRAnimation1__
#define __PlatformData__DRAnimation1__

struct DRAnimation1Parameters {
    uint32_t base_color;
};

#include "RNAnimation.h"

void initalizeBeams(RNInfo * info);

class DRAnimation1 : public RNAnimation {
public:
    DRAnimation1(RNInfo & info, unsigned long animationStartMillis) : RNAnimation(info, animationStartMillis) {
		min_g = .1;
		max_g = .3;
        initalizeBeams(&info);
        parametersSize = sizeof(DRAnimation1Parameters);
        parametersPointer = &parameters;
        
        // initalize parameters to default values
        parameters.base_color = 0;
    };
    virtual void paint(RNLights & lights);
    virtual const char * name();

    float min_g, max_g;
    
    DRAnimation1Parameters parameters;
};

#endif /* defined(__PlatformData__DRAnimation1__) */
