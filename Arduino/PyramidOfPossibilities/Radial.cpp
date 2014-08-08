//
//  Radial.h
//
//  Created by Danny on 8/7/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Radial.h"
#include "Constants.h"
#include <math.h>

#define RN_RADIAL_DEBUG 1

float locationForT(float t) {

    if ( t > .5 ) {
        return (1 - t) * constants.pyramidRadiusFromGround * 2;
    }
    return t * constants.pyramidRadiusFromGround * 2;
}


void Radial::paint(RNLights & lights) {
    
    unsigned long millis = getAnimationMillis();

    // t will be a number between 0 and 1.    
    /// TODO: Need help setting up parameters that we want for speed, etc.
    float t = (float)((millis / 10 ) % parameters.period) / (float)parameters.period;

    // calculate position of the radial based on t
    float r = locationForT(t);


    float innerShellBoundry = r - parameters.thickness;
    float outerShellBoundry = r + parameters.thickness;
    float doublethickness = parameters.thickness * 2;

    for(int i = 0; i < lights.getNumPixels(); i++) {

        float pixelRadius = info.getGlobalRadiusGround(i);

        RNGradient *gradientToUse = 0;
        float point = 0;
        
        // determine color gradient to use based on whether you are inside, or outside, or within the shell of the radial.

        if ( pixelRadius < innerShellBoundry ) {
            
            // inside 
            gradientToUse = &(parameters.gradientInside);
            point = pixelRadius / constants.pyramidRadiusFromGround;

        } else if ( pixelRadius < outerShellBoundry ) {
            
            // shell 
            gradientToUse = &(parameters.gradientShell);
            point = (pixelRadius - innerShellBoundry ) / doublethickness;

        } else {

            // outside
            gradientToUse = &(parameters.gradientOutside);
            point = pixelRadius / constants.pyramidRadiusFromGround;
        }

        // find the color now
        uint32_t color = gradientToUse->getColor(point * 255);
        lights.setPixelColor(i,color);

        // debugging stuff
#if RN_RADIAL_DEBUG
        static int once = 0;
        if ( !once && i == 0) {
            once = 1;
            info.printf("pixelRadius = %.2f. Period = %u\n", pixelRadius, parameters.period);
        }
        static int n = 0;
        if ( i == 0 && (++n%10 == 0)) {
            info.printf("Millis = %lu,  PixelRadius = %.2f, T = %f, R = %f.  innerShellBoundry = %f,  outerShellBoundry = %f\n", millis, pixelRadius, t, r, innerShellBoundry, outerShellBoundry);
        }
#endif /* RN_RADIAL_DEBUG */

    }

    info.showActivityWithSparkles(lights);
    
}

const char * Radial:: name() {
    return "Radial";
}

