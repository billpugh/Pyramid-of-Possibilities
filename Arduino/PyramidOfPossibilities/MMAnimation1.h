//
//  DRAnimation0.h
//  PlatformData
//
//  Created by Meelow based on Bills and Dannys work
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__MMAnimation1__
#define __PlatformData__MMAnimation1__

#include "RNAnimation.h"

class MMAnimation1 : public RNAnimation {
private:

public:
    MMAnimation1(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {};
	// MMAnimation1(RNInfo & info, unsigned long animationStartMillis);
    virtual void paint(RNLights & lights);
    virtual char * name();

};

#endif /* defined(__PlatformData__DRAnimation0__) */
