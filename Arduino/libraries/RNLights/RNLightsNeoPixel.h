//
//  RNLights.h
//  PlatformTest0
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#ifndef __PlatformTest0__RNLightsNeoPixel__
#define __PlatformTest0__RNLightsNeoPixel__

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include "RNLights.h"

class RNLightsNeoPixel : public RNLights {
    
public:
    RNLightsNeoPixel(Adafruit_NeoPixel & strip);
    
    unsigned long show();
    
private:
   Adafruit_NeoPixel & strip;
};

#endif /* defined(__PlatformTest0__RNLightsNeoPixel__) */
