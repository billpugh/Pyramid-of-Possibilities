//
//  RNInfo.cpp
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//


#include "RNInfo.h"
#include "Arduino.h"

RNInfo::RNInfo(
       uint8_t tier,
       uint8_t number,
       uint8_t identifier,
       int16_t x,
       int16_t y,
               int16_t z) : tier(tier), number(number), identifier(identifier),
x(x), y(y), z(z) {};



unsigned long RNInfo::getGlobalMillis() {
    return millis();
    
}
float RNInfo::getGlobalActivity() {
    return 0.0;
}
float RNInfo::getLocalActitiviity() {
    return 0.0;
}
uint8_t RNInfo::getTaps() {
    return 0;
}
void RNInfo::getLocalXYZActitiviity(float data[3]) {
    data[0] =  data[1] =  data[2] = 0.0;
}


uint16_t RNInfo::getGlobalAngle(uint8_t led) {
    return led * 360 / numLEDs;
}