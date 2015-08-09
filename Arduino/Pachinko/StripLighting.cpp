//
//  StripLighting.cpp
//
//  Created by Bill on 5/19/15.
//
//

#include "StripLighting.h"
#include "PachinkoMain.h"
#include <stdlib.h>




StripLighting::StripLighting(OctoWS2811 & lights, int firstPixel, int numPixels) : lights(lights), firstPixel(firstPixel), numPixels(numPixels) {};


bool changeColors() {
  if (currentAmbientMode == AmbientPattern)
        return true;
  return (random() & 0x3) == 0;
}

void StripLighting::setColor(int rgb) {
  for (int i = 0; i < numPixels; i++) {
    lights.setPixel(firstPixel + i, rgb);
  }
}

void StripLighting::fill() {
    if (currentAmbientMode == AmbientPattern && currentAmbientPatternChoice == AmbientComets) {
        for (int i = 0; i < numPixels; i++)
            lights.setPixel(firstPixel + i, 0);
        return;
    }
    
  int rgb =  randomColor(0);
  for (int i = 0; i < numPixels; i++) {
    lights.setPixel(firstPixel + i, rgb);
    if (changeColors())
      rgb = randomColor(i+1);
  }
}

void StripLighting::update() {
    if (currentAmbientMode == AmbientPattern && currentAmbientPatternChoice == AmbientSparkles) {
        for (int i = 0; i < numPixels - 1; i++)
            lights.setPixel(firstPixel + i, randomColor(i));
        return;
    }
  for (int i = 0; i < numPixels - 1; i++)
    lights.setPixel(firstPixel + i, lights.getPixel(firstPixel + i + 1));
  if (changeColors())
    lights.setPixel(firstPixel + numPixels - 1, randomColor(numPixels - 1));
}

