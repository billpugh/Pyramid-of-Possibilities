//
//  Beacon.cpp
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Beacon.h"
#include "Constants.h"
#include <math.h>

void Beacon::paint(RNLights & lights) {
    
    float angle = getAnimationCycles();


    float height = (float)info.z / (float)constants.pyramidRadiusFromGround;
    uint32_t platformZValue = height * 255;
    
    for(int i = 0; i < lights.getNumPixels(); i++) {
        if (parameters.onlyExterior && !info.isExteriorLED(i)) {
            lights.setPixelColor(i, parameters.baseGradient.getColor(platformZValue));
            continue;
        };
        float diff = (info.getGlobalAngle(i) - angle) * parameters.numBeacons;
        
        float a = diff - roundf(diff);
        if (a < 0) a = -a;
        if (a < parameters.width) {
            uint8_t gradientPosition = a*256/parameters.width;
            uint32_t color = parameters.gradient.getColor(gradientPosition);
            lights.setPixelColor(i,color);
        } else {
            lights.setPixelColor(i, parameters.baseGradient.getColor(platformZValue));
        }
    }

    info.showActivityWithSparkles(lights);
    
}

const char * Beacon:: name() {
    return "Beacon";
}

