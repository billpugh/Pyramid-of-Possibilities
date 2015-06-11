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

enum  AnimationEnum {
    
    e_TimeRainbowGradient,
    e_RGBHeartBeat,
    
    e_AnimationCount
}

Animation * getAnimation(AnimationEnum a );
AnimationEnum nextAnimation(AnimationEnum a );
AnimationEnum firstAnimation( );

Animation * getAnimation(AnimationEnum a )

#endif /* defined(__Cuberosity__Animations__) */
