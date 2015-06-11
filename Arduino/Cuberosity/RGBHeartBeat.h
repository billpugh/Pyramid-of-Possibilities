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


class RGBHeartBeat : Animation {
public:
    virtual void prepare() {};
    virtual void setPixel(int pos, int side, int height, int horizontalOffset) {};
private:
    float effectSize;
    AHEasingFunction easingFunction = getEasingFunction(EaseIn, CurveTypeBounce);

    
    
};

#endif /* defined(__Cuberosity__RGBHeartBeat__) */
