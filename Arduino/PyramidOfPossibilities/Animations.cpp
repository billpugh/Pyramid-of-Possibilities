//
//  Animations.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Animations.h"

// Animations by WWP
#include "WWPAnimation1.h"
#include "WWPAnimation2.h"
#include "WWPAnimation3.h"
#include "WWPAnimation4.h"



RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis ) {
  switch (a) {

    // Animations by WWP
  case e_WWPAnimation1 : 
    return new WWPAnimation1(info, animationStartMillis);
  case e_WWPAnimation2 : 
    return new WWPAnimation2(info, animationStartMillis);
  case e_WWPAnimation3 : 
    return new WWPAnimation3(info, animationStartMillis);

  case e_WWPAnimation4 : 
    return new WWPAnimation4(info, animationStartMillis);

  default:
    return 0;
  }
}

