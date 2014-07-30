//
//  GlowFade.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "GlowFade.h"


void getGradiant(uint8_t pos, uint8_t &h,  uint8_t &s,  uint8_t &v) {
	h = pos;
	s = 255;
	v = 255;
	}

void getLinear(float pos, uint8_t &value) {
   int result;
   if (pos < 0.75) {
	result = (uint8_t) (pos/0.75 * 256);
	}
   else {
	result = 255 + (0.75 - pos) * 4 *  256;
	}
   if (result < 0) result = 0;
   else if (result > 255) result = 255;
   value = result;
}


  GlowFade::GlowFade(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis), sparkles(info.numLEDs) {
        sparkles.setFade(animationStartMillis, 750);
    };
    
void GlowFade::paint(RNLights & lights) {
    const uint16_t period = 4000;
    const uint16_t gradiantSkip = 69 ;
    
    unsigned long ms = getAnimationMillis();

    uint16_t cycle = ms / period;
    uint8_t gradiantPosition = cycle * gradiantSkip;
    uint8_t h,s,v;
    getGradiant(gradiantPosition, h, s, v);
    lights.setAllPixelHSVs(h,s,v);
    
    float moment = ((float)(ms % period)) / period;
    uint8_t brightness;
    getLinear(moment, brightness);
    lights.setBrightness(brightness);
    lights.applyBrightness();
    sparkles.fade(ms);
    if (info.getTaps()) {
      for(int i = 0; i < 10; i++) {
        sparkles.setPixelColor(info.getRandomPixel(), 255, 255, 255);
      }}
    info.printf("local activity level %f\n", info.getLocalActivity());
    lights.copyPixelsMax(sparkles);
    
    info.printf("%3d %f %3d %3d %3d %3d\n", gradiantPosition, moment, h, s, v, brightness);

   }

  char * GlowFade:: name() {
    return "GlowFade";
  }
