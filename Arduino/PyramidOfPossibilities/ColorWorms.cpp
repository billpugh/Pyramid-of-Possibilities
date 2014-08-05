//
//  ColorWorms.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "ColorWorms.h"

const char * ColorWorms:: name() {
  return "ColorWorms";
}

void ColorWorms::paint(RNLights & lights, int position, int length, 
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

void ColorWorms::paint(RNLights & lights) {
    
    int length = info.numLEDs * parameters.lengthFraction;
    
    int rPos = getAnimationMillis()/parameters.redSpeed;
    int gPos = getAnimationMillis()/parameters.greenSpeed;
    int bPos = getAnimationMillis()/parameters.blueSpeed;
    paint(lights, rPos, length, parameters.brightness, 0, 0);
    paint(lights, gPos, length, 0, parameters.brightness, 0);
    paint(lights, bPos, length, 0, 0, parameters.brightness);
    info.showActivityWithBrightness( lights, parameters.brightnessWithoutActivity);
    
}





