//
//  Swirl.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Swirl.h"

void Swirl::paint(RNLights & lights) {
    
    
    uint16_t startPosition =  lights.getNumPixels() * rpm * getAnimationMillis()  / 60000.0;
    int gradientPosition = 256 * gpm * getAnimationMillis()  / 60000.0;
    uint32_t headColor = headGradient.getValue(gradientPosition);
    uint32_t tailColor = tailGradient.getValue(gradientPosition);
    
    RNGradient stripGradient(headGradient.isHSV, RNGradientCapped, headColor, tailColor);
    
    
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

