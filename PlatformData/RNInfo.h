//
//  RNInfo.h
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__RNInfo__
#define __PlatformData__RNInfo__

#include <stdint.h>

class RNInfo {
    RNInfo(
           uint8_t tier,
           uint8_t number,
           uint8_t identifier,
           int16_t x,
           int16_t y,
           int16_t z);
    
    unsigned long getGlobalMillis();
    float getGlobalActivity();
    float getLocalActitiviity();
    uint8_t getTaps();
    float getAccelerometerData(float data[3]);
    
    // Information about the platform
    const uint8_t tier;
    const uint8_t number;
    const uint8_t identifier;
    const int16_t x,y,z;
    
    // getGlobalAngle for LED in degrees (0 = south)
    uint16_t getGlobalAngle(uint8_t led);
    
};


#endif /* defined(__PlatformData__RNInfo__) */
