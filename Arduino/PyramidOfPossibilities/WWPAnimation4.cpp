//
//  WWPAnimation4.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "WWPAnimation4.h"

  char * WWPAnimation4:: name() {
    return "WWPAnimation4";
  }
   
   
void WWPAnimation4::paint(RNLights & lights, int position, int length, 
uint8_t r, 
uint8_t g, 
uint8_t b ) {
  for(int i = position; i < position+length; i++) {
    int j = lights.normalize(i);
    lights.addPixelColor(j, r, g, b);
  }
}

void WWPAnimation4::paint(RNLights & lights) {

  int length = 20;

  int rPos = getAnimationMillis()/10;
  int gPos = getAnimationMillis()/17;
  int bPos = -getAnimationMillis()/13;
  paint(lights, rPos, length, 120, 0, 0);
  paint(lights, gPos, length, 0, 120, 0);
  paint(lights, bPos, length, 0, 0, 120);

}



