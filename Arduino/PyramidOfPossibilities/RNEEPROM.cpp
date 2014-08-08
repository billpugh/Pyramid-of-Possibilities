//
//  RNEEPROM.cpp
//  PlatformCode
//
//  Created by Bill on 8/2/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "RNEEPROM.h"

#include <Arduino.h>

const char version = 'a';
#ifndef POP_SIMULATOR
#include "EEPROM.h"
#endif

bool readFromEEPROM(short sz, char *p) {
#ifndef POP_SIMULATOR
     uint8_t storedVersion = EEPROM.read(0);
    if (version != storedVersion) {
        return false;
    }
    uint16_t storedSize = EEPROM.read(1) << 8 | EEPROM.read(2);
    
    if (sz != storedSize) {
        return false;
    }
    for(int i = 0; i < sz; i++)
        p[i] = EEPROM.read(3+i);

    return true;
    
#endif
}


void writeToEEPROM(short sz, char *p) {
#ifndef POP_SIMULATOR
    EEPROM.write(0, version);
    EEPROM.write(1, sz>>8);
    EEPROM.write(2, sz);

    for(int i = 0; i < sz; i++)
        EEPROM.write(3+i,p[i]);
    
#endif
}
