//
//  Snow.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__Snow__
#define __PlatformData__Snow__

#include "RNAnimation.h"


struct SnowParameters {
    uint8_t brightnessActivity = 100;
    uint8_t brightnessBase = 20;
    uint8_t brightnessRandom = 50;
    
    uint8_t msPerFlake = 4;
    uint8_t flakesPerTap = 10;
    uint8_t brightness = 64;
    
    
};



class Snow : public RNAnimation {
public:
    Snow(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(SnowParameters), &parameters), lastUpdateMillis(animationStartMillis), snow(info.numLEDs) {
     snow.setFade(animationStartMillis, 750);
   };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
    void addSnowFlake();
    
    unsigned long lastUpdateMillis;
    
    RNLights snow;
    
    SnowParameters parameters;

};

#endif /* defined(__PlatformData__Snow__) */
