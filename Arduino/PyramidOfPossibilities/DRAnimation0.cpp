//
//  DRAnimation0.cpp
//  PlatformData
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "DRAnimation0.h"

#define MAX_BRIGHTNESS 120

static uint32_t i = 0;

void DRAnimation0::paint(RNLights & lights) {
	uint8_t hue = (getAnimationMillis() / 2) % 256;
	lights.setAllPixelColors((i==0)?MAX_BRIGHTNESS:0,(i==1)?MAX_BRIGHTNESS:0,(i==2)?MAX_BRIGHTNESS:0);

	if ( info.getTaps() ) {
		info.printf("Tappy\n");
		i = (i+1)%3;
	}
}

char * DRAnimation0:: name() {
	return "DRAnimation0";
}
