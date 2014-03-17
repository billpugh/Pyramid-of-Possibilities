//
//  LightModel.h
//  PlatformTest0
//
//  Created by Bill on 2/24/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#ifndef __PlatformTest0__LightModel__
#define __PlatformTest0__LightModel__

#include <iostream>

typedef void (*SetPixels)(uint16_t pixel, float h, float s, float v);

typedef unsigned long millitime;
class LightModel {
    
public:
    
    LightModel(uint16_t numPixels=219);
    ~LightModel();
     void measureTempurature();
    
    void getPixelColor(uint16_t pixel, float &h, float &s, float &v);
    
    millitime update(millitime millis);
    void tap(float v);
    uint16_t random(uint16_t n);
    void setRandomPixel(float v);
    uint16_t randomPixel();
    float temperature = 0.0;
    int updates = 0;
    int tapRate = 0;
    int jiggleRate = 0;
    int updateRate = 0;
    float avgJiggle = 0.0;
    
private:
    const uint16_t numPixels;

    float totalJiggle = 0.0;
    float averageTemperature = 0.0;
    bool didTap = false;
    float  *l;
    float effectiveTemperature, minL, maxL;
    int direction = 1;

    millitime nextPossibleReversal;
    millitime statsStart;
    int taps;
    int jiggles;
    

};

#endif /* defined(__PlatformTest0__LightModel__) */
