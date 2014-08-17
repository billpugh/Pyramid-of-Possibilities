//
//  Controller.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Controller.h"
#include "RNInfo.h"
#include "Arduino.h"
#include "Animations.h"
#include "RNAnimation.h"
#ifndef POP_SIMULATOR
#include "malloc.h"
#endif
#include "Constants.h"
#include "RNComm.h"

static int heapSize(){
#ifdef POP_SIMULATOR
    return 0;
#else
    return mallinfo().uordblks;
#endif
}

void RNController::switchToAnimation(RNAnimation * newAnimation) {
    if (currentAnimation) {
        info.printf("Deleting old animation\n");
        int before = heapSize();
        delete currentAnimation;
        int after = heapSize();
        info.printf("%d bytes freed\n", before-after);
    }

    info.printf("Switching to animation %s\n", newAnimation->name());
    unsigned long start = millis();
    int before = heapSize();
    currentAnimation = newAnimation;
    int after = heapSize();
    info.printf("%d bytes allocated\n",after-before);

    // See Constants.h
    animationExpires = start + constants.animationDuration;

    if (currentAnimation)
      info.printf("Created %s\n", currentAnimation->name());
}

void RNController::nextAnimation() {
    int next = firstAnimation;
    if (currentAnimation) {
        next= 1+currentAnimation->animationInfo.program;
    }
    if (next == e_AnimationCount)
        next = 0;
    AnimationEnum nextAnimationEnum = (AnimationEnum) next;
    unsigned long start = millis();
    AnimationInfo animationInfo =  AnimationInfo(nextAnimationEnum, (uint32_t)start);
    RNAnimation * newAnimation = getAnimation(info, animationInfo);
    switchToAnimation( newAnimation );
}

void RNController::paint(RNLights & lights) {
    info.update();
    if (millis() > animationExpires || !currentAnimation) {
        nextAnimation();
    }

    checkComm(info);

    // call the paint() method on the current animation. 
    // NOTE: we use RN_DEBUG_SAMPLE_ANIMATION_DURATION to debug the duration of calls to paint().
    if (currentAnimation) {

#ifdef RN_PRINT_LOG_ANIMATIONS
        unsigned long start = millis();
#endif /* RN_PRINT_LOG_ANIMATIONS */

        currentAnimation->paint(lights);

#ifdef RN_PRINT_LOG_ANIMATIONS
        unsigned long end = millis();
        unsigned long duration = end - start;
        if ( duration > kMaxPaintDuration ) {
            info.printf("WARNING: Animation %s took %lu ms inside paint()\n", currentAnimation->name(), duration);
        }
#endif  /* RN_PRINT_LOG_ANIMATIONS */
    checkComm(info);
    }
}

void RNController::animationUpdate(AnimationInfo broadcast) {
    info.printf("got broadcast, program %d, tweak %d\n", broadcast.program, broadcast.tweakValue);
    if (currentAnimation && currentAnimation->animationInfo.program == broadcast.program
        && currentAnimation->animationInfo.seqId == broadcast.seqId) {
         info.printf("tweaking existing animation\n", broadcast.program, broadcast.tweakValue);
        // tweak of existing animation
        currentAnimation->animationInfo.lastTweakAt = broadcast.lastTweakAt;
         currentAnimation->animationInfo.cyclesAtLastTweak = broadcast.cyclesAtLastTweak;
        currentAnimation->animationInfo.tweakValue = broadcast.tweakValue;
    } else {
            RNAnimation * newAnimation = getAnimation(info, broadcast);
        info.printf("switching to %s\n", newAnimation->name());

        
    }
    
    }




