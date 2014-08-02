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
#include <stdarg.h>


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
x(x), y(y), z(z), sparkles(numLEDs) {
    sparkles.setFade(millis(), 750);
    for(int i = 0; i < numLEDs; i++) {
        localAngle[i] = ((float)i)/numLEDs;
        globalAngle[i] = localAngle[i];
    }
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
    return globalAngle[led];
}


float RNInfo::getLocalAngle(uint8_t led) {
    return localAngle[led];
}

float getGlobalRadius(uint8_t led) {
    return 1.0;
}

unsigned long RNInfo::timeSinceLastTap() {
    return millis() - lastTap;
}

void RNInfo::println(const char * s) {
    Serial.println(s);
}

void RNInfo::printf(const char *fmt, ... ){
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

long RNInfo::getRandom(long max) {
    return random(max);
}
long random(long max);

void RNInfo::update() {
    sparkles.fade(millis());
    if (getTaps()) {
        for(int i = 0; i < numLEDs/20; i++) {
            sparkles.setPixelColor(getRandomPixel(), 255, 255, 255);
        }
    }
}

void RNInfo::showActivityWithBrightness(RNLights & lights,  uint16_t minBrightness) {
    int maxAdjustment = (256 - minBrightness);
    float activity = getLocalActivity() * 6;
    if (activity > 1.0)
        activity = 1.0;
    minBrightness += maxAdjustment * activity / 4;
    if (minBrightness >= 256) return;
    int b = 256;
    int age = timeSinceLastTap() - 100;
    if (age > 0)
        b = 256 - age/2;
    if (b < minBrightness)
        b = minBrightness;
    int newBrightness = b * lights.getBrightness() / 256;
    printf("Changing brightness %d -> %d\n", lights.getBrightness(), newBrightness);
    
    lights.setBrightness(newBrightness);
}


void RNInfo::showActivity(RNLights & lights, bool showSparkles, uint16_t minBrightness) {
    if (showSparkles)
        showActivityWithSparkles(lights);
    if (minBrightness < 255)
        showActivityWithBrightness(lights, minBrightness);
}


void RNInfo::showActivityWithSparkles(RNLights & lights) {
    lights.applyBrightness();
    lights.copyPixelsMax(sparkles);
}

