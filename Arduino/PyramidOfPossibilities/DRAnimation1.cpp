//
//  DRAnimation1.cpp
//  PlatformData
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Arduino.h"
#include "DRAnimation1.h"
#include "RNBeam.h"

//#define CONSIDER_THE_ACCELEROMETER

// TODO: don't statically allocate these. move to constructor.
const uint8_t numBeams = 3;
RNBeam beams[numBeams] = {
	RNBeam(),
	RNBeam(),
	RNBeam()
};
float widths[numBeams] = {100,100,100};

void initalizeBeams(RNInfo * info) {
    
	for ( uint8_t n = 0; n < numBeams; n++ ) {
  		beams[n].speed = 1+n;
  		beams[n].offset = 333 * n;
        beams[n].width = widths[n];
  		beams[n].r = (n==0)*200;
  		beams[n].g = (n==1)*200;
  		beams[n].b = (n==2)*200;
		beams[n].info = info;
	}
}

void DRAnimation1::paint(RNLights & lights) {
    
	unsigned long millis = getAnimationMillis();
    
	// Begin real animation
#ifdef CONSIDER_THE_ACCELEROMETER
	// TODO: find a better multipler. See bill's code where he had a good value to use.
	float activity = info.getLocalActivity();
	if ( activity < min_g ) {
		activity = min_g;
	} else if ( activity > max_g ) {
		activity = max_g;
	}
	float g_range = max_g - min_g;
	float multiplier = (activity - min_g) / g_range;
	for ( int i = 0; i < numBeams; i++ ) {
		beams[i].width = widths[i] * multiplier + 33;
	}
	info.printf("multiplier is %f.  Local Activity is %f\n", multiplier, info.getLocalActivity());
#endif
    
    
	for ( int i = 0; i < numBeams; i++ ) {
//        uint32_t bcolor = 0;
//        switch (i) {
//            case 0:
//                bcolor = parameters.color_0;
//                break;
//            case 1:
//                bcolor = parameters.color_1;
//                break;
//            case 2:
//                bcolor = parameters.color_2;
//            default:
//                break;
//        }
//        beams[i].r = bcolor >> 16;
//        beams[i].g = bcolor >> 8;
//        beams[i].b = bcolor;
		beams[i].loop(millis);
	}
    
	for ( int j = 0; j < info.numLEDs; j++ ) {
		uint32_t currentColor = parameters.base_color;
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

	info.showActivityWithSparkles(lights);
}

const char * DRAnimation1:: name() {
	return "DRAnimation1";
}
