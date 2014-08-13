//
//  GlowFade.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "GlowFade.h"


void GlowFade::getLinear(float pos, uint8_t &value) {
   int result;
   if (pos < parameters.fractionUp) {
	result = (uint8_t) (pos/parameters.fractionUp * 256);
	}
   else {
	result = 255 - (pos - parameters.fractionUp)/parameters.fractionUp *  256;
	}
   if (result < 0) result = 0;
   else if (result > 255) result = 255;
   value = result;
}

    
void GlowFade::paint(RNLights & lights) {
 
    
    unsigned long ms = getAnimationMillis();

    uint16_t cycle = ms / parameters.period;
    uint8_t gradiantPosition = cycle * parameters.gradiantSkip;
    uint8_t r,g,b;
    parameters.gradient.getColor(gradiantPosition, r,g,b);
    
    lights.setAllPixelColors(r,g,b);
    float moment = ((float)(ms % parameters.period)) / parameters.period;
    uint8_t brightness;
    getLinear(moment, brightness);
    lights.setBrightness(brightness);

    info.showActivityWithSparkles(lights);
    }

  const char * GlowFade:: name() {
    return "GlowFade";
  }
