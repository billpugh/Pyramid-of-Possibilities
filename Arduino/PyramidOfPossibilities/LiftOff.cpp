//
//  LiftOff.cpp
//  PlatformCode
//
//  Created by Bill on 8/16/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "LiftOff.h"
#include "Constants.h"
#include <math.h>


void LiftOff::paint(RNLights & lights) {

    float c = getAnimationCycles()/4.0;
    float cycle = c - floor(c);

    info.printf("%6dms  %11f %11f %11f %11f\n", getAnimationMillis(), c, cycle,
   cycle*parameters.overlap, (cycle+1.0)*parameters.overlap);
   
    if (!paintWave(lights, cycle*parameters.overlap))
        paintWave(lights, (cycle+1.0)*parameters.overlap);
    info.showActivityWithSparkles(lights);
}

bool LiftOff::paintWave(RNLights & lights, float height) {

//    AHEasingFunction easingFunction = getEasingFunction(parameters.easingMode, parameters.curveType);
//    height = easingFunction(height);

    float topHeight = height * constants.pyramidHeight;
    float bottomHeight = (height - parameters.thickness) * constants.pyramidHeight;

    float gradientPosition = (info.y - bottomHeight)/(topHeight - bottomHeight);

    if (0.0 <= gradientPosition &&
        gradientPosition < 1) {
 info.printf(" gradient %11f\n", gradientPosition);
 
        uint32_t color = parameters.gradient.getColor(256*gradientPosition);
        lights.setAllPixelColors(color);
        return true;
    }
    return false;
}



const char * LiftOff::name() {
    return "LiftOff";
}
