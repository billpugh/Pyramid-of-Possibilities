//
//  RNEEPROM.cpp
//  PlatformCode
//
//  Created by Bill on 8/2/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "RNEEPROM.h"

#include "Platform.h"
#include "Constants.h"
#include <Arduino.h>

const char version = 'b';
#ifndef POP_SIMULATOR
#include "EEPROM.h"
#endif

bool readFromEEPROM(uint16_t offset,  uint16_t sz, char *p);
void writeToEEPROM(uint16_t offset,  uint16_t sz, char *p);


bool readPlatformFromEEPROM(Platform * platform) {
    return readFromEEPROM(1, sizeof(Platform), (char *) platform);
}
bool readConstantsFromEEPROM() {
    return readFromEEPROM(1+sizeof(Platform),
                          sizeof(RNConstants),
                          (char *) &constants);
}

void writePlatformToEEPROM(Platform * platform) {
    return writeToEEPROM(1, sizeof(Platform), (char *) platform);
}
void writeConstantsToEEPROM() {
    return writeToEEPROM(1+sizeof(Platform),
                          sizeof(RNConstants),
                          (char *) &constants);
}




bool readFromEEPROM(uint16_t offset, uint16_t sz, char *p) {
#ifndef POP_SIMULATOR
    uint8_t storedVersion = EEPROM.read(0);
    if (version != storedVersion) {
        Serial.println("Incompatible version stored in EEPROM");
        return false;
    }
    uint16_t storedSize = EEPROM.read(offset) << 8 | EEPROM.read(offset+1);

    if (sz != storedSize) {
        Serial.println("Sizes don't match");
        return false;
    }

    for(int i = 0; i < sz; i++)
        p[i] = EEPROM.read(offset+2+i);
#endif
    return true;
}


void writeToEEPROM(uint16_t offset, uint16_t sz, char *p) {
#ifndef POP_SIMULATOR
    EEPROM.write(0, version);
    EEPROM.write(offset, sz>>8);
    EEPROM.write(offset+1, sz);

    for(int i = 0; i < sz; i++)
        EEPROM.write(offset+2+i,p[i]);
    
#endif
}
