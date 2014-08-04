//
//  Snow.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Snow.h"


// Called if there are any parameters from central
bool Snow::setParameters(int size, char * data) {
    if (!RNAnimation::setParameters(size,data))
        return false;
    snow.setFade(getAnimationMillis(), parameters.fade);
    return true;
}

void Snow::addSnowFlake() {
  int v = parameters.brightnessActivity * info.getLocalActivity() + parameters.brightnessBase + info.getRandom(parameters.brightnessRandom);
  if (v > 255)
    v = 255;
  snow.setPixelColorMax(info.getRandomPixel(), v, v, v);
}

void Snow::paint(RNLights & lights) {

  unsigned long ms = getAnimationMillis();
  snow.fade(ms);
  do {
    addSnowFlake();
    lastUpdateMillis += parameters.msPerFlake;
  } 
  while (lastUpdateMillis < ms);
  if (info.getTaps())
    for(int i = 0; i < parameters.flakesPerTap; i++)
      addSnowFlake();
  lights.copyPixels(snow);
  lights.setBrightness(parameters.brightness);

}

const char * Snow:: name() {
  return "Snow";
}




