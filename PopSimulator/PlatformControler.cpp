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

    animation = getAnimation(e_Flashes, *info, millis());
}

void PlatformControler::refreshPlatform() {
    animation->paint(*lights);
    lights->show();
}

PlatformControler::~PlatformControler() {
    delete lights;
    delete info;
    delete animation;
}

