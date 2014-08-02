//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"

void WWPAnimationTest::paint(RNLights & lights) {

  uint8_t baseHue = (getAnimationMillis() / 10) % 256;

  for(int i = 0; i < lights.getNumPixels(); i++) {
    lights.setPixelColor(i, gradient.getColor(baseHue+i*256*4/info.numLEDs));
  }
  lights.setBrightness(40);
  info.showActivity(lights, false, 16);

}

char * WWPAnimationTest:: name() {
  return "WWPAnimationTest";
}

