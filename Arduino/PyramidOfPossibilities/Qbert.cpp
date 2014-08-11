//
//  Qbert.cpp
//  PlatformData
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Qbert.h"

void Qbert::paint(RNLights & lights) {

	if ( info.getTaps() ) {
		i++;
	}
	if ( i >= parameters.numColors ) {
		i = 0;
	}

	uint8_t *color = &(parameters.colors[i*3]);

	lights.setAllPixelColors(color[0],color[1],color[2]);

}

const char * Qbert:: name() {
	return "Qbert";
}
