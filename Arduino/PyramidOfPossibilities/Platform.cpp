//
//  Platform.cpp
//  PlatformData
//
//  Created by Bill on 7/14/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Platform.h"


bool Platform::initialize(char * p, uint16_t sz) {
    if (sz  > sizeof(Platform))
        return 0;
    uint8_t * from = (uint8_t*)p;
    uint8_t * to = (uint8_t*)&identifier;
    for(uint16_t i = 0; i < sizeof(Platform); i++)
        *to++ = *from++;
    return 1;

}
