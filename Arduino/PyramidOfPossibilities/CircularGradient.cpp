//
//  CircularGradient.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "CircularGradient.h"


void CircularGradient::paint(RNLights & lights) {

  uint16_t gradientSize = 256 * parameters.repeats;
  float baseAngle =  getAnimationCycles();

  for(int i = 0; i < lights.getNumPixels(); i++) {
      float angle;
      if (parameters.global)
          angle = info.getGlobalAngle(i);
      else
          angle = info.getLocalAngle(i);


      uint16_t gradientPosition = (baseAngle+angle)*gradientSize;
      lights.setPixelColor(i, parameters.gradient.getColor(gradientPosition/parameters.chunkSize * parameters.chunkSize));
    }

  info.showActivityWithBrightness(lights, parameters.brightnessWithoutActivity);
}

const char * CircularGradient:: name() {
  return "CircularGradient";
}

