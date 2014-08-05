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

    // What is the identify of the platform (unique)
    const uint16_t identifier;
    
    // What is the x,y,z displacement of the center of the platform
    // from the center base of the Pyramid
    const int16_t x,y,z;

    // base rotation direction for interlocking gears
    const int8_t direction;

    
    Platform(

             uint16_t identifier,
             int16_t x,
             int16_t y,
             int16_t z,
             int8_t direction)
    :  identifier(identifier), x(x), y(y), z(z), direction(direction) {};


    bool initialize(char * p, uint16_t sz);
};

#endif /* defined(__Platform__) */
