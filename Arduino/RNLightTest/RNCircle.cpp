//
//  RNCircle.cpp
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#include "RNCircle.h"
#include <stdlib.h>
#include <math.h>




RNCircle::RNCircle(RNLights & lights, float radius) : 
lights(lights), radius(radius), velocity(radius*2), pixelX(new float[lights.getNumPixels()]), \
pixelY(new float[lights.getNumPixels()]) {

  width = radius/10;
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


uint16_t RNCircle::update(unsigned long millis) {
 
  float outerRadius = velocity * (millis - startTime)/1000.0;
  float innerRadius = outerRadius - width;
  if (innerRadius < 0) innerRadius = 0;
  if (innerRadius > 2*radius) {
    active = false;
    return 0;
  }

  return drawCircle(innerRadius, outerRadius);
}



uint16_t RNCircle::drawCircle(float innerRadius, float outerRadius) {
   hsv2rgb_rainbow(hsv,rgb);
   outerRadius = outerRadius * outerRadius;
  innerRadius = innerRadius * innerRadius;
  uint16_t lit = 0;
  for(int i = 0; i < lights.getNumPixels(); i++) {
    float xDiff = pixelX[i] - x;
    float yDiff = pixelY[i] - y;
    float rangeSquare = xDiff * xDiff + yDiff * yDiff;
    if (rangeSquare <= outerRadius && innerRadius <= rangeSquare) {
      lights.setPixelColor(i, rgb.r, rgb.g, rgb.b);
//      lights.setPixelColor(i, 0, 255, 0);
      lit++;
    }
  }
  return lit;
}
void RNCircle::start(int pixel, unsigned long millis) {
  startTime = millis;
  x = pixelX[pixel];
  y = pixelY[pixel];
  active = true;
  
}




