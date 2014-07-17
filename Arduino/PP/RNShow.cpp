//
//  RNShow.cpp
//  RNShow
//
//  Created by Bill on 6/15/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "RNShow.h"

RNShow::RNShow(RNLights & lights) : 
lights(lights) {
}

RNShow::~RNShow() {
}

void RNShow::accelerometerCallback( float totalG,
float directionalG[3],
uint8_t tapSource) {
}

unsigned long RNShow::getMillis() {
  return ms;
}
void RNShow::setMillis(unsigned long millis) {
  this->ms = millis;
}

