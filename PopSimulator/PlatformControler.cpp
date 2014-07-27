/* 
 * File:   PlatformControler.cpp
 * Author: antoine
 * 
 * Created on July 22, 2014, 7:24 PM
 */

#include "PlatformControler.hpp"
#include "RNLightsSimulator.hpp"
#include "WWPAnimation1.h"
#include "WWPAnimation2.h"
#include "WWPAnimation3.h"
#include "WWPAnimation4.h"
#include "WWPAnimation5.h"
#include "Arduino.h"

PlatformControler::PlatformControler(Pyramid* _pyramid, int _platform) {
    pyramid = _pyramid;
    platform = _platform;
    lights = new RNLightsSimulator(pyramid, platform);
    info = new RNInfo(220, 0, 0, 0, 0, 0, 0);
    
    animation = new WWPAnimation5(*info, millis());
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

