//
//  RNCircle.h
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#ifndef __RNCircle__
#define __RNCircle__

#include <stdint.h>

#include "RNLights.h"
#include <hsv2rgb.h>

class RNCircle {

public:
  RNCircle(RNLights & lights, float radius);
  ~RNCircle();
  uint16_t update(unsigned long millis); 
  void start(int pixel, unsigned long millis); 
  uint16_t drawCircle(float innerRadius, float outerRadius);

  float * pixelX;
  float * pixelY;
  float radius;
  float x,y;
  float velocity;
  float width;
  bool active;
  unsigned long startTime;
  CHSV hsv;
  CRGB rgb;
private:
  RNLights & lights;

};

#endif /* defined(__RNCircle__) */

