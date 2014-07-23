/* 
 * File:   RNLightsSimulator.cpp
 * Author: antoine
 * 
 * Created on July 22, 2014, 6:43 PM
 */

#include "RNLightsSimulator.hpp"
#include "Pyramid.hpp"

RNLightsSimulator::RNLightsSimulator(Pyramid* _pyramid, int _platform)
: RNLights(220) {
    pyramid = _pyramid;
    platform = _platform;
}

unsigned long RNLightsSimulator::show() {
    for (uint16_t i = 0; i < getNumPixels(); i++) {
        uint8_t r, g, b;
        getPixelColor(i, r, g, b);
        pyramid->setLedColor(platform, i, r, g, b);
    }
}

