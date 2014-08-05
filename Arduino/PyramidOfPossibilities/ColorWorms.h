//
//  WWPAnimation4.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__WWPAnimation4__
#define __PlatformData__WWPAnimation4__

#include "RNAnimation.h"


struct WWPAnimation4Parameters {
    
    
    uint8_t brightness = 120;
    int8_t redSpeed = 20;
    int8_t greenSpeed = 34;
    int8_t blueSpeed = -26;
    
     uint8_t brightnessWithoutActivity = 32;
    
    float lengthFraction = 1/3.0;
    
    
};


class WWPAnimation4 : public RNAnimation {
public:
    WWPAnimation4(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(WWPAnimation4Parameters), &parameters) {};
    virtual void paint(RNLights & lights);

    void paint(RNLights & lights, int position, int length, 
	uint8_t r, 
	uint8_t g, 
	uint8_t b );
  virtual const char * name();
    
    WWPAnimation4Parameters parameters;
    
};


#endif /* defined(__PlatformData__WWPAnimation4__) */
