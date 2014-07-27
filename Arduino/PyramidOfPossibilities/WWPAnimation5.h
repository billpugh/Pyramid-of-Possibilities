//
//  WWPAnimation5.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__WWPAnimation5__
#define __PlatformData__WWPAnimation5__

#include "RNAnimation.h"
#include "RNChaser.h"



class WWPAnimation5 : 
public RNAnimation {
public:
  const uint8_t numChasers = 6;
  WWPAnimation5(RNInfo & info, unsigned long animationStartMillis);
  virtual void paint(RNLights & paintMe);

  virtual char * name();
  RNLights lights;
  RNLights dots;
  RNChaser chaser[11] = { 
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),  RNChaser(lights)
  };

  unsigned long nextUpdate;
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
  void updateTemperature();
  void tapHandler(float f);
};


#endif /* defined(__PlatformData__WWPAnimation5__) */


