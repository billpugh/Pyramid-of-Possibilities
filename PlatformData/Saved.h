//
//  Saved.h
//  PlatformData
//
//  Created by Bill on 7/14/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__Saved__
#define __PlatformData__Saved__

#include <iostream>
#include <stdint.h>
#include "Platform.h"

typedef struct saved_s {
    const uint8_t tier;
    const uint8_t number;
    const uint8_t identifier;
    const int16_t x,y,z;
    
    
} __attribute ((packed)) saved_t;


#endif /* defined(__PlatformData__Saved__) */
