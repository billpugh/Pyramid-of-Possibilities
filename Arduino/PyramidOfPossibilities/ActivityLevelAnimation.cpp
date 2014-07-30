//
//  ActivityLevelAnimation.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "ActivityLevelAnimation.h"



  ActivityLevelAnimation::ActivityLevelAnimation(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis), level(0) {};


void ActivityLevelAnimation::paint(RNLights & lights) {
    uint16_t num = info.numLEDs * info.getLocalActivity();
    if (num > info.numLEDs)
      num = info.numLEDs;
    if (level < num)
      level = num;
    else 
      level = (15*level + num)/16;
    if (info.getTaps()) 
      info.printf("Taps %x\n", info.getTaps());
    int shift = info.timeSinceLastTap()/4;
    if (shift > 255) shift = 255;
    for(int i = 0; i < level; i++)
      lights.setPixelColor(i, 255-shift, 0, shift);
    lights.setBrightness(128);
   
   }

  char * ActivityLevelAnimation:: name() {
    return "ActivityLevelAnimation";
  }
