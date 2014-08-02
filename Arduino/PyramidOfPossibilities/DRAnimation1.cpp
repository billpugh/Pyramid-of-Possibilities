//
//  DRAnimation1.cpp
//  PlatformData
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "DRAnimation1.h"
#include "RNBeam.h"
#include "Arduino.h"


#define CONSIDER_THE_ACCELEROMETER

// TODO: don't statically allocate these. move to constructor.
const uint8_t numBeams = 3;
RNBeam beams[numBeams] = { 
	// RNBeam(),
	RNBeam(), 
	RNBeam(),
	RNBeam()
};
float widths[numBeams] = {333,333,333};
static int once = 0;

void initalizeBeams(RNInfo * info) {

	for ( uint8_t n = 0; n < numBeams; n++ ) {
  		beams[n].speed = 1;
  		beams[n].offset = 333 * n;
        
  		switch (n) {
//  			case 0:
//                beams[n].width = 50;
//                break;
//  			case 1:
//                beams[n].width = 50;
//                break;
//  			case 2:
//                beams[n].width = 100;
//                break;
  			// default:
     //            beams[n].width = 150;
  		}
        beams[n].width = widths[n];
  		beams[n].r = (n==0)*200;
  		beams[n].g = (n==1)*200;
  		beams[n].b = (n==2)*200;
        
		beams[n].info = info;
	}
}

void DRAnimation1::paint(RNLights & lights) {

	// TODO: move to initalizer
	if ( once == 0 ) {
		base_color = 0x000000;
		initalizeBeams(&info);
		min_g = .1;
		max_g = .3;
	}

	// Begin real animation
#ifdef CONSIDER_THE_ACCELEROMETER
	unsigned long millis = getAnimationMillis();
	float activity = info.getLocalActivity();
	if ( activity < min_g ) {
		activity = min_g;
	} else if ( activity > max_g ) {
		activity = max_g;
	}
	float g_range = max_g - min_g;
	float multiplier = (activity - min_g) / g_range;
	for ( int i = 0; i < numBeams; i++ ) {
		beams[i].width = widths[i] * multiplier + 10;
	}
	info.printf("multiplier is %f.  Local Activity is %f\n", multiplier, info.getLocalActivity());
#endif


	for ( int i = 0; i < numBeams; i++ ) {
		beams[i].loop(millis);
	}
	for ( int j = 0; j < info.numLEDs; j++ ) {
		uint32_t currentColor = base_color;
    	for ( int i = 0; i < numBeams; i++ ) {
			uint32_t color = beams[i].drawPixel(j);
			if (color > 0)
			{
		   		currentColor = beams[i].combine_colors(color, currentColor);
		   	}
	  	}
	  	if ( j == 15 ) {
			// info.printf("beam[%d] color is 0x%016x\n", j, currentColor);
	  	}
		lights.setPixelColor(j, currentColor);
	}
}

const char * DRAnimation1:: name() {
	return "DRAnimation1";
}
