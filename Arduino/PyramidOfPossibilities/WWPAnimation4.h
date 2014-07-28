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

class WWPAnimation4 : public RNAnimation {
public:
    WWPAnimation4(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
    virtual void paint(RNLights & lights);

    void paint(RNLights & lights, int position, int length, 
	uint8_t r, 
	uint8_t g, 
	uint8_t b );
  virtual char * name();
    
};


#endif /* defined(__PlatformData__WWPAnimation4__) */
