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

class PlatformControler {
public:
    PlatformControler(Pyramid* _pyramid, int _platform);
    virtual ~PlatformControler();
    
    void refreshPlatform();
private:
    Pyramid* pyramid;
    int platform;
    RNLightsSimulator* lights;
    RNInfo* info;
    RNAnimation* animation;
};

#endif	/* PLATFORMCONTROLER_HPP */

