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
#include "easing.h"
#include "easingSelect.h"
#include "Animation.h"

class TimeRainbowGradient : public Animation {
        public:
        TimeRainbowGradient() {};
    virtual void prepare();
    virtual void setPixel(int pos, int side, int height, int horizontalOffset);
private:
    int color;


};

#endif /* defined(__Cuberosity__TimeRainbowGradient__) */
