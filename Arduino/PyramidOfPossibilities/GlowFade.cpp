//
//  GlowFade.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "GlowFade.h"
#include <math.h>


void GlowFade::getLinear(float pos, uint8_t &value) {

    if (pos < parameters.fractionUp)
        pos /=parameters.fractionUp ;

    else
        pos =  (1 - (pos - parameters.fractionUp)/(1-parameters.fractionUp));
    int result =   parameters.maxBrightness * pos;
	if (result < 0) result = 0;
    else if (result > 255) result = 255;
    value = result;
}

    
void GlowFade::paint(RNLights & lights) {
 
    
    float cycle = getAnimationCycles();


    uint8_t gradiantPosition = floor(cycle)* parameters.gradiantSkip;
    uint8_t r,g,b;
    parameters.gradient.getColor(gradiantPosition, r,g,b);
    
    lights.setAllPixelColors(r,g,b);
    float moment = cycle - floor(cycle);
    uint8_t brightness;
    getLinear(moment, brightness);
    lights.setBrightness(brightness);

    info.showActivityWithSparkles(lights);
    }

  const char * GlowFade:: name() {
    return "GlowFade";
  }
