//
//  Swirl.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Swirl.h"

void Swirl::paint(RNLights & lights) {
    
    uint16_t length = parameters.lengthFraction * info.numLEDs;
    
    float animationMinutes = getAnimationMinutes();
    uint16_t startPosition =  lights.getNumPixels() * parameters.rpm * animationMinutes;
    int gradientPosition = 256 * parameters.gpm * animationMinutes;
    uint32_t headColor = parameters.headGradient.getValue(gradientPosition);
    uint32_t tailColor = parameters.tailGradient.getValue(gradientPosition);
    
    RNGradient stripGradient(parameters.headGradient.isHSV, RNGradientCapped, headColor, tailColor);
    
    for(int i = 0; i < length; i++) {
        int pixelPosition = startPosition - i;
        int pixelGradientPosition = i * 256 / length;
        lights.setPixelColor( lights.normalize(pixelPosition), stripGradient.getColor(pixelGradientPosition));
    }
    
    info.showActivityWithBrightness(lights, 40);
}

const char * Swirl:: name() {
    return "Swirl";
}

