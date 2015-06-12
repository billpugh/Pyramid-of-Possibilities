//
//  VerticalGradient.h
//  Cuberosity
//
//  Created by Bill on 6/11/15.
//  Copyright (c) 2015 Hall of Mirrors. All rights reserved.
//

#ifndef __Cuberosity__VerticalGradient__
#define __Cuberosity__VerticalGradient__

#include <stdio.h>

#include <stdio.h>
#include "easing.h"
#include "easingSelect.h"
#include "Animation.h"
#include "RNGradient.h"

class VerticalGradient : public Animation {
public:
    VerticalGradient();
    virtual void prepare();
    virtual void setPixel(int pos, int side, int height, int horizontalOffset);
private:
    float offset;
    RNGradient gradient;
    
    
};
#endif /* defined(__Cuberosity__VerticalGradient__) */
