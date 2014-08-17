//
//  MMAnimation0.cpp
//  PlatformData
//
//  Created by Meelow.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "MMAnimation1.h"
#include <math.h>

#define MIN_BRIGHTNESS 20
#define MAX_BRIGHTNESS 250
#define STEP_BRIGHTNESS 1

#define DEBUG true  // print msgs over serial

const float logOneHalf = -.6931471806; // log(1/2);

void MMAnimation1::paint(RNLights & lights)
{

    uint32_t now = getAnimationMillis();
    uint32_t since = now - lastUpdate;
    lastUpdate = now;

    double logFade = logOneHalf * since / parameters.halfLifeMillis;
    brightness *= exp(logFade);

    if (info.getTaps()) {
        brightness += parameters.increaseOnTap;
        // brightness is allowed to go above 1.0
    }

    float pulseBrightness =
    1.0 - info.timeSinceLastTap()/parameters.pulseWidth;
    if (pulseBrightness < 0)
        pulseBrightness = 0.0;

    AHEasingFunction easingFunction = getEasingFunction(parameters.easingMode, parameters.curveType);
    float b = easingFunction(fmin(1.0,fmax(brightness,pulseBrightness)));

    int finalBrightness = parameters.minimumBrightness + b * (parameters.maxBrightness - parameters.minimumBrightness);

    // gradiant uses cycle value
    uint8_t gradientPosition = getAnimationCycles()*256;
    uint32_t color = parameters.gradient.getColor(gradientPosition);

    lights.setAllPixelColors(color);
    lights.setBrightness(finalBrightness);
}

const char * MMAnimation1:: name() {
	return "Traces(MM1)";
}
