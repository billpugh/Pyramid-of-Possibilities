//
//  SideEffects.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "SideEffects.h"


static uint8_t corner[] = {
  18, 55,92, 129,166,202};



static uint8_t getCorner(uint8_t led) {

  for(int i = 0; i < 6; i++)
    if (led < corner[i]) return i;
  return 0;
} 

void SideEffects::paint(RNLights & lights) {
  uint32_t ms = getAnimationMillis();
  if (info.getTaps() || lastPhaseChange + parameters.switchTime < ms) {
    phase = (phase+1)%6;
    lastPhaseChange = ms;
  }
  for(int i = 0; i < lights.getNumPixels(); i++) {
    int c = (getCorner(i)+ phase) % 6;
    lights.setPixelColor(i, parameters.colors[c]);
  }
  lights.setBrightness(64);
   info.showActivityWithBrightness(lights, 128);
}

const char * SideEffects:: name() {
  return "SideEffects";
}


