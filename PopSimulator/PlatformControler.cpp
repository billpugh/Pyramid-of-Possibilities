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

#include "DRAnimation0.h"
#include "DRAnimation1.h"

#include "Snow.h"
#include "GlowFade.h"

#include "AVEAnimation1.h"

#include "Arduino.h"
#include "PyramidArchitecture.hpp"

PlatformControler::PlatformControler(Pyramid* _pyramid, int _platform) {
    pyramid = _pyramid;
    platform = _platform;
    lights = new RNLightsSimulator(pyramid, platform);
    short *coords;
    PyramidArchitecture::getLocationOfPlatform(platform, coords);
    info = new RNInfo(PyramidArchitecture::nbLedsPerPlatform,
            PyramidArchitecture::getTierOfPlatform(platform),
            PyramidArchitecture::getPlatformNumberOnTier(platform),
            platform,
            coords[0],
            coords[1],
            coords[2]);

    animation = new GlowFade(*info, millis());
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

