//
//  DRAnimation2.cpp
//  PlatformData
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "DRAnimation2.h"


void DRAnimation2::setup() {

}

void DRAnimation2::paint(RNLights & lights) {

	static int once = 0;
	if ( !once ) {
		setup();
		once = 1;
		lights.setPixelColor(20, 100, 0, 0);		
	}
	lights.rotate(true);

}

char * DRAnimation2:: name() {
	return "DRAnimation2";
}
