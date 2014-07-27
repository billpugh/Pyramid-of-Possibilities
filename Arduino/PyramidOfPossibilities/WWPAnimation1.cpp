//
//  WWPAnimation1.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimation1.h"

void WWPAnimation1::paint(RNLights & lights) {
    uint8_t hue = (getAnimationMillis() / 10) % 256;
    lights.setAllPixelHSVs(hue, 255, 255);
   }

  char * WWPAnimation1:: name() {
    return "WWPAnimation1";
  }
