//
//  RNLights.cpp
//  PlatformTest0
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#include "RNLights.h"

// 
RNLights::RNLights(uint16_t numPixels) : numPixels(numPixels) {
    pixels = (uint8_t*)malloc(numPixels * 3);
    reset();
    }

RNLights::~RNLights() {
    free(pixels);
}

void RNLights::reset() {
    fullBrightness = true;
    brightness = 0;
    for(int i = 0; i < numPixels*3; i++)
        pixels[i] = 0;
    offset = 0;
}

void RNLights::fade(uint8_t amount) {
   
    for(int i = 0; i < numPixels*3; i++) {
        uint8_t v = pixels[i];
        if (v == 0) continue;
        if (v <= amount)
            pixels[i] = 0;
        else
            pixels[i] = v-amount;
    }
}

void RNLights::fadeMultiply(uint8_t amount) {
    
    for(int i = 0; i < numPixels*3; i++) {
        uint8_t v = pixels[i];
        if (v == 0) continue;
        uint16_t v16 = v;
        v = (v16 * amount) >> 8;
        pixels[i] = v;
    }
}

void RNLights::rotate(bool up) {
    // if up, what was v[i] should now be at v[i+1]
    if (up) {
        if (offset == 0)
            offset = numPixels-1;
        else offset--;
    } else  if (offset == numPixels-1)
        offset = 0;
    else
        offset++;
}
void RNLights::shift(bool up) {
    rotate(up);
    if (up)
        setPixelColor(0, 0, 0, 0);
    else
        setPixelColor(numPixels-1, 0, 0, 0);
}


void RNLights::setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
    pixel = 3*((pixel+offset) % numPixels);
    pixels[pixel] = red;
    pixels[pixel+1] = green;
    pixels[pixel+2] = blue;

}

void RNLights::setAllPixelColors(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *p = pixels;
    uint8_t *pixelsEnd = p + numPixels*3;
    while(p < pixelsEnd)
        *p++ = red;
    *p++ = green;
    *p++ = blue;
}

void RNLights::getPixelColor(uint16_t pixel, uint8_t &red, uint8_t &green, uint8_t &blue) {
    pixel = 3*((pixel+offset) % numPixels);
    red = pixels[pixel];
    green = pixels[pixel+1];
    blue = pixels[pixel+2];
    
}
uint8_t RNLights::getPixelRed(uint16_t pixel) {
    pixel = 3*((pixel+offset) % numPixels);
    return pixels[pixel];
}
uint8_t RNLights::getPixelGreen(uint16_t pixel)  {
    pixel = 3*((pixel+offset) % numPixels);
    return pixels[pixel+1];
}

uint8_t RNLights::getPixelBlue(uint16_t pixel)  {
    pixel = 3*((pixel+offset) % numPixels);
    return pixels[pixel+2];
}

void RNLights::setBrightness(uint16_t amount) {
    if(amount == 256)
        fullBrightness = true;
    else {
        fullBrightness = false;
        brightness = (uint8_t) amount;
    }
}
uint16_t RNLights::getBrightness() {
    if (fullBrightness)
        return 256;
    return brightness;
}

uint16_t RNLights::normalize(int16_t pixel) {
    while (pixel < 0)
        pixel += numPixels;
    if (pixel < numPixels)
        return pixel;
    return pixel % numPixels;
}


