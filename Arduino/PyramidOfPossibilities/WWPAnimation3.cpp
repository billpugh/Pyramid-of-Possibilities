//
//  WWPAnimation3.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimation3.h"

void WWPAnimation3::paint(RNLights & lights) {

   uint8_t hue = (getAnimationMillis() / 20) % 256;

  lights.setAllPixelHSVs(hue, 255, 255);
  info.showActivity(lights, true, 16);
}

  const char * WWPAnimation3:: name() {
    return "WWPAnimation3";
  }
  
