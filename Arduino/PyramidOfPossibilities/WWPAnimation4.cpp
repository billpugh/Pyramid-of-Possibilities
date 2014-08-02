//
//  WWPAnimation4.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimation4.h"

const char * WWPAnimation4:: name() {
  return "WWPAnimation4";
}

void WWPAnimation4::paint(RNLights & lights, int position, int length, 
uint8_t r, 
uint8_t g, 
uint8_t b ) {
  for(int i = 0; i < length; i++) {
    int offset = i- length/2;
    if (offset < 0)
      offset = offset/2;
    int factor = 255 - 2*offset * 255/length;
    if (factor < 0)
      factor = 0;
    int j = lights.normalize(i+position);
    lights.addPixelColor(j, r*factor/255, g*factor/255, b*factor/255);
  }
}

void WWPAnimation4::paint(RNLights & lights) {

  int length = info.numLEDs/3;

  int rPos = getAnimationMillis()/20;
  int gPos = getAnimationMillis()/34;
  int bPos = -getAnimationMillis()/26;
  paint(lights, rPos, length, 120, 0, 0);
  paint(lights, gPos, length, 0, 120, 0);
  paint(lights, bPos, length, 0, 0, 120);
  info.showActivity(lights, false, 32);

}





