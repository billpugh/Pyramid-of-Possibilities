//
//  TimeGradient.h
//  Cuberosity
//
//  Created by Bill on 8/8/15.
//  Copyright (c) 2015 Hall of Mirrors. All rights reserved.
//

#ifndef __Cuberosity__TimeGradient__
#define __Cuberosity__TimeGradient__

#include <stdio.h>
#include "easing.h"
#include "easingSelect.h"
#include "Animation.h"
#include "RNGradient.h"

class TimeGradient : public Animation {
public:
    TimeGradient(AHEasingFunction easeUp, AHEasingFunction easeDown, RNGradient gradient, int period) : easeUp(easeUp), easeDown(easeDown), gradient(gradient), period(period) {};
    virtual void prepare();
    virtual void setPixel(int pos, int side, int height, int horizontalOffset);
private:
    int color;
    AHEasingFunction easeUp, easeDown;
    RNGradient gradient;
    int period;
    
    
    
    
};

#endif /* defined(__Cuberosity__TimeGradient__) */
