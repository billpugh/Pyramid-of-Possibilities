//
//  GlowFade.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __GlowFade__
#define __GlowFade__

#include "RNAnimation.h"

class GlowFade : public RNAnimation {

public:
    GlowFade(RNInfo & info, unsigned long animationStartMillis);
    virtual void paint(RNLights & lights);
    virtual char * name();
private:
    RNLights sparkles;

};

#endif /* defined(__GlowFade__) */
