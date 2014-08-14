//
//  Mute.cpp
//
//  Created by Bill on 8/13/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Mute.h"

void Mute::paint(RNLights & lights) {
    lights.setAllPixelColors(parameters.brightness,
                             parameters.brightness,
                             parameters.brightness
                             );
}

const char * Mute:: name() {
    return "Mute";
}