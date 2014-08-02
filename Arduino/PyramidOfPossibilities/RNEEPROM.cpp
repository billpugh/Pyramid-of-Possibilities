//
//  RNEEPROM.cpp
//  PlatformCode
//
//  Created by Bill on 8/2/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "RNEEPROM.h"
#include <EEPROM.h>

void readFromEEPROM(uint8_t version, uint16_t sz, uint8_t *p) {
     uint8_t storedVersion = EEPROM.read(0);
    if (version != storedVersion) {
        return;
    }
    uint16_t storedSize = EEPROM.read(1) << 8 | EEPROM.read(2);
    
    if (sz != storedSize) {
        return;
    }
    for(int i = 0; i < sz; i++)
        p[i] = EEPROM.read(3+i);
    
}


void writeTo(uint8_t version, uint16_t sz, uint8_t *p) {
    EEPROM.write(0, version);
    EEPROM.write(1, sz>>8);
    EEPROM.write(2, sz);

    for(int i = 0; i < sz; i++)
        EEPROM.write(3+i,p[i]);
    
}
