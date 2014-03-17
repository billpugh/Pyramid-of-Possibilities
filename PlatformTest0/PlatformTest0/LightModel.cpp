//
//  LightModel.cpp
//  PlatformTest0
//
//  Created by Bill on 2/24/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#include "LightModel.h"


LightModel::LightModel(uint16_t numPixels) : numPixels(numPixels) {
    if((l = (float *)malloc(numPixels * sizeof(float)))) {
        for(int i = 0; i < numPixels; i++)
            l[i] = 0.0f;
    }
    
}
LightModel::~LightModel() {
    if (l)
        free(l);
}

uint16_t LightModel::random(uint16_t n) {
    if (n == 0) return 0;
    return rand() % n;
}
uint16_t LightModel::randomPixel() {
    return random(numPixels);
}


void LightModel::setRandomPixel(float v) {
    uint16_t pixel = randomPixel();
    if (l[pixel] < v)
        l[pixel] = v;
}


void LightModel::measureTempurature(){
    effectiveTemperature = temperature - averageTemperature/3;
    if (effectiveTemperature < 0)
        effectiveTemperature = 0;
    else if (effectiveTemperature > 1.0)
        effectiveTemperature = 1.0;
    
    minL = 2.0;
    maxL = 0.0;
    for(int i = 0; i < numPixels; i++) {
        if (minL > l[i])
            minL = l[i];
        if (maxL < l[i])
            maxL = l[i];
    }
    if (maxL == minL)
        maxL = minL+0.1;
}


void LightModel::getPixelColor(uint16_t i, float &h, float &s, float &v) {
    
    v = l[i];
    s = 1.0;
    
    if (temperature < 0.9)
        h =  140*effectiveTemperature*(1+l[i]);
    else {
        float cappedTemperature = temperature;
        if (cappedTemperature > 1.0)
            cappedTemperature = 1.0;
        float r = 10*(cappedTemperature -0.9);
        
        float h1 = 140*effectiveTemperature*(1+l[i]);
        float h2 = 360*(l[i]-minL)/(maxL-minL);
        h = r*h2 + (r-1)*h1;
    }
}


float fade(float l) {
    l = l*0.9;
    if (l < 0.001)
        return 0.0;
    return l;
}

millitime LightModel::update(unsigned long millis) {
    if (didTap) {
        temperature = temperature+0.1;
        didTap = 0;
    }
    if (direction > 0) {
        float p0 = l[0];
        
        for(int i = 1; i < numPixels; i++)
            l[i-1] = fade(l[i]);
        
        l[numPixels-1] = fade(p0);
    }
    else if (direction == 0) {
        for(int i = 0; i < numPixels; i++)
            l[i] = fade(l[i]);
    }
    else if (direction < 0) {
        float p0 = l[numPixels-1];
        
        for(int i = numPixels-1; i > 0; i--)
            l[i] = fade(l[i-1]);
        
        l[0] = fade(p0);
    }
    if (millis > nextPossibleReversal
        && (direction == 0
            || ((temperature < 0.1 || temperature > 0.9) && random(30) == 0))) {
            if (direction == 0)
                direction  = random(2)*2-1;
            else
                direction = random(3)-1;
            if (direction == 0)
                nextPossibleReversal = millis + 500;
            else
                nextPossibleReversal = millis + 5000;
        }
    
    temperature = temperature*0.97;
    
    // at 10 updates / second, want to add 1 led to a strip of 8 every 3 seconds
    // add 1 to a strip of 240 every 2 updates
    if (random(1000) < numPixels)
        setRandomPixel(0.5);
    
    
    if (averageTemperature > temperature)
        averageTemperature = temperature;
    else
        averageTemperature = (19*averageTemperature + temperature)/20;
    
    updates++;
    if (millis > statsStart + 1000) {
        tapRate = taps;
        jiggleRate = jiggles;
        updateRate = updates;
        avgJiggle = totalJiggle / jiggles;
        totalJiggle = 0.0;
        taps = jiggles = updates = 0;
        statsStart = millis;
    }
    if (temperature > 1.0)
        return 40;
    else if (temperature > 0.1)
        return 160-120*temperature;
    else
        return 150 + 1/(temperature + 0.02);
    
}
void LightModel::tap(float v) {
    if (v >= 1.0) {
        v = 1.0;
        didTap = true;
        taps++;
    }
    else {
        jiggles++;
        totalJiggle += v;
    }
    
    int num = v*numPixels/10;
    setRandomPixel(v);
    for(int i = 0; i < num; i++) {
        setRandomPixel(v);
    }
    
}