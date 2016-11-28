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
// #include <Adafruit_NeoPixel.h>
#include "RNLights.h"

class RNLightsNeoPixel : 
public RNLights {

public:
  RNLightsNeoPixel(Adafruit_NeoPixel & strip);
  RNLightsNeoPixel(Adafruit_NeoPixel & strip, uint16_t firstPixel);

  virtual unsigned long show();

private:
  Adafruit_NeoPixel & strip;
  const uint16_t firstPixel;
};

#endif /* defined(__RNLightsNeoPixel__) */

