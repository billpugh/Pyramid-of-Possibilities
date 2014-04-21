//
//  RNLights.h
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#ifndef __RNLightsNeoPixel__
#define __RNLightsNeoPixel__

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

#endif /* defined(__RNLightsNeoPixel__) */
