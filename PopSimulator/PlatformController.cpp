/* 
 * File:   PlatformControler.cpp
 * Author: antoine
 * 
 * Created on July 22, 2014, 7:24 PM
 */

#include "PlatformController.hpp"
#include "RNLightsSimulator.hpp"

#include "Animations.h"
#include "Arduino.h"
#include "PyramidArchitecture.hpp"

PlatformController::PlatformController(Pyramid* _pyramid, int _platform) {
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
    
    controller = new RNController(*info);
}

const char * PlatformController::nextAnimation() {
    controller->nextAnimation();
    return controller->currentAnimation->name();
}

void PlatformController::refreshPlatform() {
    lights->reset();
    controller->paint(*lights);
    lights->show();
}

PlatformController::~PlatformController() {
    delete lights;
    delete info;
    delete controller;
}

