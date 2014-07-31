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

const uint8_t numBeams = 1;
RNBeam beams[numBeams] = { 
	// RNBeam(),
	// RNBeam(), 
	// RNBeam(),
	RNBeam()
};
static int once = 0;

void initalizeBeams(RNInfo * info) {
  	// beams[0].speed = 128;
  	// beams[0].width = 35;
  	// beams[0].offset = 0;
  	beams[0].info = info;
}

void DRAnimation1::paint(RNLights & lights) {

	if ( once == 0 ) {
		initalizeBeams(&info);
	}
	if ( ++once < 50 ) {
		lights.setAllPixelColors(once, 0, 0);
		return;
	}

	unsigned long millis = getAnimationMillis();
	// info.printf("Millis = %ld\n", millis);

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
			info.printf("beam[%d] color is 0x%016x\n", j, currentColor);
	  	}
		lights.setPixelColor(j, currentColor);
	}
}

char * DRAnimation1:: name() {
	return "DRAnimation1";
}
