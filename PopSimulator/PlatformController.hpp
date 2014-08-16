/* 
 * File:   PlatformControler.hpp
 * Author: antoine
 *
 * Created on July 22, 2014, 7:24 PM
 */

#ifndef PLATFORMCONTROLLER_HPP
#define	PLATFORMCONTROLLER_HPP

#include "Pyramid.hpp"
#include "RNLightsSimulator.hpp"
#include "RNInfo.h"
#include "RNAnimation.h"
#include "Animations.h"
#include "Controller.h"

class PlatformController {
public:
    PlatformController(Pyramid* _pyramid, int _platform);
    virtual ~PlatformController();
    
    void refreshPlatform();
    const char * nextAnimation();
private:
    Pyramid* pyramid;
    int platform;
    RNLightsSimulator* lights;
    RNInfo* info;
    RNController* controller;
};

#endif	/* PLATFORMCONTROLLER_HPP */

