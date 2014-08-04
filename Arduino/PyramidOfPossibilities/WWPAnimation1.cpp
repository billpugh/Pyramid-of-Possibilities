//
//  WWPAnimation1.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimation1.h"

void WWPAnimation1::paint(RNLights & lights) {
    
    uint8_t gradiantPosition = getAnimationMillis() * 256 * parameters.gpm / 60000;
    
    uint8_t r,g,b;
    parameters.gradient.getColor(gradiantPosition, r, g, b);

    lights.setAllPixelColors(r, g, b);
    info.showActivity(lights, true, parameters.brightnessWithoutActivity);
   }

  const char * WWPAnimation1:: name() {
    return "WWPAnimation1";
  }
