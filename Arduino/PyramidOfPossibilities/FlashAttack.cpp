//
//  FlashAttack.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "FlashAttack.h"
#include "Arduino.h"

void FlashAttack::paint(RNLights & lights) {

  int value = (int)(255 - info.timeSinceLastTap()*parameters.tapMultiplier);

  int value2 = parameters.minimumValue+info.getLocalActivity() * parameters.activityMultiplier;

    value = max(value, value2);
    value = min(value, 255);


  lights.setAllPixelHSVs(getUnsignedTweakValue(),255,value);

}

const char * FlashAttack:: name() {
  return "FlashAttack";
}

