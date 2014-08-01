//
//  Animations.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__Animations__
#define __PlatformData__Animations__

#include "RNAnimation.h"


enum  AnimationEnum {

  e_WWPAnimationTest,
  e_ActivityLevelAnimation,
  e_GlowFade,
  e_SideEffects,
  
  // Animations defined by Bill Pugh (WWP)
  e_WWPAnimation1,
  e_WWPAnimation2,
  e_WWPAnimation3,
  e_WWPAnimation4,
  e_WWPAnimation5,
  e_FlashAttack,

  // Danny's animations.
  e_DRAnimation0,   // RGB simple
  e_DRAnimation1,   // RNBeam
  


  // Not an actual enum, just the value used to give us the count of the number of enums
  e_AnimationCount};


RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis );

#endif /* defined(__PlatformData__Animations__) */

