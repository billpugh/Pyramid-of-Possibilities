//
//  Snow.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Snow.h"

void Snow::addSnowFlake() {
  int v = 400 * info.getLocalActivity() + 20 + info.getRandom(50);
  if (v > 255)
    v = 255;
  snow.setPixelColorMax(info.getRandomPixel(), v, v, v);
}

void Snow::paint(RNLights & lights) {

  unsigned long ms = getAnimationMillis();
  snow.fade(ms);
  do {
    addSnowFlake();
    lastUpdateMillis += 4;
  } 
  while (lastUpdateMillis < ms);
  if (info.getTaps())
    for(int i = 0; i < 10; i++)
      addSnowFlake();
  lights.copyPixels(snow);
  lights.setBrightness(64);

}

char * Snow:: name() {
  return "Snow";
}




