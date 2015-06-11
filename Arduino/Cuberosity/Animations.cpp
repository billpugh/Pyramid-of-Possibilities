//
//  Animations.cpp
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#include "Animations.h"

AnimationEnum nextAnimation(AnimationEnum a ) {
    a = (AnimationEnum) (a+1);
    
}
AnimationEnum firstAnimation( ) {
    a = (AnimationEnum) (0);
    
}


Animation * getAnimation(AnimationEnum a ) {
    switch (a) {
            
        case e_TimeRainbowGradient:
            return new TimeRainbowGradient();
            case
        case e_RGBHeartBeat:
            return new RGBHeartBeat();
        default :
            return new TimeRainbowGradient();
    }
}