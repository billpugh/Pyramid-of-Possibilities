//
//  RNDigit.h
//  PachinkoTestbed
//
//  Created by Bill on 4/20/15.
//
//

#ifndef __PachinkoTestbed__RNDigit__
#define __PachinkoTestbed__RNDigit__

#include <stdio.h>
#include "OctoWS2811.h"

class RNDigit {
    public:
    RNDigit(OctoWS2811 & lights, int firstPixel);
    RNDigit(OctoWS2811 & lights, int firstPixel, int skipPixels, int numPixels);
    
    int nextPixel();
    void setDigit(int digit);
    void setColor(int rgb);
    void test(int rgb);
    void clear();
    
    static const int MAX_PIXELS = 41;
    
private:
    OctoWS2811 & lights;
    const int firstPixel;
    const int skipPixels;
    const int numPixels;

private:
    int rgb;
};


#endif /* defined(__PachinkoTestbed__RNDigit__) */
