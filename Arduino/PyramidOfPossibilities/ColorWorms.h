//
//  ColorWorms.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __ColorWorms__
#define __ColorWorms__

#include "RNAnimation.h"
#include "easingSelect.h"


struct ColorWormsParameters {
    
    
    uint8_t brightness = 120;
    int8_t redSpeed = 20;
    int8_t greenSpeed = 34;
    int8_t blueSpeed = -26;
    
     uint8_t brightnessWithoutActivity = 32;
    
    float lengthFraction = 1/3.0;
    EasingMode easingMode = EaseOut;
    CurveType curveType = CurveTypeQuadratic;

    
    
};


class ColorWorms : public RNAnimation {
public:
    ColorWorms(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(ColorWormsParameters), &parameters) {};
    virtual void paint(RNLights & lights);

    void paint(RNLights & lights, int8_t speed, int length, 
	uint8_t r, 
	uint8_t g, 
	uint8_t b );
  virtual const char * name();
    
    ColorWormsParameters parameters;
    
};


#endif /* defined(__ColorWorms__) */
