/* 
 * File:   RNLightsSimulator.hpp
 * Author: antoine
 *
 * Created on July 22, 2014, 6:43 PM
 */

#ifndef RNLIGHTSSIMULATOR_HPP
#define	RNLIGHTSSIMULATOR_HPP

#include "Pyramid.hpp"
#include "RNLights.h"

class RNLightsSimulator : public RNLights {
public:
    RNLightsSimulator(Pyramid* _pyramid, int _platform);

    unsigned long show();
private:
    Pyramid* pyramid;
    int platform;
};

#endif	/* RNLIGHTSSIMULATOR_HPP */

