//
//  Platform.h
//  PlatformData
//
//  Created by Bill on 7/14/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Platform__
#define __Platform__

#include <stdint.h>

class Platform {
public:
    // What tier is the platform on
    const uint8_t tier;
    // What is the number of the platform within that tier
    const uint8_t number;
    // What is the identify of the platform (unique)
    const uint8_t identifier;
    
    // What is the x,y,z displacement of the center of the platform
    // from the center base of the Pyramid
    const int16_t x,y,z;

    
    Platform(
             uint8_t tier,
             uint8_t number,
             uint8_t identifier,
             int16_t x,
             int16_t y,
             int16_t z) : tier(tier), number(number), identifier(identifier), x(x), y(y), z(z) {};
    
    
};

#endif /* defined(__Platform__) */
