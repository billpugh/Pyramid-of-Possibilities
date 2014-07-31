//
//  DRAnimation1.cpp
//  PlatformData
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "DRAnimation1.h"
#include "RNBeam.h"

#define MAX_BRIGHTNESS 100

// TODO: don't statically allocate these. move to constructor.
const uint8_t numBeams = 3;
RNBeam beams[numBeams] = { 
	// RNBeam(),
	RNBeam(), 
	RNBeam(),
	RNBeam()
};
static int once = 0;

void initalizeBeams(RNInfo * info) {

	for ( uint8_t n = 0; n < numBeams; n++ ) {
  		beams[n].speed = n+1;
  		beams[n].width = 55+33 * n;
  		beams[n].offset = 333 * n;

  		beams[n].r = (n==0)*200;
  		beams[n].g = (n==1)*200;
  		beams[n].b = (n==2)*200;

		beams[n].info = info;
	}
}

void DRAnimation1::paint(RNLights & lights) {

	// TODO: move to initalizer
	if ( once == 0 ) {
		initalizeBeams(&info);
	}
	if ( ++once < 20 ) {
		lights.setAllPixelColors(once, 0, 0);
		return;
	}

	// Begin real animation

	unsigned long millis = getAnimationMillis();

	for ( int i = 0; i < numBeams; i++ ) {
		beams[i].loop(millis);
	}
	for ( int j = 0; j < info.numLEDs; j++ ) {
		uint32_t currentColor = 0;
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

char * DRAnimation1:: name() {
	return "DRAnimation1";
}
