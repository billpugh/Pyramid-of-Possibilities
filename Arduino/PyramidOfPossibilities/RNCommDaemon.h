//
//  RNCommDaemon.h
//  PlatformCode
//
//  Created by Bill on 8/12/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __RNCommDaemon__
#define __RNCommDaemon__

#include <stdint.h>
#include "RNInfo.h"

// For speed, we are assuming all milli() values
// can be represented using 32 bit values

typedef uint32_t comm_time_t;

void initializeCommDaemonTimer();

bool scheduleSend(RNInfo &info,
                  comm_time_t when,
                  uint8_t size, char * buffer);
bool dataAvailable(RNInfo &info,
                   comm_time_t &when);
void lookForData(RNInfo &info);
comm_time_t getSentAt();

#endif /* defined(__RNCommDaemon__) */
