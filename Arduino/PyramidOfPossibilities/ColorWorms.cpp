//
//  ColorWorms.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "ColorWorms.h"

const char * ColorWorms:: name() {
  return "ColorWorms";
}

void ColorWorms::paint(RNLights & lights, int8_t speed, int length,
uint8_t r, 
uint8_t g, 
uint8_t b ) {
  int position = (int)((long)getAnimationMillis()/speed);

  AHEasingFunction easingFunction = getEasingFunction(parameters.easingMode, parameters.curveType);
  for(int i = 0; i < length; i++) {
      float p = ((float) i)/length;
      p = easingFunction(p);
      int brightness =
      p * parameters.brightness;
      if (brightness < 0)
          brightness = 0;
      if (brightness > 255)
          brightness = 255;


      int j;
      if (speed > 0)
          j = lights.normalize(position+i);
      else
          j = lights.normalize(position-i);

    lights.addPixelColor(j, r*brightness, g*brightness, b*brightness);
  }
}

void ColorWorms::paint(RNLights & lights) {
    
    int length = info.numLEDs * parameters.lengthFraction;

    paint(lights, parameters.redSpeed, length, 1, 0, 0);
    paint(lights, parameters.greenSpeed, length, 0, 1, 0);
    paint(lights, parameters.blueSpeed, length, 0, 0, 1);
    info.showActivityWithBrightness( lights, getUnsignedTweakValue());
    info.println();
    
}





