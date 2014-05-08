//
//  RNCircle.cpp
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#include "RNCircle.h"
#include <stdlib.h>
#include <math.h>


static CRGB rgb;

RNCircle::RNCircle(RNLights & lights, float radius) : 
lights(lights), radius(radius), pixelX(new float[lights.getNumPixels()]), \
pixelY(new float[lights.getNumPixels()]) {

  width = radius/20;
  active = false;
  hsv.h = 0;
  hsv.s = 255;
  hsv.v = 255;
  float angle = 3.1415926 * 2 / lights.getNumPixels();
  for(int i = 0; i < lights.getNumPixels(); i++) {
    pixelX[i] = radius * cos(i*angle);
    pixelY[i] = radius * sin(i * angle);
  }
}

RNCircle::~RNCircle() {
  delete [] pixelX;
  delete [] pixelY;
}


bool RNCircle::update(unsigned long millis) {
  float outerRadius = velocity * (millis - startTime)/1000.0;
  float innerRadius = outerRadius - width;
  if (innerRadius < 0) innerRadius = 0;
  bool anyLit = false;
  outerRadius = outerRadius * outerRadius;
  innerRadius = innerRadius * innerRadius;
  hsv2rgb_rainbow(hsv,rgb);
  for(int i = 0; i < lights.getNumPixels(); i++) {
    float xDiff = pixelX[i] - x;
    float yDiff = pixelY[i] = y;
    float rangeSquare = xDiff * xDiff + yDiff * yDiff;
    if (rangeSquare <= outerRadius && innerRadius <= rangeSquare) {
      lights.setPixelColor(i, rgb.r, rgb.g, rgb.b);
      anyLit = true;
    }
  }
  return anyLit;
}
void RNCircle::start(int pixel, unsigned long millis) {
  startTime = millis;
  x = pixelX[pixel];
  y = pixelY[pixel];
  active = true;
  
}




