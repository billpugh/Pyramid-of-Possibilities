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
    e_VerticalGradientRed,

    e_TimeRainbowGradient,
    e_VerticalGradient,
    e_RGBHeartBeat,
    e_WhiteGlow,
    
    e_RadialGradient,
    e_VerticalGradientBlue,
    
    e_GreenPurpleGlow,
    e_AnimationCount
};


Animation * getAnimation(AnimationEnum a );
AnimationEnum nextAnimation(AnimationEnum a );
AnimationEnum firstAnimation( );

Animation * getAnimation(AnimationEnum a );

#endif /* defined(__Cuberosity__Animations__) */
