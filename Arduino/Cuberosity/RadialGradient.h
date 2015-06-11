//
//  RadialGradient.h
//  Cuberosity
//
//  Created by Bill on 6/11/15.
//  Copyright (c) 2015 Hall of Mirrors. All rights reserved.
//

#ifndef __Cuberosity__RadialGradient__
#define __Cuberosity__RadialGradient__

#include <stdio.h>

#include "Animation.h"
#include "led_sysdefs.h"
#include "hsv2rgb.h"

class RadialGradient : public Animation {
public:
    RadialGradient() {};
    virtual void prepare();
    virtual void setPixel(int pos, int side, int height, int horizontalOffset);
private:
    float offset;
        CHSV hsv;
    
    
};


#endif /* defined(__Cuberosity__RadialGradient__) */
