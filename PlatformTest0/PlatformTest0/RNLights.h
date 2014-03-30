//
//  RNLights.h
//  PlatformTest0
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#ifndef __PlatformTest0__RNLights__
#define __PlatformTest0__RNLights__

#include <iostream>


class RNLights {
    
public:
    RNLights(uint16_t numPixels=219);
    ~RNLights();
    
    void setBrightness(uint16_t amount=256);
    uint16_t getBrightness();
    
    uint16_t getNumPixels();
    uint16_t normalize(int16_t pixel);
    void reset();
    void rotate(bool up);
    void shift(bool up);
    void fade(uint8_t amount=1);
    void fadeMultiply(uint8_t amount=255);
    void setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
    void setAllPixelColors(uint8_t red, uint8_t green, uint8_t blue);
    void getPixelColor(uint16_t pixel, uint8_t &red, uint8_t &green, uint8_t &blue);
    uint8_t getPixelRed(uint16_t pixel);
    uint8_t getPixelGreen(uint16_t pixel);
    uint8_t getPixelBlue(uint16_t pixel);
    
private:
    const uint16_t numPixels;
    uint16_t offset;
    bool fullBrightness;
    uint8_t brightness;
    
    // Note: pixel i is stored at pixel[(i+offset) % numPixels];
    uint8_t * pixels;
};

#endif /* defined(__PlatformTest0__RNLights__) */
