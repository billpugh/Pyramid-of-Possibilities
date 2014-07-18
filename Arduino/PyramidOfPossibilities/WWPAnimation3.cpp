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

   int brightness = 50;
   if (since < 1000)
     brightness = 250 - since/5;
   uint8_t hue = (getAnimationMillis() / 10) % 256;
    
    lights.setAllPixelHSVs(0, 255, brightness);
   }

