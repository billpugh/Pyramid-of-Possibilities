//
//  EEPROM.h
//  PlatformCode
//
//  Created by Bill on 8/8/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef PlatformCode_EEPROM_h
#define PlatformCode_EEPROM_h

#include <stdint.h>

class EEPROMClass {
public:
    uint8_t read(uint16_t);
    void write(uint16_t, uint8_t);

};

extern EEPROMClass EEPROM;

#endif
