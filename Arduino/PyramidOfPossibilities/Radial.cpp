//
//  Radial.h
//
//  Created by Danny on 8/7/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Radial.h"
#include "Constants.h"
#include <math.h>

// #define RN_RADIAL_DEBUG 1

float locationForT(float t) {

    if ( t > .5 ) {
        return (1 - t) * constants.pyramidRadiusFromGround * 2;
    }
    return t * constants.pyramidRadiusFromGround * 2;
}


void Radial::paint(RNLights & lights) {
    
    float minutes = getAnimationMinutes();

    // t will be a number between 0 and 1.    
    /// TODO: Need help setting up parameters that we want for speed, etc.
    float t =  parameters.bpm  * minutes;
    t = t - floorf(t);
    AHEasingFunction easingFunction
    = getEasingFunction(parameters.easingMode, parameters.curveType);
    t = easingFunction(t);

    // calculate position of the radial based on t
    float r = locationForT(t);

    float thickness = parameters.thickness
    * constants.pyramidRadiusFromGround;

    float innerShellBoundry = r - parameters.thickness;
    float outerShellBoundry = r + parameters.thickness;
    float doublethickness = parameters.thickness * 2;

    int in = 0;
    int out = 0;
    int middle = 0;
    float minDistance = 100000;
    float maxDistance = 0;


    for(int i = 0; i < lights.getNumPixels(); i++) {

        float pixelRadius = info.getGlobalRadiusGround(i);

        if (minDistance > pixelRadius)
            minDistance = pixelRadius;
        if (maxDistance < pixelRadius)
            maxDistance = pixelRadius;

        RNGradient *gradientToUse = 0;
        float point = 0;
        
        // determine color gradient to use based on whether you are inside, or outside, or within the shell of the radial.

        if ( pixelRadius < innerShellBoundry ) {
            
            // inside 
            gradientToUse = &(parameters.gradientInside);
            point = pixelRadius / innerShellBoundry;
            in++;

        } else if ( pixelRadius < outerShellBoundry ) {
            
            // shell 
            gradientToUse = &(parameters.gradientShell);
            point = (pixelRadius - innerShellBoundry ) / doublethickness;
            middle++;

        } else {

            // outside
            gradientToUse = &(parameters.gradientOutside);
            point = pixelRadius / constants.pyramidRadiusFromGround;
            out++;
        }

        // find the color now
        uint32_t color = gradientToUse->getColor(point * 255);
        lights.setPixelColor(i,color);

        // debugging stuff
#ifdef RN_RADIAL_DEBUG
        static int once = 0;
        if ( !once && i == 0) {
            once = 1;
            info.printf("pixelRadius = %.2f. Period = %u\n", pixelRadius, parameters.bpm);
        }
        static int n = 0;
        if ( i == 0 && (++n%10 == 0)) {
            info.printf("minutes = %f,  PixelRadius = %.2f, T = %f, R = %f.  innerShellBoundry = %f,  outerShellBoundry = %f\n", minutes, pixelRadius, t, r, innerShellBoundry, outerShellBoundry);
        }
#endif /* RN_RADIAL_DEBUG */

    }

    info.printf("Radial ms = %5d, minutes = %10f, t=%10f, r = %10f, min = %10f, max = %10f, in/mid/out = %3d/%3d/%3d\n",
                getAnimationMillis(), minutes, t, r, minDistance, maxDistance, in, middle,out);
    info.showActivityWithSparkles(lights);
    
}

const char * Radial:: name() {
    return "Radial";
}

