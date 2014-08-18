//
//  ExpandingSphere.cpp
//  PlatformCode
//
//  Created by Bill on 8/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "ExpandingSphere.h"
#include "Constants.h"
#include "ledPositions.h"

#include <math.h>

void ExpandingSphere::paint(RNLights & lights) {


    uint32_t outerRadius =
    2.0 * constants.pyramidRadiusFromGround * getEffectFraction();
    int32_t innerRadius =
        2.0 * constants.pyramidRadiusFromGround * (getEffectFraction() - parameters.thickness);
    if (innerRadius < 0)
        innerRadius = 0;

    outerRadius = outerRadius * outerRadius;
    innerRadius = innerRadius * innerRadius;
    uint32_t xOffset = info.x - parameters.x;
    uint32_t yOffset = info.y - parameters.y;
    uint32_t zOffset = info.z - parameters.z;

    uint32_t zSquared = zOffset * zOffset;

    for(int i = 0; i < lights.getNumPixels(); i++) {

        uint32_t xSquared = xOffset + getLEDXPosition(i);
        xSquared = xSquared * xSquared;
        uint32_t ySquared = yOffset + getLEDYPosition(i);
        ySquared = ySquared * ySquared;
        uint32_t dSquared = xSquared + ySquared + zSquared;
        if (innerRadius <= dSquared && dSquared <= outerRadius)
            lights.setPixelColor(i, parameters.color);

    }
    






}

const char * ExpandingSphere:: name() {
    return "ExpandingSphere";
}

