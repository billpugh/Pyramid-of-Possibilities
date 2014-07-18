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

  // Animations defined by Bill Pugh (WWP)
  e_WWPAnimation1,
  e_WWPAnimation2,
  e_WWPAnimation3,


  // Not an actual enum, just the value used to give us the count of the number of enums
  e_AnimationCount};


RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis );

#endif /* defined(__PlatformData__Animations__) */

