//
//  ActivityLevelAnimation.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "ActivityLevelAnimation.h"
#include <Arduino.h>



ActivityLevelAnimation::ActivityLevelAnimation(RNInfo & info, unsigned long animationStartMillis)
: 
RNAnimation(info, animationStartMillis), level(0), direction(random(2)*2-1) {
};


void ActivityLevelAnimation::paint(RNLights & lights) {
  float activity = info.getLocalActivity()/3;
  if (activity >= 0.15)
    activity = 0.15;
  uint16_t num = info.numLEDs *activity+1;
  if (level < num)
    level = num;
  else 
    level = (15*level + num)/16;


  int hue = info.timeSinceLastTap()/8;
  if (hue > 180) hue = 180;

  int16_t position =  0; // getAnimationMillis() * info.numLEDs/10000;
  for(int i = 0; i < level; i++) 
    for(int side = 0; side < 6; side++) {
      int offset = side * info.numLEDs/6;
      lights.setPixelHSV(lights.normalize(position+offset+i), hue, 255, 255 - i*200/level);
      lights.setPixelHSV(lights.normalize(position+offset-i), hue, 255, 255 - i*200/level);
    }
  lights.setBrightness(128);

}

char * ActivityLevelAnimation:: name() {
  return "ActivityLevelAnimation";
}

