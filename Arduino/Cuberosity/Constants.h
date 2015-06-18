//
//  Constants.h
//  Cuberosity
//
//  Created by Bill on 6/4/15.
//
//

#ifndef Cuberosity_Constants_h
#define Cuberosity_Constants_h

#include <stdint.h>

// #define FULL_SIZE

#ifdef FULL_SIZE

static const uint16_t verticalLength = 240;
static const uint16_t horizontalLength = 210;
static const uint16_t horizontalGap = 0;
#else
static const uint16_t verticalLength = 12;
static const uint16_t horizontalLength = 8;
static const uint16_t horizontalGap = 1;
#endif

static const uint16_t LEDsPerStrip = verticalLength+2*horizontalLength+horizontalGap;


#endif
