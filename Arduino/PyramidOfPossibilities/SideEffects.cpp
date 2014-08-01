//
//  SideEffects.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "SideEffects.h"


static uint8_t corner[] = {
  18, 55,92, 129,166,202};

static uint32_t color[] = {
  0xff0000, 0x505050, 0x0000ff, 0xff0000, 0x505050, 0x0000ff};

static uint8_t phase = 0;

static uint8_t getCorner(uint8_t led) {

  for(int i = 0; i < 6; i++)
    if (led < corner[i]) return i;
  return 0;
} 

void SideEffects::paint(RNLights & lights) {
  unsigned long ms = getAnimationMillis();
  if (info.getTaps() || lastPhaseChange + 5000 < ms) {

    phase = (phase+1)%6;
    lastPhaseChange = ms;
    info.printf("Changing to phase %d\n", phase);
  }
  for(int i = 0; i < lights.getNumPixels(); i++) {
    int c = (getCorner(i)+ phase) % 6;
    lights.setPixelColor(i, color[c]);
  }
  lights.setBrightness(64);
  info.showActivity(lights, false, 128);
}

char * SideEffects:: name() {
  return "SideEffects";
}


