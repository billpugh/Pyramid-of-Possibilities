//
//  Constants.cpp
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Constants.h"

unsigned long ConstantsAnimationDuration() {

// If RN_REALLY_LONG_ANIMATIONS is defined then we return a VERY long time (1 hour) for each animation. Otherwise, use the normal value
#ifdef RN_REALLY_LONG_ANIMATIONS
	return 3600000;
#else
	return 60000;			// Normal value for animation duration.
#endif
}