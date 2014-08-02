//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"

void WWPAnimationTest::paint(RNLights & lights) {
  
  float timeInMinutes =  getAnimationMillis()/60000.0;

  float basePos =  timeInMinutes * rpm;
//  info.printf("rotation %f -> %d\n", timeInMinutes, baseHue);
//  
  for(int i = 0; i < lights.getNumPixels(); i++) {
    float pos = basePos;
    if (global)
      pos += info.getGlobalAngle(i)/360;
    else
      pos += ((float)i)/info.numLEDs;
      lights.setPixelColor(i, gradient.getColor( pos*256*repeats ));
  }

  info.showActivity(lights, false, 40);

}

char * WWPAnimationTest:: name() {
  return "WWPAnimationTest";
}

