//
//  Snow.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__Snow__
#define __PlatformData__Snow__

#include "RNAnimation.h"

class Snow : public RNAnimation {
public:
    Snow(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis), lastUpdateMillis(animationStartMillis), snow(info.numLEDs) {
     snow.setFade(animationStartMillis, 750);
   };
    virtual void paint(RNLights & lights);
    
    virtual char * name();
    
    void addSnowFlake();
    
    unsigned long lastUpdateMillis;
    
    RNLights snow;

};

#endif /* defined(__PlatformData__Snow__) */
