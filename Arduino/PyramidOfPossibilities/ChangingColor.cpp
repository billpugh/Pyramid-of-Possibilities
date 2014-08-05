//
//  ChangingColor.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "ChangingColor.h"

void ChangingColor::paint(RNLights & lights) {
    
    uint8_t gradiantPosition = getAnimationMillis() * 256 * parameters.gpm / 60000;
    
    uint8_t r,g,b;
    parameters.gradient.getColor(gradiantPosition, r, g, b);

    lights.setAllPixelColors(r, g, b);
    info.showActivityWithSparkles(lights);
    info.showActivityWithBrightness(lights, parameters.brightnessWithoutActivity);
   }

  const char * ChangingColor:: name() {
    return "ChangingColor";
  }
