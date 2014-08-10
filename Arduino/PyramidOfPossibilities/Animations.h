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
  
  // Animations defined by Bill Pugh (WWP)
  e_WWPAnimation1,
  e_WWPAnimation2,
  e_WWPAnimation3,
  e_WWPAnimation4,
  e_WWPAnimation5,

  // Danny's animations.
  e_DRAnimation0,   // RGB simple
  e_DRAnimation1,   // RNBeam
  
  // milos animations
  e_MMAnimation0,   		// strip color cycles through HSV, tapping activity brightens, no activity fades out
  e_MMAnimation1,   		// same as 0, but takes globaltime for cycling through HSV
  

  // Not an actual enum, just the value used to give us the count of the number of enums
  e_AnimationCount};


RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis );

#endif /* defined(__PlatformData__Animations__) */

