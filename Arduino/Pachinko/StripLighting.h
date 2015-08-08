//
//  StripLighting.h
//  PachinkoTestbed
//
//  Created by Bill on 5/19/15.
//
//

#ifndef __PachinkoTestbed__StripLighting__
#define __PachinkoTestbed__StripLighting__

#include <stdio.h>
#include "hsv2rgb.h"
#include "OctoWS2811.h"

class StripLighting {
public:
    StripLighting(OctoWS2811 & lights, int firstPixel, int numPixels);
    
    void fill();
    void update();
    void setColor(int rgb);
private:
    OctoWS2811 & lights;
    const int firstPixel;
    const int numPixels;
};

#endif /* defined(__PachinkoTestbed__StripLighting__) */
