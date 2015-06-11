//
//  TimeRainbowGradient.h
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#ifndef __Cuberosity__TimeRainbowGradient__
#define __Cuberosity__TimeRainbowGradient__

#include <stdio.h>
#include "easingSelect.h"

class TimeRainbowGradient : Animation {
        public:
    virtual void prepare() {};
    virtual void setPixel(int pos, int side, int height, int horizontalOffset) {};
private:
    int color;


};

#endif /* defined(__Cuberosity__TimeRainbowGradient__) */
