//
//  RNChaser.cpp
//  PlatformTest0
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#include "RNChaser.h"
#include <stdlib.h>

// 

    RNChaser::RNChaser(RNLight & lights) : lights(lights) {
      lastUpdate = 0;
      forward = true;
      active = false;
      delay = 20;
      position = 0;
      r = b = g = 50;
    }
    
void RNChaser::setRPM(uint16_t rpm) {
  delay = 60000 / rpm / lights.getNumPixels();
}
void RNChaser::update(unsigned long millis) {
  if (!active) return;
  if (lastUpdate + delay > millis)
    return;
  lastUpdate = lastUpdate + delay;
  if (forward) 
    position = lights.normalize(position+1);
  else
    position = lights.normalize(position-1);
  lights.addPixelColor(position, r, g, b);
  }

