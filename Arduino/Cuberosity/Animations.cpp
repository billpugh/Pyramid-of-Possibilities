//
//  Animations.cpp
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#include "Animations.h"
#include "TimeRainbowGradient.h"
#include "RGBHeartBeat.h"
#include "RadialGradient.h"

AnimationEnum nextAnimation(AnimationEnum a ) {
    a = (AnimationEnum) (a+1);
    if (a == e_AnimationCount)
        return firstAnimation();
    else return a;
    
}
AnimationEnum firstAnimation( ) {
    return  (AnimationEnum) (0);
    
}


Animation * getAnimation(AnimationEnum a ) {
    switch (a) {
            
        case e_TimeRainbowGradient:
            return new TimeRainbowGradient();
            
        case e_RGBHeartBeat:
            return new RGBHeartBeat();
        case e_RadialGradient:
            return new RadialGradient();
        default :
            return new TimeRainbowGradient();
    }
}
