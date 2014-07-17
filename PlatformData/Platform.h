//
//  Platform.h
//  PlatformData
//
//  Created by Bill on 7/14/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__Platform__
#define __PlatformData__Platform__

#include <iostream>
#include <stdint.h>

class Platform {
public:
    const uint8_t tier;
    const uint8_t number;
    const uint8_t identifier;
    const int16_t x,y,z;
    
    Platform(
             uint8_t tier,
             uint8_t number,
             uint8_t identifier,
             int16_t x,
             int16_t y,
             int16_t z) : tier(tier), number(number), identifier(identifier), x(x), y(y), z(z) {};
    
    
};

#endif /* defined(__PlatformData__Platform__) */
