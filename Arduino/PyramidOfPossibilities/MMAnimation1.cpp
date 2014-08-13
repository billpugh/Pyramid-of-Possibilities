//
//  MMAnimation0.cpp
//  PlatformData
//
//  Created by Meelow.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "MMAnimation1.h"

#define MIN_BRIGHTNESS 20
#define MAX_BRIGHTNESS 250
#define STEP_BRIGHTNESS 5

#define DEBUG true  // print msgs over serial

static uint8_t brightness = MIN_BRIGHTNESS;
static unsigned long lastActivity=0;

void MMAnimation1::paint(RNLights & lights) 
{
  // flash on value if there was a tap, if not use brightness for value
  int value = 255 - info.timeSinceLastTap();
  if (value < 20)
    value = 20;
  if (value < brightness)
    value = brightness;	
	
  // hue is made from globaltime	
  uint8_t hue = (info.getGlobalMillis() / 150) % 256;

  lights.setAllPixelHSVs(hue,250,value);  
  
  // increase /decrease brightness:
  if(info.getTaps() )
  {
    if( brightness<MAX_BRIGHTNESS ) brightness+=STEP_BRIGHTNESS;
    if(DEBUG) info.printf("[MM1]: brightness=%i\n", brightness);
	lastActivity = getAnimationMillis();
    if(false)
	{
	  info.printf("[MM1]: numLEDs %i\n", info.numLEDs);
	  info.printf("[MM1]: tier    %i\n", info.tier);
	  info.printf("[MM1]: number  %i\n", info.number);
	  info.printf("[MM1]: getTaps()           %u\n", info.getTaps());
	  info.printf("[MM1]: timeSinceLastTap    %u\n", info.timeSinceLastTap());
	  info.printf("[MM1]: getLocalActivity    %f\n", info.getLocalActivity());
	  info.printf("[MM1]: getGlobalActivity   %f\n", info.getGlobalActivity());
//	  info.printf("[MM1]: getGlobalRadius    %u\n", info.getGlobalRadius(0));
	  info.printf("[MM1]: getGlobalMillis    %u\n", info.getGlobalMillis());
	  info.printf("[MM1]: getRandom          %i\n", info.getRandom(1000));
	  info.printf("[MM1]: getRandomPixel     %i\n", info.getRandomPixel());
	}
  }
  
  // last activity longer than 1s ago?
  if( getAnimationMillis() - lastActivity > 1000 )
  {
    if( brightness>MIN_BRIGHTNESS ) brightness-= STEP_BRIGHTNESS;
    if(DEBUG) info.printf("[MM1]: brightness=%i\n", brightness);
	lastActivity = getAnimationMillis();
  }
}

char * MMAnimation1:: name() {
	return "MMAnimation1";
}
