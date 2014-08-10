//
//  Animations.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Animations.h"


// Animations by WWP
#include "WWPAnimationTest.h"
#include "WWPAnimation1.h"
#include "WWPAnimation2.h"
#include "WWPAnimation3.h"
#include "WWPAnimation4.h"
#include "WWPAnimation5.h"


#include "DRAnimation0.h"
#include "DRAnimation1.h"

#include "GlowFade.h"
#include "ActivityLevelAnimation.h"

#include "MMAnimation0.h"
#include "MMAnimation1.h"


RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis ) {

  switch (a) {

  case e_ActivityLevelAnimation:
    return new ActivityLevelAnimation(info, animationStartMillis);

  case e_GlowFade:
    return new GlowFade(info, animationStartMillis);

    // Animations by WWP
  case e_WWPAnimationTest : 
    return new WWPAnimationTest(info, animationStartMillis);
  case e_WWPAnimation1 : 
    return new WWPAnimation1(info, animationStartMillis);
  case e_WWPAnimation2 : 
    return new WWPAnimation2(info, animationStartMillis);
  case e_WWPAnimation3 : 
    return new WWPAnimation3(info, animationStartMillis);

  case e_WWPAnimation4 : 
    return new WWPAnimation4(info, animationStartMillis);
  case e_WWPAnimation5 : 
    return new WWPAnimation5(info, animationStartMillis);
  case e_DRAnimation0 :
    return new DRAnimation0(info, animationStartMillis);
  case e_DRAnimation1 :
    return new DRAnimation1(info, animationStartMillis);
	
  case e_MMAnimation0 :
	return new MMAnimation0(info, animationStartMillis);
  case e_MMAnimation1:
    return new MMAnimation1(info, animationStartMillis);  
  default:
    return 0;
  }
}


