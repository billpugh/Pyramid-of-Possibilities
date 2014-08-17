//
//  UploadConstants.cpp
//  PlatformCode
//
//  Created by Bill on 8/16/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "UploadConstants.h"

#include "RNInfo.h"
#include "Constants.h"


void setupUploadConstants() {
    Platform platform( /* ID */ 42, /* XYZ */ 0,0,700,
                      /* dir */ 0, /* wire Pos */ 1);
    RNInfo info(constants.LEDs, platform);
    
    int size = sizeof(RNConstants);
    info.printf("%d\n", size);
    uint8_t * p = (uint8_t*) &constants;
    for(int i = 0; i < size; i++)
        info.printf("%02x", (uint8_t)p[i]);
    info.println("");
}
