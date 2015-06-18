//
//  OctoWS2811.h
//  Cuberosity
//
//  Created by Bill on 6/11/15.
//  Copyright (c) 2015 Hall of Mirrors. All rights reserved.
//

#ifndef Cuberosity_OctoWS2811_h
#define Cuberosity_OctoWS2811_h

#include <stdint.h>

static const uint16_t WS2811_GRB = 1;
static const uint16_t WS2811_800kHz = 1;

class OctoWS2811 {
public:
    OctoWS2811(uint16_t LEDsPerStrip, int* displayMemory, int* drawingMemory,
               uint16_t config);
    void begin() {}
    void show() {}
    void setPixel( int pos, int color) {}
    
};
#endif
