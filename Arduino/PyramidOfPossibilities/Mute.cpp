//
//  Mute.cpp
//
//  Created by Bill on 8/13/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Mute.h"

void Mute::paint(RNLights & lights) {
    uint8_t brightness = 20 + getUnsignedTweakValue()/5;
    lights.setAllPixelColors(brightness, brightness, brightness);
}

const char * Mute:: name() {
    return "Mute";
}