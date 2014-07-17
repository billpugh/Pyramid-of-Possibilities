//
//  RNChaser.h
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#ifndef __RNChaser__
#define __RNChaser__

#include <stdint.h>

#include "RNLights.h"
#include <hsv2rgb.h>

class RNChaser {

public:
  RNChaser(RNLights & lights);
  bool update(unsigned long millis); 
  void setRPM(uint16_t rpm); 
  uint16_t getRPM();
  void setHalflife(uint16_t ms); 
  uint16_t getHalflife();
  void activate(unsigned long millis);

  bool forward;
  bool active;
  int16_t position;
  float fadeBottom = 0.3;
  float fadeValue = 1 + fadeBottom;
  CHSV hsv;
  uint8_t brightness;

  uint16_t delay;

private:

  unsigned long nextUpdate;
  unsigned long nextFadeUpdate;
  uint16_t fadeDelay;
  void fade(float amount=0.99);
  RNLights & lights;

};

#endif /* defined(__RNChaser__) */

