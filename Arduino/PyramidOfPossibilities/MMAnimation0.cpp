//
//  MMAnimation0.cpp
//  PlatformData
//
//  Created by Meelow.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "MMAnimation0.h"

#define MAX_BRIGHTNESS 120
#define DEBUG false  // print msgs over serial

static uint8_t brightness = 120;
static unsigned long lastActivity=0;

void MMAnimation0::paint(RNLights & lights) 
{
  uint8_t hue = (getAnimationMillis() / 150) % 256;
  lights.setAllPixelHSVs(hue,250,brightness);
  
  if(info.getTaps() )
  {
    if( brightness<250 ) brightness+=1;
    if(DEBUG) info.printf("[MM0]: brightness=%i\n", brightness);
	lastActivity = getAnimationMillis();
  }
  
  // last activity longer than 1s ago?
  if( getAnimationMillis() - lastActivity > 1000 )
  {
    if( brightness>50 ) brightness-= 1;
    if(DEBUG) info.printf("[MM0]: brightness=%i\n", brightness);
	lastActivity = getAnimationMillis();
  }
}

char * MMAnimation0:: name() {
	return "MMAnimation0";
}
