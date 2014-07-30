//
//  RNInfo.cpp
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//


#include "RNInfo.h"
#include "Arduino.h"
#include <stdlib.h>
#include <stdio.h>


RNInfo::RNInfo(
uint8_t numLEDs,
uint8_t tier,
uint8_t number,
uint8_t identifier,
int16_t x,
int16_t y,
int16_t z) : 
numLEDs(numLEDs),
tier(tier), number(number), identifier(identifier),
x(x), y(y), z(z) {
};


float myTotalG = 0;
float myDirectionalG[3];
uint8_t myTapSource;
unsigned long lastTap = 0;

void accelerometerCallback( float totalG, 
float directionalG[3],
uint8_t source) {
  //  if (source)
  //    printf("TotalG = %f\n", totalG);
  if (source)
    lastTap = millis();
  myTotalG = totalG;
  myTapSource = source;
  for(int i = 0; i < 3; i++)
    myDirectionalG[i] = directionalG[i];
}



unsigned long RNInfo::getGlobalMillis() {
  return millis();

}
float RNInfo::getGlobalActivity() {
  return myTotalG;
}
float RNInfo::getLocalActivity() {
  return myTotalG;
}
uint8_t RNInfo::getTaps() {
  return myTapSource;
}
void RNInfo::getLocalXYZActivity(float data[3]) {
  for(int i = 0; i < 3; i++)
    data[i] = myDirectionalG[i];
}

float RNInfo::getGlobalAngle(uint8_t led) {
  return led * 360.0 / numLEDs;
}

float getGlobalRadius(uint8_t led) {
  return 1.0;
}

unsigned long RNInfo::timeSinceLastTap() {
  return millis() - lastTap;
}

void RNInfo::printf(char *fmt, ... ){
  char tmp[256]; // resulting string limited to 256 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 256, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

uint16_t RNInfo::getRandomPixel() {
    return random(numLEDs);
  }

