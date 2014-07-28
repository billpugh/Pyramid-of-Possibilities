//
//  WWPAnimation3.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimation3.h"

void WWPAnimation3::paint(RNLights & lights) {

  unsigned long since = info.timeSinceLastTap();

  int brightness = 100;
  if (since < 1000)
    brightness = 250 - since/7;
  uint8_t hue = (getAnimationMillis() / 5) % 256;

  lights.setAllPixelHSVs(hue, 255, brightness);
}

  char * WWPAnimation3:: name() {
    return "WWPAnimation3";
  }
  
