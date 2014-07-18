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
    e_WWPAnimation1,
    e_WWPAnimation2,
    
    // Not an actual enum, just the value used to give us the count of the number of enums
    e_AnimationCount};


RNAnimation * getAnimation(AnimationEnum a);

#endif /* defined(__PlatformData__Animations__) */
