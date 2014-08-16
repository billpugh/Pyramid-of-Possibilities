/* 
 * File:   PlatformControler.cpp
 * Author: antoine
 * 
 * Created on July 22, 2014, 7:24 PM
 */

#include "PlatformControler.hpp"
#include "RNLightsSimulator.hpp"

#include "Animations.h"
#include "Arduino.h"
#include "PyramidArchitecture.hpp"

PlatformControler::PlatformControler(Pyramid* _pyramid, int _platform) {
    pyramid = _pyramid;
    platform = _platform;
    lights = new RNLightsSimulator(pyramid, platform);
    short *coords;
    PyramidArchitecture::getLocationOfPlatform(platform, coords);
    info = new RNInfo(PyramidArchitecture::nbLedsPerPlatform,
            platform,
            coords[0],
            coords[1],
            coords[2]);

    animationId = (AnimationEnum) 0;
    animation = getAnimation(animationId, *info, millis());
}

const char * PlatformControler::nextAnimation() {
    if (animation != NULL) {
        delete animation;
    }
    animationId = (AnimationEnum) (animationId + 1);
    if (animationId == e_AnimationCount) {
        animationId = (AnimationEnum)0;
    }
    animation = getAnimation(animationId, *info, millis());
    return animation->name();
}

void PlatformControler::refreshPlatform() {
    lights->reset();
    animation->paint(*lights);
    lights->show();
}

PlatformControler::~PlatformControler() {
    delete lights;
    delete info;
    if (animation != NULL) {
        delete animation;
    }
}

