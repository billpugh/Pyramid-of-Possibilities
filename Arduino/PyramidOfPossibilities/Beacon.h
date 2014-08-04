//
//  Beacon.h
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __Beacon__
#define __Beacon__

#include "RNAnimation.h"
#include "RNGradient.h"


struct BeaconParameters {
    uint8_t rpm = 30;
    float width = 0.05;
    RNGradient gradient = RNGradient(0, RNGradientCapped, 0xff0000, 0x000000);
    
    
   
};


class Beacon : public RNAnimation {
public:
    Beacon(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(BeaconParameters), &parameters) { };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
    BeaconParameters parameters;


};

#endif /* defined(__Beacon__) */
