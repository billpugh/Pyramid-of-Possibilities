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
void RNChaser::fade(uint8_t amount) {
  if (r > amount)
	r -= amount;
  else r = 0;
  if (g > amount)
	g -= amount;
  else g = 0;
  if (b > amount)
	b -= amount;
  else b = 0;
  if (r == 0 && g == 0 && b == 0)
    active = false;
}

uint16_t RNChaser::getRPM() {
  return 60000 / delay / lights.getNumPixels();
}

bool RNChaser::update(unsigned long millis) {
  if (!active) return false;
  if (nextUpdate > millis)
    return false;
  do {
    nextUpdate += delay;
  } while (nextUpdate < millis);
 
  if (forward) 
    position = lights.normalize(position+1);
  else
    position = lights.normalize(position-1);
  lights.addPixelColor(position, r, g, b);
  return true;
}


