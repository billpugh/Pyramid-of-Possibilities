//
//  RGBHeartBeat.h
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#ifndef __Cuberosity__RGBHeartBeat__
#define __Cuberosity__RGBHeartBeat__

#include <stdio.h>
#include "Animation.h"
#include "easingSelect.h"


class RGBHeartBeat : public Animation {
public:
    RGBHeartBeat() {};
    virtual void prepare();
    virtual void setPixel(int pos, int side, int height, int horizontalOffset);
private:
    float effectSize;
    AHEasingFunction easingFunction = getEasingFunction(EaseIn, CurveTypeBounce);

    
    
};

#endif /* defined(__Cuberosity__RGBHeartBeat__) */
