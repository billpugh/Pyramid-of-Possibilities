//
//  RNChaser.cpp
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#include "RNChaser.h"
#include <stdlib.h>


static CRGB rgb;

RNChaser::RNChaser(RNLights & lights) : 
lights(lights) {
  nextUpdate = 0;
  forward = true;
  active = false;
  delay = fadeDelay = 20;
  position = 0;
  hsv.h = 0;
  hsv.s = 255;
  brightness = 255;
}


void RNChaser::fade(float amount) {
  fadeValue *= amount;
  if (fadeValue < fadeBottom)
    active = false;
}

void RNChaser::activate() {
  active = true;
  fadeValue = 1.0+fadeBottom;
}

void RNChaser::setRPM(uint16_t rpm) {
  delay = 60000 / rpm / lights.getNumPixels();
  fadeDelay = 60000 / rpm / 30;
}

uint16_t RNChaser::getRPM() {
  return 60000 / delay / lights.getNumPixels();
}

void RNChaser::setHalflife(uint16_t ms) {
  fadeDelay = ms/13;
}

uint16_t RNChaser::getHalflife() {
  return fadeDelay*13;
}

bool RNChaser::update(unsigned long millis) {
  if (!active) return false;
  while (true) {
    if (nextFadeUpdate < nextUpdate) {
      if (nextFadeUpdate > millis) break;
      nextFadeUpdate += fadeDelay;
      fade(0.99);
    } 
    else {
      if (nextUpdate > millis) break;
      nextUpdate += delay;
      if (forward) 
        position = lights.normalize(position+1);
      else
        position = lights.normalize(position-1);
      hsv.v = (uint8_t)(brightness * (fadeValue-fadeBottom));
      hsv2rgb_rainbow(hsv,rgb);
      lights.addPixelColor(position, rgb.r, rgb.g, rgb.b);
    }
  }
  return true;
}




