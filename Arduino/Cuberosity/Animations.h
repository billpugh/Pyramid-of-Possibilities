//
//  Animations.h
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#ifndef __Cuberosity__Animations__
#define __Cuberosity__Animations__

#include <stdio.h>
#include "Animation.h"

enum  AnimationEnum {
        e_VerticalGradient,
    e_VerticalGradientBlue,
    
    e_TimeRainbowGradient,
    e_RGBHeartBeat,
     e_RadialGradient,

    
    e_AnimationCount
};


Animation * getAnimation(AnimationEnum a );
AnimationEnum nextAnimation(AnimationEnum a );
AnimationEnum firstAnimation( );

Animation * getAnimation(AnimationEnum a );

#endif /* defined(__Cuberosity__Animations__) */
