/* 
 * File:   RNLightsSimulator.cpp
 * Author: antoine
 * 
 * Created on July 22, 2014, 6:43 PM
 */

#include "RNLightsSimulator.hpp"
#include "Pyramid.hpp"
#include "PyramidArchitecture.hpp"

RNLightsSimulator::RNLightsSimulator(Pyramid* _pyramid, int _platform)
: RNLights(PyramidArchitecture::nbLedsPerPlatform) {
    pyramid = _pyramid;
    platform = _platform;
}

unsigned long RNLightsSimulator::show() {
    for (uint16_t i = 0; i < getNumPixels(); i++) {
        uint8_t r, g, b;
        getPixelColor(i, r, g, b);
        pyramid->setLedColor(platform, i,
                (float) r / 255.0, (float) g / 255.0, (float) b / 255.0);
    }
}

