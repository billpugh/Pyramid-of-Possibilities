//
//  RNInfo.cpp
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//


#include "RNInfo.h"
#include "Arduino.h"
#include "ledPositions.h"
#include "RNComm.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

RNInfo::RNInfo(
               uint8_t numLEDs,
               uint8_t identifier,
               int16_t x,
               int16_t y,
               int16_t z) : Platform( identifier, x, y, z, 1, 1),
numLEDs(numLEDs), sparkles(numLEDs) {
    initialize();
   };

void RNInfo::initialize() {
    float radiansInCircle = 2 * 3.1415926;
    sparkles.setFade(millis(), 750);

    if (x != 0 || y != 0)
        platformGlobalAngle = atan2(y, x)/radiansInCircle;

    for(int i = 0; i < numLEDs; i++) {
        float  xLED = getLEDXPosition(i);
        float  yLED = getLEDYPosition(i);
        localAngle[i] =atan2(yLED, xLED)/radiansInCircle;
        xLED += x;
        yLED += y;
        if (xLED == 0 && yLED == 0)
            globalAngle[i] = 0;
        else {
            float d = atan2(yLED, xLED)/radiansInCircle;
            if (d < 0) d = 1.0+d;
            globalAngle[i] = d;
        }

        float r = xLED*xLED + yLED*yLED;
        globalRadius[i] = sqrt(r);
        globalRadiusGround[i] = sqrt(r+((float) z)*z);
        
    }
    
    
}


float RNInfo::getPlatformGlobalAngle() {
    return platformGlobalAngle;
}

bool RNInfo::isExteriorLED(uint8_t led) {
    if (x == 0 && y == 0)
        return true;
    int16_t  xLED = getLEDXPosition(led);
    int16_t  yLED = getLEDYPosition(led);
    return x*xLED + y*yLED >= 0;
}

RNInfo::RNInfo(uint8_t numLEDs, Platform & p)

                : Platform(p),
numLEDs(numLEDs), sparkles(numLEDs)  {
    initialize();
};


void RNInfo::accelerometerCallback( float totalG,
                           float directionalG[3],
                           uint8_t source) {
//      if (source)
//        printf("TotalG = %f\n", totalG);
    if (source)
        lastTap = millis();
    myTotalG = totalG;
    myTapSource = source;
    accumulatedTaps |= source;
    for(int i = 0; i < 3; i++) {
        myDirectionalG[i] = directionalG[i];
        if (maxDirectionalG[i] < directionalG[i])
            maxDirectionalG[i] = directionalG[i];
    }
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
uint8_t RNInfo::getAndResetAccumulatedTaps() {
    uint8_t result = accumulatedTaps;
    accumulatedTaps = 0;
    return result;
}

void RNInfo::getLocalXYZActivity(float data[3]) {
    for(int i = 0; i < 3; i++)
        data[i] = myDirectionalG[i];
}

void RNInfo::getAndResetAccumulatedXYZActivity(float data[3]) {
    for(int i = 0; i < 3; i++) {
        data[i] = maxDirectionalG[i];
        maxDirectionalG[i] = 0.0;
    }
}

float RNInfo::getGlobalAngle(uint8_t led) {
    return globalAngle[led];
}


float RNInfo::getLocalAngle(uint8_t led) {
    return localAngle[led];
}

float RNInfo::getGlobalRadius(uint8_t led) {
    return globalRadius[led];
}

// Distance of pixel from center at ground level
float RNInfo::getGlobalRadiusGround(uint8_t led) {
    return globalRadiusGround[led];
}


unsigned long RNInfo::timeSinceLastTap() {
    return millis() - lastTap;
}

void RNInfo::println(const char * s) {
#ifndef POP_SIMULATOR
    Serial.println(s);
#endif
}

void RNInfo::printf(const char *fmt, ... ){
#ifndef POP_SIMULATOR
    char tmp[256]; // resulting string limited to 256 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 256, fmt, args);
    va_end (args);
    Serial.print(tmp);
#endif
}

uint16_t RNInfo::getRandomPixel() {
    return random(numLEDs);
}

int RNInfo::getRandom(int max) {
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
#ifdef RN_PRINT_BRIGHTNESS_ADJUSTMENTS
    printf("Changing brightness %d -> %d\n", lights.getBrightness(), newBrightness);
#endif /* RN_PRINT_BRIGHTNESS_ADJUSTMENTS */    
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


void RNInfo::yield() {
    checkComm(*this);
}


