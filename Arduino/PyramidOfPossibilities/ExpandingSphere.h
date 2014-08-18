//
//  ExpandingSphere.h
//  PlatformCode
//
//  Created by Bill on 8/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __ExpandingSphere__
#define __ExpandingSphere__

#include "RNAnimation.h"
#include "RNGradient.h"

#include "EffectParameters.h"

struct ExpandingSphereParameters : public EffectParameters {

    float thickness = 0.1;
    uint32_t color = 0x00ff00;

};
class ExpandingSphere : public RNAnimation {
public:
    ExpandingSphere(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(ExpandingSphereParameters), &parameters) {  };

    virtual void paint(RNLights & lights);

    virtual const char * name();

private:
    ExpandingSphereParameters parameters;
    uint32_t updated = 0;
    
};


#endif /* defined(__ExpandingSphere__) */
