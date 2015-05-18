//
//  Animations.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Animations__
#define __Animations__


enum  AnimationEnum {

        e_ActivityLevelAnimation,
        e_Chasers,
    
    // e_Mute,

    // Animations defined by Bill Pugh (WWP)
    e_ChangingColor,
    e_CircularGradient,
    e_ColorWorms,
    e_FlashAttack,
    e_Snow,
    e_Swirl,
    e_GlowFade,

    e_Beacon,
    e_WWPAnimationTest,

    e_SideEffects,

    // Danny's animations.
    e_Qbert,   // RGB simple
    e_DRAnimation1,   // RNBeam
    //e_FlashEcho,

    // Antoine's animations
    //e_MovingFaces,
    //e_Explosion,

    // Branden's animations
    e_Kittens,

    // meelows animations
	e_MMAnimation1,   		// strip color cycles through HSV, tapping activity brightens, no activity fades out

    // Not an actual enum, just the value used to give us the count of the number of enums
    e_AnimationCount,
    e_LiftOff,
    e_Radial,
     e_Flashes,
   
    

};


const AnimationEnum firstAnimation = e_ActivityLevelAnimation;

#endif /* defined(__Animations__) */

