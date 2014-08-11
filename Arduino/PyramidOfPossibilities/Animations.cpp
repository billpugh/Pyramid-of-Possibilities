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
#include "ChangingColor.h"
#include "CircularGradient.h"
#include "ColorWorms.h"
#include "Chasers.h"
#include "FlashAttack.h"
#include "SideEffects.h"
#include "Snow.h"
#include "Swirl.h"
#include "Beacon.h"


#include "Qbert.h"
#include "DRAnimation1.h"

#include "GlowFade.h"
#include "ActivityLevelAnimation.h"

#include "AVEAnimation1.h"
#include "Flashes.h"
#include "MovingFaces.h"
#include "Radial.h"
#include "FlashEcho.h"

#include "Kittens.h"
#include "MovingFaces.h"

RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis ) {
    switch (a) {

        case e_Beacon:
            return new Beacon(info, animationStartMillis);

        case e_Kittens:
            return new Kittens(info, animationStartMillis);
            
        case e_ActivityLevelAnimation:
            return new ActivityLevelAnimation(info, animationStartMillis);

        case e_SideEffects:
            return new SideEffects(info, animationStartMillis);

        case e_Swirl:
            return new Swirl(info, animationStartMillis);

        case e_Snow:
            return new Snow(info, animationStartMillis);

        case e_GlowFade:
            return new GlowFade(info, animationStartMillis);
        case e_FlashAttack:
            return new FlashAttack(info, animationStartMillis);


            // Animations by WWP
        case e_WWPAnimationTest :
            return new WWPAnimationTest(info, animationStartMillis);
        case e_ChangingColor :
            return new ChangingColor(info, animationStartMillis);
        case e_CircularGradient :
            return new CircularGradient(info, animationStartMillis);

        case e_ColorWorms :
            return new ColorWorms(info, animationStartMillis);
        case e_Chasers :
            return new Chasers(info, animationStartMillis);
        case e_Qbert :
            return new Qbert(info, animationStartMillis);
        case e_DRAnimation1 :
            return new DRAnimation1(info, animationStartMillis);

        case e_Flashes :
            return new Flashes(info, animationStartMillis);
        case e_AVEAnimation1 :
            return new AVEAnimation1(info, animationStartMillis);
        case e_MovingFaces :
            return new MovingFaces(info, animationStartMillis);
        case e_Radial:
            return new Radial(info, animationStartMillis);
        case e_FlashEcho:
            return new FlashEcho(info, animationStartMillis);

        default:
            return 0;
    }
}



