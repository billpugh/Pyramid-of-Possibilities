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


// Red Beacon
struct BeaconParameters {
    uint8_t numBeacons = 2;
    bool onlyExterior = false;
    float width = 0.05;
    RNGradient gradient = RNGradient(0, RNGradientCapped, 0xff0000, 0x000000);
    RNGradient baseGradient = RNGradient(0, RNGradientCapped, 0x000000, 0x000000);
};

// Blue Exterior Beacon
//struct BeaconParameters {
//    uint8_t numBeacons = 1;
//    bool onlyExterior = true;
//    float width = 0.05;
//    RNGradient gradient = RNGradient(0, RNGradientCapped, 0x0000ff, 0x000022);
//    RNGradient baseGradient = RNGradient(0, RNGradientCapped, 0x000000, 0x000000);
//};

// Rainbow Wipe
//struct BeaconParameters {
//    uint8_t numBeacons = 1;
//    bool onlyExterior = false;
//    float width = 0.2;
//    RNGradient gradient = RNGradient(0, RNGradientCapped, 0xff0000, 0x000000);
//    RNGradient baseGradient = RNGradient(1, RNGradientCapped, 0x00FFFF, 0xFFFFFF);
//};

// Christmas Tree
//struct BeaconParameters {
//    uint8_t numBeacons = 3;
//    bool onlyExterior = false;
//    float width = 0.15;
//    RNGradient gradient = RNGradient(0, RNGradientCapped, 0x44FF00, 0x00FF33);
//    RNGradient baseGradient = RNGradient(0, RNGradientCapped, 0xAA3300, 0xAA8800);
//};




class Beacon : public RNAnimation {
public:
    Beacon(RNInfo & info, AnimationInfo animationInfo)
    : RNAnimation(info, animationInfo, sizeof(BeaconParameters), &parameters) { };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();
    
    BeaconParameters parameters;


};

#endif /* defined(__Beacon__) */
