//
//  Radial.h
//
//  Created by Danny on 8/7/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Radial.h"
#include "Constants.h"
#include <math.h>

float locationForT(float t) {

    if ( t > .5 ) {
        return (1 - t) * PYRAMID_RADIUS * 2;
    }
    return t * PYRAMID_RADIUS * 2;
}


void Radial::paint(RNLights & lights) {
    
    unsigned long millis = getAnimationMillis();

    // t will be a number between 0 and 1.
    /// TODO: Need help setting up parameters that we want for speed, etc.
    float t = (float)((millis / 10 ) % parameters.period) / (float)parameters.period;

    // calculate position of the radial based on t
    float r = locationForT(t);

    for(int i = 0; i < lights.getNumPixels(); i++) {

        float pixelRadius = info.getGlobalRadiusGround(i);

        RNGradient *gradientToUse = 0;
        float point = 0;
        float innerShellBoundry = r - parameters.thickness;
        float outerShellBoundry = r + parameters.thickness;
        
        if ( pixelRadius < innerShellBoundry ) {
            
            // inside 
            gradientToUse = &(parameters.gradientInside);
            point = pixelRadius / PYRAMID_RADIUS;

        } else if ( pixelRadius < outerShellBoundry ) {
            
            // shell 
            gradientToUse = &(parameters.gradientShell);
            point = (pixelRadius - innerShellBoundry ) / (parameters.thickness * 2);

        } else {

            // outside
            gradientToUse = &(parameters.gradientOutside);
            point = pixelRadius / PYRAMID_RADIUS;
        }

        // find the color now
        uint32_t color = gradientToUse->getColor(point);
        lights.setPixelColor(i,color);

        static int once = 0;
        if ( !once && i == 0) {
            once = 1;
            info.printf("pixelRadius = %.2f. Period = %u\n", pixelRadius, parameters.period);
        }
        static int n = 0;
        if ( i == 0 && (++n%10 == 0)) {
            info.printf("Millis = %lu,  PixelRadius = %.2f, T = %f, R = %f.  innerShellBoundry = %f,  outerShellBoundry = %f\n", millis, pixelRadius, t, r, innerShellBoundry, outerShellBoundry);
        }
    }

    info.showActivityWithSparkles(lights);
    
}

const char * Radial:: name() {
    return "Radial";
}

