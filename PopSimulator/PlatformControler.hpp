/* 
 * File:   PlatformControler.hpp
 * Author: antoine
 *
 * Created on July 22, 2014, 7:24 PM
 */

#ifndef PLATFORMCONTROLER_HPP
#define	PLATFORMCONTROLER_HPP

#include "Pyramid.hpp"
#include "RNLightsSimulator.hpp"
#include "RNInfo.h"
#include "RNAnimation.h"
#include "Animations.h"

class PlatformControler {
public:
    PlatformControler(Pyramid* _pyramid, int _platform);
    virtual ~PlatformControler();
    
    void refreshPlatform();
    const char * nextAnimation();
private:
    Pyramid* pyramid;
    int platform;
    RNLightsSimulator* lights;
    RNInfo* info;
    AnimationEnum animationId;
    RNAnimation* animation;
};

#endif	/* PLATFORMCONTROLER_HPP */

