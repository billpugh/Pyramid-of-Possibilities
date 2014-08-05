//
//  WWPAnimation5.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __WWPAnimation5__
#define __WWPAnimation5__

#include "RNAnimation.h"
#include "RNChaser.h"



class WWPAnimation5 : 
public RNAnimation {
public:
  const uint8_t numChasers = 6;
  WWPAnimation5(RNInfo & info, unsigned long animationStartMillis);
  virtual void paint(RNLights & paintMe);

  virtual const char * name();
  RNLights lights;
  RNLights dots;
  RNChaser chaser[11] = { 
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),  RNChaser(lights)
  };

  unsigned long lastUpdate;

  unsigned long nextChaser = 0;
  long jiggles;
  long taps;
  long updates;
  float totalJiggle;
  bool didTap = false;
  float tapStrength;
  uint8_t currentHue();
  void setRandomPixel(float v);
  void addChaser();
  void tap(float v);
};


#endif /* defined(__WWPAnimation5__) */


