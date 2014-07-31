//
//  WWPAnimationTest.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimationTest.h"

void WWPAnimationTest::paint(RNLights & lights) {
    uint16_t length = (getAnimationMillis() / 100) % (info.numLEDs*2);
    if (length >= info.numLEDs)
      length = info.numLEDs*2-1-length;
    if (length >=  info.numLEDs | length < 0)
      length = 0;
    for(int i = 0; i < length; i++)
      lights.setPixelColor(i, 40, 40, 40);
   }

  char * WWPAnimationTest:: name() {
    return "WWPAnimationTest";
  }
