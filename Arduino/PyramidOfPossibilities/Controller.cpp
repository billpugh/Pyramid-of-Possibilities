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
#include "malloc.h"
#include "Constants.h"
#include "RNComm.h"

static int heapSize(){
    return mallinfo().uordblks;
}

void RNController::switchToAnimation(AnimationEnum nextAnimation) {
    if (currentAnimation) {
        info.printf("Deleting old animation\n");
        int before = heapSize();
        delete currentAnimation;
        int after = heapSize();
        info.printf("%d bytes freed\n", before-after);
    }
    currentAnimationEnum = nextAnimation;
    if (currentAnimationEnum >= e_AnimationCount)
        currentAnimationEnum = (AnimationEnum) 0;
    info.printf("Switching to animation %d\n", currentAnimationEnum);
    unsigned long start = millis();
    int before = heapSize();
    currentAnimation = getAnimation(currentAnimationEnum, info, start);
    int after = heapSize();
    info.printf("%d bytes allocated\n",after-before);

    // See Constants.h
    animationExpires = start + constants.animationDuration;

    if (currentAnimation)
      info.printf("Created %s\n", currentAnimation->name());
}

void RNController::nextAnimation() {
  switchToAnimation((AnimationEnum) (1+((int)currentAnimationEnum)));
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




