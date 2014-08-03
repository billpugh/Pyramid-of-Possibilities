//
//  FlashAttack.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "FlashAttack.h"

void FlashAttack::paint(RNLights & lights) {

  int value = 255 - info.timeSinceLastTap()*2;
  if (value < 20)
    value = 20;
  int value2 = 20+info.getLocalActivity() * 400;
  if (value2 > 255) value2 = 255;
  if (value < value2)
    value = value2;
  lights.setAllPixelHSVs(hue,255,value);
  //  
  //    uint16_t length = (getAnimationMillis() / 10) % (info.numLEDs*2);
  //    if (length >= info.numLEDs)
  //      length = info.numLEDs*2-1-length;
  //    if (length >=  info.numLEDs | length < 0)
  //      length = 0;
  //    for(int i = 0; i < length; i++)
  //      lights.setPixelColor(i, 64, 64, 64);
}

char * FlashAttack:: name() {
  return "FlashAttack";
}

