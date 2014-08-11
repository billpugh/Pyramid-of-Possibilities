//
//  Qbert.h
//  PlatformData
//
//  Created by Danny
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __QBERT__
#define __QBERT__

#include "RNAnimation.h"

struct QbertParameters {
    uint8_t colors[15];		// 3 bytes per color
    uint8_t numColors;
};

class Qbert : public RNAnimation {
public:
    Qbert(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {

    	// initialize animation to have 3 colors
    	parameters.colors[0] = 0xFF;
    	parameters.colors[1] = 0x00;
    	parameters.colors[2] = 0x00;

    	parameters.colors[3] = 0x00;
    	parameters.colors[4] = 0xFF;
    	parameters.colors[5] = 0x00;
    	
    	parameters.colors[6] = 0x00;
    	parameters.colors[7] = 0x00;
    	parameters.colors[8] = 0xFF;

    	parameters.numColors = 3;
    
        // initalize class properties
    	i = 0;

    };
    virtual void paint(RNLights & lights);
    virtual const char * name();

    uint8_t i;

    QbertParameters parameters;

};

#endif /* defined(__QBERT__) */
