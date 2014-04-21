//
//  RNChaser.cpp
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#include "RNChaser.h"
#include <stdlib.h>

RNChaser::RNChaser(RNLights & lights) : lights(lights) {
  nextUpdate = 0;
  forward = true;
  active = false;
  delay = 20;
  position = 0;
  r = b = g = 50;
}

void RNChaser::setRPM(uint16_t rpm) {
  delay = 60000 / rpm / lights.getNumPixels();
}

uint16_t RNChaser::getRPM() {
  return 60000 / delay / lights.getNumPixels();
}

void RNChaser::update(unsigned long millis) {
  if (!active) return;
  if (nextUpdate > millis)
    return;
  do {
    nextUpdate += delay;
  } while (nextUpdate < millis);
 
  if (forward) 
    position = lights.normalize(position+1);
  else
    position = lights.normalize(position-1);
  lights.addPixelColor(position, r, g, b);
}


