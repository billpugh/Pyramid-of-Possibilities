//
//  RNLights.h
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#ifndef __RNLightsOctoWS2811__
#define __RNLightsOctoWS2811__

#include <Arduino.h>
#include "OctoWS2811.h"
#include "RNLights.h"

class RNLightsOctoWS2811 : 
public RNLights {

public:
  RNLightsOctoWS2811(OctoWS2811 & strip,  void *frameBuffer,  uint16_t firstPixel=0);

  unsigned long show();

private:
  OctoWS2811 & strip;
  uint8_t *frameBuffer;
  const uint16_t firstPixel;
};

#endif /* defined(__RNLightsOctoWS2811__) */

