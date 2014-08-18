//
//  RNEEPROM.h
//  PlatformCode
//
//  Created by Bill on 8/2/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __RNEEPROM__
#define __RNEEPROM__
#include "Platform.h"


bool readPlatformFromEEPROM(Platform * platform);
bool readConstantsFromEEPROM();
void writePlatformToEEPROM(Platform * platform);
void writeConstantsToEEPROM();


#endif /* defined(__RNEEPROM__) */
