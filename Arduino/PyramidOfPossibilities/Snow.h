//
//  Snow.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Snow__
#define __Snow__

#include "RNAnimation.h"


struct SnowParameters {
    uint8_t msPerFlake = 4;
    uint8_t flakesPerTap = 10;
    uint8_t brightnessActivity = 100;
    uint8_t brightnessBase = 20;
    uint8_t brightnessRandom = 50;
    uint8_t brightness = 64;
    uint16_t fade = 750;
};



class Snow : public RNAnimation {
public:
    Snow(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(SnowParameters), &parameters),  snow(info.numLEDs) {
     snow.setFade(0, parameters.fade);
   };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    virtual bool setParameters(int size, char * data);
    
    void addSnowFlake();
    
    unsigned long lastUpdateMillis = 0;
    
    RNLights snow;
    
    SnowParameters parameters;

};

#endif /* defined(__Snow__) */
