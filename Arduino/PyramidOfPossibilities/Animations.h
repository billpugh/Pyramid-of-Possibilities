//
//  Animations.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Animations__
#define __Animations__

#include "RNAnimation.h"


enum  AnimationEnum {

      e_Beacon,
    // Branden's animations
    e_Kittens,


  e_FlashEcho,

    e_Radial,
    e_Mute,


    e_GlowFade,

    e_WWPAnimationTest,
    e_ActivityLevelAnimation,

    e_SideEffects,

    // Animations defined by Bill Pugh (WWP)
    e_ChangingColor,
    e_CircularGradient,

    e_ColorWorms,
    e_Chasers,
    e_FlashAttack,
    e_Snow,
    e_Swirl,

    // Danny's animations.
    e_Qbert,   // RGB simple
    e_DRAnimation1,   // RNBeam

    // Antoine's animations
    e_Flashes,
    e_AVEAnimation1,

    // meelows animations
    e_MMAnimation0,   		// strip color cycles through HSV, tapping activity brightens, no activity fades out
	e_MMAnimation1,   		// same as 0, but takes globaltime for cycling through HSV


    // Not an actual enum, just the value used to give us the count of the number of enums
    e_AnimationCount};


RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis );

#endif /* defined(__Animations__) */

