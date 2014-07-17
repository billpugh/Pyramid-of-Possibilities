//  RNShowChaser.h
//
//  Created by Bill on 6/15/14
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#ifndef __RNShowChaser__
#define __RNShowChaser__

#include "RNShow.h"
#include "RNChaser.h"

class RNShowChaser : RNShow {

public:
  RNShowChaser(RNLights &lights);
  ~RNShowChaser();
  virtual void accelerometerCallback( float totalG,
                               float directionalG[3],
                               uint8_t tapSource);


  const uint8_t numChasers = 6;
  RNChaser chaser[24] = { 
    RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
    RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
    RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
    RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights)
    };
  CHSV hsv;
  CRGB rgb;
  void addChaser();
  uint8_t currentHue();
  float tapStrength;
  unsigned long nextChaser;
    
};

#endif /*  __RNShowChaser__ */


