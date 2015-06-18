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
#include "VerticalGradient.h"

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
        case   e_VerticalGradient:
            return new VerticalGradient(RNGradient(1, RNGradientWrap, 0x00ff80, 0xffff80));
        case   e_VerticalGradientBlue:
            return new VerticalGradient(RNGradient(1, RNGradientBounce, 0x90ff80, 0xffff80));
            
        default :
            return new TimeRainbowGradient();
    }
}
