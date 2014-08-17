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
#include "LiftOff.h"
#include "Qbert.h"
#include "DRAnimation1.h"

#include "GlowFade.h"
#include "ActivityLevelAnimation.h"

#include "Flashes.h"
#include "MovingFaces.h"
#include "Radial.h"
#include "FlashEcho.h"
#include "Mute.h"

#include "Kittens.h"
#include "MovingFaces.h"
#include "Explosion.h"

RNAnimation * getAnimation(RNInfo & info, AnimationInfo animationInfo ) {
    switch (animationInfo.program) {

        case e_Beacon:
            return new Beacon(info, animationInfo);

        case e_Kittens:
            return new Kittens(info, animationInfo);

        case e_Mute:
            return new Mute(info, animationInfo);
        case e_LiftOff:
            return new LiftOff(info, animationInfo);

        case e_ActivityLevelAnimation:
            return new ActivityLevelAnimation(info, animationInfo);

        case e_SideEffects:
            return new SideEffects(info, animationInfo);

        case e_Swirl:
            return new Swirl(info, animationInfo);

        case e_Snow:
            return new Snow(info, animationInfo);

        case e_GlowFade:
            return new GlowFade(info, animationInfo);
        case e_FlashAttack:
            return new FlashAttack(info, animationInfo);


            // Animations by WWP
        case e_WWPAnimationTest :
            return new WWPAnimationTest(info, animationInfo);
        case e_ChangingColor :
            return new ChangingColor(info, animationInfo);
        case e_CircularGradient :
            return new CircularGradient(info, animationInfo);

        case e_ColorWorms :
            return new ColorWorms(info, animationInfo);
        case e_Chasers :
            return new Chasers(info, animationInfo);
        case e_Qbert :
            return new Qbert(info, animationInfo);
        case e_DRAnimation1 :
            return new DRAnimation1(info, animationInfo);

        case e_Flashes :
            return new Flashes(info, animationInfo);
        case e_MovingFaces :
            return new MovingFaces(info, animationInfo);
        case e_Explosion :
            return new Explosion(info, animationInfo);
        case e_Radial:
            return new Radial(info, animationInfo);
        case e_FlashEcho:
            return new FlashEcho(info, animationInfo);

        default:
            info.printf("Got request for non-existent animation %d\n", animationInfo.program);
            return 0;
    }
}


RNAnimation * getAnimation(RNInfo & info, AnimationEnum e) {
    AnimationInfo animationInfo(e, 0);
    return getAnimation(info, animationInfo);
}


